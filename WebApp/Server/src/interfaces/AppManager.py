from abc import ABC, abstractmethod


class AppManager(ABC):

    @abstractmethod
    def __init__(self):
        pass

    @abstractmethod
    def startApp(self):
        # connect
        # to the radio for the swarm app
        # to the docker container for the simulation App
        pass

    @abstractmethod
    def stopApp(self):
        # connect
        # to the radio for the swarm app
        # to the docker container for the simulation App
        pass

    @abstractmethod
    def sendCommand(self, commandId):
        pass

    # Data used to get the running application data
    @abstractmethod
    def getAppData(self):
        pass

    @abstractmethod
    def isReady(self):
        pass
