import socketIOClient from 'socket.io-client'
import {bindEventListeners} from './Utils'
import API from './API'

const SOCKET_SERVER_URL = "http://0.0.0.0:5000"

class Socket {
    constructor(componentToBind, namespace){
        this.initSocket(namespace)
        //We can now use this.component.updateState to send data to our binded component
        this.component = componentToBind
        this.namespace = namespace
        bindEventListeners(this)

    }

    // ---- Methods triggered by the events listeners

    onConnect() {
        console.log('connected to server :' , this.socket.connected)
        this.component.updateState({isConnected : true})
        this.registerClient()
    }  

    onDisconnect(reason) {
        console.log('disconnected from server : ', this.socket.disconnected, reason)
        this.component.resetState(reason)
    }

    onCommunication(state) {
        console.log('on communication : ', state)
        this.component.updateState(state)
    }
    // Method used to send requests to the server

    initSocket(nameSpace) {

        //Initiate a connection to the sever
        this.socket = socketIOClient(SOCKET_SERVER_URL + nameSpace, {
            reconnectionDelayMax: 100,
            cors : {
                origin: "*",
                methods: ["GET", "POST"],
                allowedHeaders: ["my-custom-header"],
                credentials: true
            },
            secure: true, reconnection: true, rejectUnauthorized: false 
        })
    }

    //To send a command to the server use this method, and use API.commands to select the command you want (command)
    sendCommand(commandId) {
        this.socket.emit(API.appRoutes.communication ,commandId)
    }

    registerClient() {
        this.socket.emit(API.appRoutes.registerClient, API.appsId.webApp)
    }

    startApp(data) {
        this.socket.emit(API.appRoutes.startApp, data)
    }

    stopApp() {
        this.socket.emit(API.appRoutes.stopApp)
    }

    softwareUpdate(data) {
        this.socket.emit(API.appRoutes.softwareUpdate, data)
    }

    closeConnection() {
        this.socket.close()
    }

}

export default Socket

