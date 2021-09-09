from cflib.crazyflie import Crazyflie
from cflib.crazyflie.log import LogConfig
import logging

from .logConfigsUtils import LogConfigUtils

import struct 
from ...API.API import DronesState

logging.basicConfig(level=logging.ERROR)
class CrazyFlieWrapper :
    def __init__(self, URI, droneId) :
        self.crazyFlie = Crazyflie()
        self.URI = URI
        self.droneId = droneId
        self.registerCallBack()
        self.initData()
        
    
    def connect(self) :
        self.crazyFlie.open_link(self.URI)
    
    def disconnect(self) :
        self.crazyFlie.close_link()
    
    def initData(self) :
        self.data = {
            self.droneId : {
                "back": None,
                "batteryLevel": None,
                "front": None,
                "left": None,
                "orientation": None,
                "positionX": None,
                "positionY": None,
                "positionZ": None,
                "right": None,
                "state": DronesState.disconnected,
                "velocityX": None,
                "velocityY": None,
                "velocityZ": None,
                "roll": None,
                "yaw": None,
                "pitch":None,

            }
        }

    def sendCommand(self, command) :
        data = struct.pack("<i", command)
        self.crazyFlie.appchannel.send_packet(data)

    def setLogConfigs(self, logConfigs) :
        for logConfig in logConfigs : 
            self.crazyFlie.log.add_config(logConfig)
            logConfig.data_received_cb.add_callback(self.updateData)
            logConfig.start()

    def updateData(self, timestamp, data, logConfig) :
        if logConfig.name == 'MultiRangerLogs' :
            scalingFactor = 1000
            self.data[self.droneId]['back'] = data['range.back'] / scalingFactor
            self.data[self.droneId]['front'] = data['range.front'] / scalingFactor
            self.data[self.droneId]['left'] = data['range.left'] / scalingFactor
            self.data[self.droneId]['right'] = data['range.right'] / scalingFactor
       
        elif logConfig.name == 'KalmanLogs' :
            self.data[self.droneId]['velocityX'] = data['stateEstimate.vx']
            self.data[self.droneId]['velocityY'] = data['stateEstimate.vy']

            self.data[self.droneId]['positionX'] = data['stateEstimate.x'] 
            self.data[self.droneId]['positionY'] = data['stateEstimate.y'] 
            self.data[self.droneId]['positionZ'] = data['stateEstimate.z']

        else : 
            self.data[self.droneId]['state'] = data['drone.droneState']
            self.data[self.droneId]['batteryLevel'] = data['drone.batteryLevel']
            self.data[self.droneId]['roll'] = data['stabilizer.roll']
            self.data[self.droneId]['yaw'] = data['stabilizer.yaw']
            self.data[self.droneId]['pitch'] = data['stabilizer.pitch']


    def registerCallBack(self) :
        self.crazyFlie.connected.add_callback(self.onConnect)
        self.crazyFlie.disconnected.add_callback(self.onDisconnect)
        self.crazyFlie.connection_failed.add_callback(self.onDisconnect)
        self.crazyFlie.connection_lost.add_callback(self.onDisconnect)

    
    def onConnect(self, link_uri):
        logConfigs = LogConfigUtils.getLogConfigs()
        self.setLogConfigs(logConfigs)
    
    def onDisconnect(self, uri, msg = None) :
        print(msg)
        self.initData()
    
    def getData(self) :
        return self.data
    
    def isConnected(self) :
        return self.crazyFlie.is_connected()
