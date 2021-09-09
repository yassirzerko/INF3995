from .. import db
from datetime import datetime
from tinydb import Query
from . SLAM import mapGenerateData
from ..API.API import NameSpaces
import json
from .. Utils.utils import Utils


class DataManager():

    def __init__(self):
        self.db = db
        self.currentSessionId = None
        self.query = None
        self.nameSpace = None

    def startNewSession(self, nameSpace):
        self.configureNewSession()
        self.formatNewSession(nameSpace)

    def configureNewSession(self):
        completedSessions = self.db.all()
        self.currentSessionId = str(len(completedSessions) + 1)
        query = Query()
        self.query = query.id == self.currentSessionId

    def formatNewSession(self, nameSpace):
        sessionStartTime = str(datetime.now())

        self.db.insert({
            'id': self.currentSessionId,
            'sessionStartTime': sessionStartTime,
            'nameSpace': nameSpace,
            'dronesData': {},
            'commandsData': {}
        })
        self.nameSpace = nameSpace

    def sanitizeAndSaveData(self, data, isDronesData):
        # For simulation App, the first communication is onRegisterClient, so we don't have data
        isAppReady = data != 'None'
        if hasattr(data, 'drones'):
            isAppReady = isAppReady and len(data['drones']) != 0

        sanitizedData = self.sanitizeData(data, isDronesData)
        if isAppReady:
            self.saveData(sanitizedData, isDronesData)
        return sanitizedData

    # Used to modify datas
    def sanitizeData(self, runningAppData, isDronesData):
        if not isDronesData:
            return runningAppData

        dronesData = runningAppData['drones']

        swarmState = Utils.getSwarmState(dronesData)
        permissions = Utils.getPermissions(swarmState)
        nDrones = len(dronesData)

        sanitizedData = {
            "drones": mapGenerateData(dronesData, self.nameSpace == NameSpaces.argosSimulation),
            "swarm": {
                "state": swarmState,
                "nDrones": nDrones
            },
            "permissions": permissions
        }

        return sanitizedData

    def saveData(self, dataToSave, isDronesData):
        oldData = None
        field = None
        if isDronesData:
            field = 'dronesData'
        else:
            field = 'commandsData'

        oldData = self.db.search(self.query)[0][field]

        currentTime = str(datetime.now())
        oldData.update({
            currentTime: dataToSave
        })

        self.db.update({field: oldData},
                       self.query)
