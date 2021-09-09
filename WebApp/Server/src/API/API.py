class AppsId:
    swarmApp = 0
    simulationApp = 1
    swarmTestApp = 2
    webApp = 3


class CommandsId:
    takeOff = 0
    land = 1
    startMission = 2
    returnToBase = 3
    softwareUpdate = 4


class DronesState:
    notReady = 0
    ready = 1
    takingOff = 2
    landing = 3
    hovering = 4  # take off command
    explorating = 5
    returningToBase = 6
    updating = 7
    disconnected = 8
    readyToUpdate = 9
    isUpdating = 10
    doneUpdating = 11
    failedUpdating = 12


class Permissions:
    # Case A : swarmState = "notReady | updating | landing | taking Off | led " --> Available commands :
    caseA = 0

    # Case B : swarmState = "ready" --> Available commands : Take off, start exploration, software update
    caseB = 1

    # Case C : swarmState = "hovering | explorating" --> Available commands : land, return to base
    caseC = 2

    # Case D : swarmState = "return to base" --> Available commands : land
    caseD = 3


class NameSpaces:
    argosSimulation = "/argosSimulation"
    swarmApp = "/swarmApp"


class AppRoutes:
    home = "/"
    connect = "connect"
    disconnect = "disconnect"
    registerClient = "registerClient"
    communication = "communication"
    notifyError = "notifyError"
    messageReceived = "messageReceived"
    startApp = "startApp"
    stopApp = "stopApp"
    softwareUpdate = "softwareUpdate"
    getDataBase = "/getDataBase"
    resetDataBase = "/resetDataBase"
    getLastSessionData = "/getLastSessionData"
