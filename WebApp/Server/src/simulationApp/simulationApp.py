from .. interfaces.AppManager import AppManager
from ..API.API import AppsId, NameSpaces
from ..data.dataManager import DataManager
import requests

SIMULATION_API = 'http://0.0.0.0:2000/'

# Inherits from AppManager interface
class SimulationApp(AppManager):
    def __init__(self):
        self.sessionData = dict()
        self.dataManager = DataManager()

    def registerNewClient(self, clientId, sid):
        self.sessionData[sid] = clientId

    def startApp(self, nDrones):
        self.dataManager.startNewSession(NameSpaces.argosSimulation)
        START_SIMULATION = 'startSimulation'
        PARAM = 'nDrones'
        return requests.get(SIMULATION_API + START_SIMULATION, params={PARAM: nDrones})

    def stopApp(self):
        STOP_SIMULATION = 'stopSimulation'
        return requests.get(SIMULATION_API + STOP_SIMULATION)

    # Not used
    def sendCommand(self, data):
        pass

    def getAppData(self, dataToTransmit='None', emitterSid=None):
        isAppReady = self.isReady()
        isAppReady = '1' if isAppReady else '0'

        data = {
            'runningAppId': AppsId.simulationApp,
            'isRunningAppReady': isAppReady,
            'connectedClientsId': list(self.sessionData.values())
        }
        isDronesData = emitterSid in self.sessionData and self.sessionData[
            emitterSid] == AppsId.simulationApp
        data['runningAppData'] = self.dataManager.sanitizeAndSaveData(
            dataToTransmit, isDronesData)

        # Argos can only receive string
        if not isDronesData:
            data['runningAppData'] = str(data['runningAppData'])
            print(data, flush=True)

        return data

    # When a client disconnects
    def removeClient(self, sid):
        disconnectedAppId = self.sessionData[sid]
        if disconnectedAppId == AppsId.webApp:
            self.stopApp()
        del self.sessionData[sid]

    def isReady(self):
        numberOfClientsNeeded = 2
        registeredApps = self.sessionData.values()
        return len(self.sessionData) == numberOfClientsNeeded and AppsId.webApp in registeredApps and AppsId.simulationApp in registeredApps

    # Allows you to know which client to send the communication to depending on the sender of the communication
    def getReceiverSid(self, emitterSid):
        for sid in self.sessionData:
            if sid != emitterSid:
                return sid

    def shouldBeDestroyed(self):
        return len(self.sessionData) == 0
