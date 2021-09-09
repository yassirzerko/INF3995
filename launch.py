import subprocess
import time

deviceName = "Crazyradio PA"

def getDevicesList(result) :
    connectedDevices = result.stdout
    # We decode the string
    connectedDevices = str(connectedDevices, 'utf-8')

    #We split the string using the line return as a separator and return it
    return connectedDevices.split('\n')

def isItDeviceLine(line) :
    return deviceName in line

def getDesiredDevice(connectedDevices) :
    for device in connectedDevices :
        if isItDeviceLine(device) :
            return device
    return ""

def launchApp(busId) :
    print('Application en cours de lancement ...')
    
    #We give some time to the user to read the output
    time.sleep(3)

    subprocess.run("xhost +", shell = True)
    startDockerCommand = f"BUS_ID={busId} docker-compose build && docker-compose up"
    subprocess.run(startDockerCommand, shell = True)

if __name__ == "__main__" : 
    result = subprocess.run('lsusb', stdout=subprocess.PIPE)

    if result.returncode != 0 : 
        print('Une erreur est survenue')
        exit()

    connectedDevices = getDevicesList(result)
    desiredDevice = getDesiredDevice(connectedDevices)

    #We didn't find the CrazyRadio    
    if desiredDevice == "" :
        print("Nous ne parvenons pas à détecter la CrazyRadio")
        print("Voici la liste des appareils connectés : ")
        for device in connectedDevices : 
            print(device)
        exit()

    busId = (desiredDevice[4:7])
    launchApp(busId)