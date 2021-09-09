from .. API.API import DronesState, Permissions


class Utils:
    @staticmethod
    # Generate permissions based on the state of the swarm
    def getPermissions(swarmState):
        # Case A : swarmState = "notReady | updating | landing | taking Off " --> Available commands :
        if swarmState == DronesState.notReady or swarmState == DronesState.updating or swarmState == DronesState.landing or swarmState == DronesState.takingOff:
            return Permissions.caseA

        # Case B : swarmState = "ready" --> Available commands : Take off, start exploration, software update
        if swarmState == DronesState.ready:
            return Permissions.caseB

        # Case C : swarmState = "explorating" --> Available commands : land, return to base
        if swarmState == DronesState.explorating:
            return Permissions.caseC

        # Case D : swarmState = "return to base | hovering " --> Available commands : land
        if swarmState == DronesState.returningToBase or swarmState == DronesState.hovering:
            return Permissions.caseD

        else:
            return Permissions.caseA

    @staticmethod
    # Generated the state of the swarm according to the state of each of the drones
    def getSwarmState(dronesData):
        nDrone = len(dronesData)

        if nDrone == 0:
            return DronesState.notReady

        counts = Utils.getStatesCount(dronesData)

        for state in counts:
            if counts[state] == nDrone:
                return state

        return Utils.getComplexState(counts)

    @staticmethod
    def getStatesCount(dronesData):

        # Counts of drones in states :
        counts = {
            DronesState.ready: 0,
            DronesState.notReady: 0,
            DronesState.takingOff: 0,
            DronesState.landing: 0,
            DronesState.hovering: 0,
            DronesState.explorating: 0,
            DronesState.returningToBase: 0,
            DronesState.updating: 0,
            DronesState.disconnected: 0
        }

        for droneData in dronesData:
            droneState = dronesData[droneData]['state']
            counts[droneState] += 1

        return counts

    # The order is importants
    @staticmethod
    def getComplexState(counts):
        if counts[DronesState.explorating] > 0:
            return DronesState.explorating

        if counts[DronesState.returningToBase] > 0:
            return DronesState.returningToBase

        if counts[DronesState.notReady] > 0 or counts[DronesState.disconnected] > 0:
            return DronesState.notReady

        if counts[DronesState.hovering] > 0:
            return DronesState.hovering

        if counts[DronesState.updating] > 0:
            return DronesState.updating

        return DronesState.notReady
