import socketio


sio = socketio.Client()
isAppReady = False

@sio.on('connect',namespace = '/argosSimulation')
def connect() :
    print('connected!!!!!!!!!!!')
    sio.emit('registerClient','3',namespace = '/argosSimulation')


@sio.on('communication', namespace = '/argosSimulation')
def regularUpdate(data) :
    global isAppReady
    isAppReady = (data['isRunningAppReady'] == '1')
    if isAppReady :
        print("On regulllar updatae : ", data['runningAppData'])
    
if __name__ == "__main__" :
    sio.connect('http://localhost:5000',namespaces = ['/argosSimulation'])
    while not isAppReady :
        pass
    while 1 :
        command = input('Enter Command\n')
        if command == 'T' :
            print('Take Off Command!\n')
            sio.emit('communication', '2', namespace ='/argosSimulation')
        if command == 'L' :
            print('Land Commad\n')
            sio.emit('communication', '3', namespace ='/argosSimulation')
        if command == 'S' :
            print('Stop Simulation Commad\n')
            sio.emit('communication', '1', namespace ='/argosSimulation')
        if command == 'E' :
            print('We are breaking\n')
            break
