import '../../App.css';
import { Footer } from "../../Components/Footer/Footer.js"
import { Navbar } from "../../Components/Navbar/Navbar.js"
import MainPanel from "../../Components/MainPanel/MainPanel.js"
import { ControlHeader } from '../../Components/ControlHeader/ControlHeader.js'
import "./Operator.css"
import React from 'react'
import Socket from '../../API/Socket/Socket'


class Operator extends React.Component {
    constructor(props) {
        super(props)

        this.state = {
            isConnected: false,
            runningAppId: null,
            isRunningAppReady: false,
            connectedClientsId: {},
            runningAppData: {},
            nDrones : 2,
            shouldResetMap: false,
        }
        this.sendCommand = this.sendCommand.bind(this)
        this.startApp = this.startApp.bind(this)
        this.stopApp = this.stopApp.bind(this)
        this.softwareUpdate = this.softwareUpdate.bind(this)
        this.onChangeNDrones = this.onChangeNDrones.bind(this)
        this.socket = null

    }

    componentDidMount() {
        this.socket = new Socket(this, this.props.nameSpace)
    }

    resetState(reason) {
        this.setState({
            isConnected: false,
            runningAppId: null,
            isRunningAppReady: false,
            connectedClientsId: {},
            runningAppData: {},
            nDrones: 2,
            shouldResetMap: false,
        })
        this.socket = null
        alert('Une erreur est survenue, vous allez etre rediriger vers l accueil')
        window.location.replace('/')
    }

    updateState(state) {
        this.setState({ ...this.state, ...state })
    }

    onChangeNDrones(event) {
        const maxDroneNumber = 5
        const minDroneNumber = 1
        let nDrone = event.target.value
        if(nDrone > maxDroneNumber) {
            nDrone = maxDroneNumber
        }
        else if (nDrone < minDroneNumber) {
            nDrone = minDroneNumber
        }
        this.updateState({nDrones : nDrone})
    }

    sendCommand(commandId) {
        this.socket.sendCommand(commandId)
    }

    startApp() {
        this.socket.startApp(this.state.nDrones)
        this.setState({
            shouldResetMap : false
        })
        console.log(this.state.nDrones)
    }

    stopApp() {
        this.socket.stopApp()
        this.setState({
            shouldResetMap : true
        })
    }

    softwareUpdate() {
        this.socket.softwareUpdate(this.state.nDrones)
    }

    componentWillUnmount() {
        this.socket.closeConnection()
    }

    render() {
        document.title = "Swarm Robotics";
        const isRunningAppReady = this.state.isRunningAppReady == "1"
        const shouldUpdateMap = isRunningAppReady && this.state.runningAppData.swarm && (this.state.runningAppData.swarm.state == 5 || this.state.runningAppData.swarm.state == 6 ) 

        return (
            <div>
                <Navbar currentActive="/operator-system" />
                <ControlHeader 
                    isConnected = {this.state.isConnected} 
                    isRunningAppReady = {isRunningAppReady} 
                    sendCommand = {this.sendCommand} 
                    startApp= {this.startApp}
                    stopApp = {this.stopApp}
                    softwareUpdate = {this.softwareUpdate}
                    onChangeNDrones = {this.onChangeNDrones}
                    dronesData = {this.state.runningAppData} 
                    runningAppId = {this.state.runningAppId}
                    nDrones = {this.state.nDrones}/>
                <main>
                    <MainPanel dronesData = {this.state.runningAppData} shouldUpdateMap = {shouldUpdateMap} shouldResetMap = {this.state.shouldResetMap}/>
                </main>
                <Footer />
            </div>
        );
    }
}

export default Operator
