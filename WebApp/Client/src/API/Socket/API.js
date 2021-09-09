//Provides a communication interface between the Socket class and the rest of the components
//Provides a communication interface between the server and the Socket class
//A pear interface is used on the server side

class API{

    //Map of commands
    static commandsId = {
        takeOff: 0,
        land: 1,
        startMission : 2,
        returnToBase : 3,
        softwareUpdate: 4,
    }

    static appsId = {
        swarmApp: 0,
        simulationApp: 1,
        swarmTestApp: 2,
        webApp : 3
    }

    static appRoutes = {
        home : "/",
        connect : "connect",
        disconnect : "disconnect",
        registerClient : "registerClient",
        communication : "communication",
        notifyError : "notifyError",
        messageReceived : "messageReceived",
        startApp : "startApp",
        stopApp : "stopApp",
        softwareUpdate : "softwareUpdate",
        getDataBase : "/getDataBase",
        resetDataBase : "/resetDataBase",
        getLastSessionData : "/getLastSessionData"
    }

    static nameSpaces = {
        argosSimulation : "/argosSimulation",
        swarmApp : "/swarmApp"
    }

    static dronesState = {
        notReady : 0,
        ready : 1,
        takingOff : 2,
        landing : 3,
        hovering : 4,
        explorating: 5,
        returningToBase : 6,
        updating : 7,
        disconnected : 8,
        readyToUpdate : 9,
        isUpdating : 10,
        doneUpdating : 11,
        failedUpdating : 12
    }
    
    static permissions = {
        caseA : 0,
        caseB : 1, 
        caseC : 2,
        caseD : 3,
    }
}

export default API
