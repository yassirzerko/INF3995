import React from 'react';
import Button from '@material-ui/core/Button';
import Grid from '@material-ui/core/Grid';
import TextField from '@material-ui/core/TextField';
import API from '../../API/Socket/API.js'
import * as constants from '../../Constants/constants.js'

const SFOTWARE_UPDATE_TIMEOUT   = 36000
const SOFTWARE_UPDATE_DELAY     = 5000

class SwarmCommand extends React.Component {
    constructor(props) {
        super(props)
        this.state = {
            isStartAppPressed: false,
            isSoftwareUpdatePressed: false
        }
    }

    onStartApp() {
        this.setState({
            isStartAppPressed: true
        })
        this.props.startApp()
    }

    onStopApp() {
        this.setState({
            isStartAppPressed: false
        })
        this.props.stopApp()
    }

    onSoftwareUpdate() {
        this.props.softwareUpdate()
        this.setState({
            isStartAppPressed: false,
            isSoftwareUpdatePressed: true
        })
        setTimeout(() => {
            this.setState({ ...this.state, ...{isSoftwareUpdatePressed : false}})
        }, SFOTWARE_UPDATE_TIMEOUT * this.props.nDrones + SOFTWARE_UPDATE_DELAY)
    }

    render() {
        const permissionsCase = API.permissions
        const disableAllButtons = this.props.permissions == permissionsCase.caseA || this.props.permissions == undefined
        const shouldDisableButtonGroupA = disableAllButtons
            || this.props.permissions == permissionsCase.caseC
            || this.props.permissions == permissionsCase.caseD
        const shouldDisableButtonGroupB = disableAllButtons
            || this.props.permissions == permissionsCase.caseB
            || this.props.permissions == permissionsCase.caseD

        const startButtonName = this.state.isStartAppPressed ? "Scan Again" : "Start App"

        return (
            <Grid container spacing={constants.two_space}>
                <Grid item xs={constants.t_column}>
                    <Button
                        fullWidth={true}
                        variant="contained"
                        color="default"
                        size="medium"
                        disabled={shouldDisableButtonGroupA}
                        onClick={() => this.props.sendCommand(API.commandsId.startMission)}>
                        Start Mission
                </Button>
                </Grid>
                <Grid item xs={constants.t_column}>
                    <Button
                        fullWidth={true}
                        variant="contained"
                        color="default"
                        size="medium"
                        disabled={shouldDisableButtonGroupA}
                        onClick={() => this.props.sendCommand(API.commandsId.takeOff)}>
                        Take-off
                </Button>
                </Grid>
                <Grid item xs={constants.t_column}>
                    <Button
                        fullWidth={true}
                        variant="contained"
                        color="default"
                        size="medium"
                        disabled={shouldDisableButtonGroupB}
                        onClick={() => this.props.sendCommand(API.commandsId.returnToBase)}>
                        Return to base
                </Button>
                </Grid>
                <Grid item xs={constants.t_column}>
                    <Button
                        fullWidth={true}
                        variant="contained"
                        color="default"
                        size="medium"
                        disabled={this.state.isStartAppPressed || this.state.isSoftwareUpdatePressed || this.props.runningAppId == API.appsId.simulationApp}
                        onClick={() => this.onSoftwareUpdate()}>
                        Software Update
                </Button>
                </Grid>
                <Grid item sm={constants.f_column} xs={constants.t_column}>
                    <Button
                        fullWidth={true}
                        variant="contained"
                        color="default"
                        size="medium"
                        disabled={disableAllButtons || this.props.permissions == permissionsCase.caseB}
                        onClick={() => this.props.sendCommand(API.commandsId.land)} >
                        Land
                </Button>
                </Grid>
                <Grid item sm={constants.f_column} xs={constants.t_column}>
                    <Button
                        fullWidth={true}
                        variant="contained"
                        color="default"
                        size="medium"
                        disabled={this.state.isSoftwareUpdatePressed}
                        onClick={() => this.onStopApp()}>
                        Reset App
                </Button>
                </Grid>
                <Grid item sm={constants.f_column} xs={constants.t_column}>
                    <Button fullWidth={true}
                        variant="contained"
                        color="default"
                        size="medium"
                        disabled={this.props.isRunningAppReady || this.state.isSoftwareUpdatePressed}
                        onClick={() => this.onStartApp()}>
                        {startButtonName}
                </Button>
                </Grid>
                <Grid item sm={constants.f_column} xs={constants.t_column}>
                    <TextField
                        id="outlined-number"
                        label="Select drones count(1-5)"
                        type="number"
                        defaultValue={2}
                        InputLabelProps={{
                            shrink: true,
                        }}
                        disabled={this.props.isRunningAppReady || this.state.isStartAppPressed? "disabled" : ""}
                        variant="outlined"
                        onChange={this.props.onChangeNDrones}
                        value = {this.props.nDrones}
                    />
                </Grid>
            </Grid>
        );
    }
}

export default SwarmCommand
