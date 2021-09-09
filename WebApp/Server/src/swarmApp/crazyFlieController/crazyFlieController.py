import cflib
from .crazyFlieWrapper import CrazyFlieWrapper
from ...API.API import CommandsId

baseURI = 'radio://0/56/2M/E7E7E7E70'


class CrazyFlieController:
    def __init__(self,):
        # We init the drivers that will be used by the crazyFlies
        cflib.crtp.init_drivers(enable_debug_driver=False)
        self.desiredNdrones = None
        self.crazyFlies = dict()

    def initCrazyFlies(self, nDrones):
        self.desiredNdrones = int(nDrones)
        startIndex = 1
        for crazyFlieNumber in range(startIndex, self.desiredNdrones + 1):
            crazyFlieId = f's{crazyFlieNumber}'
            uri = f'{baseURI}{crazyFlieNumber}'
            crazyFlie = CrazyFlieWrapper(uri, crazyFlieId)
            self.crazyFlies[uri] = crazyFlie
        self.connectToCrazyFlies()

    # We try to connect to all crazyFlies that are not connected
    def connectToCrazyFlies(self):
        for uri in self.crazyFlies:
            crazyFlie = self.crazyFlies[uri]
            if not crazyFlie.isConnected():
                crazyFlie.connect()

    def sendCommand(self, command):
        # Commands to send to crazyFlies
        for crazyFlie in self.crazyFlies.values():
            crazyFlie.sendCommand(command)

    def disconnectCrazyFlies(self):
        for crazyflie in self.crazyFlies.values():
            crazyflie.sendCommand(CommandsId.land)
            crazyflie.disconnect()
        self.crazyFlies = dict()

    def isReady(self):
        # We verify first that the registered CrazyFlies are connected
        for crazyFlie in self.crazyFlies.values():
            if not crazyFlie.isConnected():
                return False

        # We verify that we have the approriate amount of connected crazyFlies
        return self.desiredNdrones and self.desiredNdrones == len(self.crazyFlies)

    def getDronesData(self):
        data = {
            'drones': {}
        }

        for crazyFlie in self.crazyFlies.values():
            data['drones'].update(crazyFlie.getData())

        return data
