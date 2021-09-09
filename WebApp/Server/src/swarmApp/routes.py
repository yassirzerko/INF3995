from flask_socketio import emit
from .. import socket
from .. API.API import AppRoutes, NameSpaces
from . swarmApp import SwarmApp

nameSpace = NameSpaces.swarmApp
appManager = None


@socket.on(AppRoutes.connect, namespace=nameSpace)
def connect():
    global appManager
    appManager = SwarmApp()


@socket.on(AppRoutes.disconnect, namespace=nameSpace)
def disconnect():
    global appManager
    if appManager:
        appManager.stopApp()
        appManager = None


@socket.on(AppRoutes.communication, namespace=nameSpace)
def onClientComminucation(data):
    global appManager
    if appManager:
        appManager.sendCommand(data)


@socket.on(AppRoutes.startApp, namespace=nameSpace)
def onStartApp(data):
    global appManager
    if appManager:
        appManager.startApp(data)
        socket.start_background_task(sendRegularUpdate)


@socket.on(AppRoutes.stopApp, namespace=nameSpace)
def onStopApp():
    global appManager
    if appManager:
        appManager.stopApp()


@socket.on(AppRoutes.softwareUpdate, namespace=nameSpace)
def onSoftwareUpdate(data):
    global appManager
    if appManager:
        dataToSend = appManager.initUpdatingData(data)
        socket.emit(AppRoutes.communication, dataToSend, namespace=nameSpace)
        socket.sleep(0)
        startIndex = 1
        for index in range(startIndex, int(data) + startIndex):
            dataToSend = appManager.setDroneIsUpdating(index, dataToSend)
            socket.emit(AppRoutes.communication,
                        dataToSend, namespace=nameSpace)
            socket.sleep(0)
            dataToSend = appManager.softwareUpdate(index, dataToSend, socket)
            socket.emit(AppRoutes.communication,
                        dataToSend, namespace=nameSpace)
            socket.sleep(0)
        socket.sleep(5)
        dataToSend = appManager.getAppData()
        socket.emit(AppRoutes.communication, dataToSend, namespace=nameSpace)

# Used to send data to the client each second
def sendRegularUpdate():
    shouldContinue = True
    while shouldContinue:
        global appManager
        if appManager:
            dataToSend = appManager.getAppData()
            socket.emit(AppRoutes.communication,
                        dataToSend, namespace=nameSpace)
            shouldContinue = appManager.isAppStarted
            socket.sleep(1)
        else:
            shouldContinue = False
