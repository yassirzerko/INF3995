import json
import socketio
import threading
import random
import time
import math
from Slam.SLAM import mainMappingComputing




sio = socketio.Client()
isAppReady = True

# read file
with open('bd1.json', 'r') as myfile:
    data=myfile.read()

# parse file
obj = json.loads(data)
dataJson=obj['dronesData']
timeStamp=list(obj['dronesData'].keys())


########################################################################################

def sendRegularUpdate(i) :
    
    s0 =mainMappingComputing(dataJson[timeStamp[i]]['drones']['s0'])
    s1 =mainMappingComputing(dataJson[timeStamp[i]]['drones']['s1'])
    s2 =mainMappingComputing(dataJson[timeStamp[i]]['drones']['s2'])
    s3 =mainMappingComputing(dataJson[timeStamp[i]]['drones']['s3'])
    
    dataToSend = dict()
    dataToSend["s0"] = s0
    dataToSend["s1"] = s1
    dataToSend["s2"] = s2
    dataToSend["s3"] = s3
    
    #dataToSend0 = dataJson[timeStamp[i]]['drones']['s0']
    #dataToSend1 = [dataJson[timeStamp[i]]['drones']['s1'],dataJson[timeStamp[i]]['drones']['s2'],dataJson[timeStamp[i]]['drones']['s3']]

    sio.emit('communication' , dataToSend, namespace = '/argosSimulation')
   # sio.emit('communication' , dataToSend1, namespace = '/argosSimulation')
   #print("Here' the data to send0",dataToSend0)
    print("Here' the data to send",dataToSend)
    print("Here' the type data to send",type(dataToSend))
    # TO DO : Change the frequency
    threading.Timer(1000, sendRegularUpdate).start()

@sio.on('connect',namespace = '/argosSimulation')
def connect() :
    print('connected!!!!!!!!!!!')
    sio.emit('registerClient','1',namespace = '/argosSimulation')
    i=0
    sendRegularUpdate(i)

@sio.on('communication', namespace = '/argosSimulation')
def regularUpdate(data) :
    global isAppReady
    isAppReady = (data['isRunningAppReady'] == '1')
    i=0
    while isAppReady :
        sendRegularUpdate(i)
        time.sleep(1)
        i+=1
    
if __name__ == "__main__" :
    random.seed(10)
    sio.connect('http://localhost:5000',namespaces = ['/argosSimulation'])
