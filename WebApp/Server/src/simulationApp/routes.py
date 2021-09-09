from . import argosSimulationBluePrint
from flask_socketio import emit
from .. import socket
from .. API.API import AppRoutes, NameSpaces
from . simulationApp import SimulationApp
from flask import request


nameSpace = NameSpaces.argosSimulation
appManager = None


@socket.on(AppRoutes.connect, namespace=nameSpace)
def connect():
    global appManager
    if not appManager:
        appManager = SimulationApp()


@socket.on(AppRoutes.registerClient, namespace=nameSpace)
def registerClient(appId):
    sid = request.sid

    global appManager
    appManager.registerNewClient(appId, sid)

    # Each time a new client register we send to all the connected clients an update of the appState
    sendData()


@socket.on(AppRoutes.disconnect, namespace=nameSpace)
def disconnect():
    global appManager
    appManager.removeClient(request.sid)
    if appManager.shouldBeDestroyed():
        appManager.stopApp()
        appManager = None
    else:
        # Each time a client disconnect we send to all the connected clients an update of the appState
        sendData()


@socket.on(AppRoutes.communication, namespace=nameSpace)
def onClientsCommunication(data):
    sendData(False, data, request.sid)


@socket.on(AppRoutes.startApp, namespace=nameSpace)
def onStartApp(data):
    global appManager
    if appManager:
        appManager.startApp(data)


@socket.on(AppRoutes.stopApp, namespace=nameSpace)
def onStopApp():
    global appManager
    if appManager:
        appManager.stopApp()


def sendData(isBroadCast=True, dataToTransmit='None', emitterSid=None):
    global appManager
    appData = appManager.getAppData(dataToTransmit, emitterSid)

    # Each time a client connects or disconnects, the information is sent to all clients
    if isBroadCast:
        emit(AppRoutes.communication, appData,
             namespace=nameSpace, broadcast=True)
        return

    receiverSid = appManager.getReceiverSid(emitterSid)
    emit(AppRoutes.communication, appData,
         namespace=nameSpace, room=receiverSid)
