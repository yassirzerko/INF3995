from .. interfaces.AppManager import AppManager
from .. API.API import CommandsId, AppsId, NameSpaces, DronesState
from .crazyFlieController.crazyFlieController import CrazyFlieController
from ..data.dataManager import DataManager
import requests

# Inherits from AppManager interface
class SwarmApp(AppManager):
    def __init__(self):
        print('in SwarmApp')
        self.crazyFlieController = CrazyFlieController()
        self.dataManager = DataManager()
        self.isAppStarted = False

    def startApp(self, nDrones):
        self.crazyFlieController.initCrazyFlies(nDrones)
        self.dataManager.startNewSession(NameSpaces.swarmApp)
        self.isAppStarted = True

    def sendCommand(self, data):
        if data == CommandsId.softwareUpdate:
            self.softwareUpdate()
        self.crazyFlieController.sendCommand(int(data))
        data = self.dataManager.sanitizeAndSaveData(data, False)

    def softwareUpdate(self, droneIndex, data, socket):
        SOFTWARE_UPDATE_API = "http://0.0.0.0:4000/"
        START_SOFTWARE_UPDATE = 'softwareUpdate'
        TIMEOUT = 35.0
        GET_STATUS = 'getReturnCode'
        crazyFlieId = f's{droneIndex}'
        success = requests.get(
            SOFTWARE_UPDATE_API + START_SOFTWARE_UPDATE, params={'index': droneIndex})
        socket.sleep(TIMEOUT)
        success = requests.get(SOFTWARE_UPDATE_API +
                               GET_STATUS).text == 'true\n'
        data['runningAppData']['drones'][crazyFlieId]['state'] = DronesState.doneUpdating if success else DronesState.failedUpdating
        return data

    def initUpdatingData(self, nDrones):
        data = self.initAppData()
        dronesData = dict()
        dronesData['drones'] = dict()
        startIndex = 1
        for index in range(startIndex, int(nDrones) + startIndex):
            crazyFlieId = f's{index}'
            dronesData['drones'][crazyFlieId] = {
                'state': DronesState.readyToUpdate}
        data['runningAppData'] = dronesData

        data['runningAppData']['swarm'] = dict()
        data['runningAppData']['swarm']['nDrones'] = nDrones
        data['runningAppData']['swarm']['state'] = DronesState.isUpdating
        return data

    def setDroneIsUpdating(self, index, data):
        crazyFlieId = f's{index}'
        data['runningAppData']['drones'][crazyFlieId]['state'] = DronesState.isUpdating
        return data

    def initAppData(self):
        isAppReady = self.isReady()

        isAppReady = "1" if isAppReady else "0"
        data = {
            'runningAppId': AppsId.swarmApp,
            'isRunningAppReady': isAppReady,
            'connectedClientsId': [AppsId.swarmApp]
        }

        return data

    def getAppData(self):
        data = self.initAppData()
        dronesData = self.crazyFlieController.getDronesData()
        data['runningAppData'] = self.dataManager.sanitizeAndSaveData(
            dronesData, True)

        return data

    def stopApp(self):
        if self.crazyFlieController:
            self.crazyFlieController.disconnectCrazyFlies()
        self.isAppStarted = False

    def isReady(self):
        return self.crazyFlieController and self.crazyFlieController.isReady()
