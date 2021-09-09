from . import mainBluePrint
from .. API.API import AppRoutes, AppsId
from flask import jsonify
from .. import db
from ..data.dataManager import DataManager
from tinydb import Query


@mainBluePrint.route(AppRoutes.home)
def index():
    data = {
        'runningAppId': None,
        'isRunningAppReady': False,
        'connectedClientsId': AppsId.webApp,
        'runningAppData': {}
    }
    return jsonify(data)


@mainBluePrint.route(AppRoutes.getDataBase)
def getDataBase():
    data = db.all()
    return jsonify(data)


@mainBluePrint.route(AppRoutes.resetDataBase)
def resetDataBase():
    db.truncate()
    return jsonify(True)


@mainBluePrint.route(AppRoutes.getLastSessionData)
def getLastSessionData():
    completedSessions = db.all()
    lastSessionId = str(len(completedSessions))
    query = Query()
    query = lastSessionId == query.id
    lastSessionData = db.search(query)
    return jsonify(lastSessionData)
