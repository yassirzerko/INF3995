import API from './API'

//Bind the event listners to the methods of Socket
export const bindEventListeners = (Socket) => {
    const routes = API.appRoutes
    const socket = Socket.socket
    
    socket.on(routes.connect, () => {
        Socket.onConnect()
    })

    socket.on(routes.disconnect, (reason) => {
        Socket.onDisconnect(reason)
    })

    socket.on(routes.communication, (state) => {
        Socket.onCommunication(state)
    })
}

export const getDroneState = (state) => {
    const states = API.dronesState
    switch(state) {
      case states.notReady : 
        return 'NOT READY'
      case states.ready : 
        return 'READY'
      case states.takingOff : 
        return 'TAKING OFF'
      case states.landing : 
        return 'LANDING'
      case states.hovering : 
        return 'HOVERING'
      case states.explorating : 
        return 'EXPLORING'
      case states.returningToBase : 
        return 'RETURNING TO BASE'
      case states.updating : 
        return 'UPDATING'
      case states.readyToUpdate : 
        return "READY TO UPDATE"
      case states.isUpdating : 
        return "UPDATING"
      case states.doneUpdating : 
        return "DONE UPDATING"
      case states.failedUpdating : 
        return "FAILED UPDATING"
      default : 
        return "DISCONNECTED"
    }
}

