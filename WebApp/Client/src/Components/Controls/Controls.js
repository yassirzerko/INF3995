import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import Paper from '@material-ui/core/Paper';
import Grid from '@material-ui/core/Grid';
import SwarmCommand from '../SwarmCommands/SwarmCommands.js'
import SwarmStatus from '../SwarmStatus/SwarmStatus.js';
import ConnexionStatus from '../ConnexionStatus/ConnexionStatus.js';
import Hidden from '@material-ui/core/Hidden';
import * as constants from '../../Constants/constants.js';


const useStyles = makeStyles((theme) => ({
    root: {
        flexGrow: 1,
        border: '1px solid rgba(0,0,0 ,0)'
    },
    paper: {
        padding: theme.spacing(1),
        textAlign: 'center',
        height: 160,
        padding: 10,
        border: '1px solid rgba(73,63,252,1)',
        [theme.breakpoints.down("xs")]: {
            height: 260,
        },
    },
}));

export function Controls(props) {
    const classes = useStyles();
    return (
        <div className={classes.root}>
            <Grid container spacing={constants.none_space}>
                <Grid item
                    md={constants.t_column}
                    sm={constants.o_column}
                    xs={constants.o_column}>
                    <Paper className={classes.paper}
                        elevation={constants.nominal_elevation}
                        square
                        variant="outlined">
                        <SwarmCommand
                            sendCommand={props.sendCommand}
                            startApp = {props.startApp} 
                            stopApp = {props.stopApp}
                            softwareUpdate = {props.softwareUpdate}
                            onChangeNDrones={props.onChangeNDrones}
                            permissions={props.dronesData.permissions}
                            isRunningAppReady={props.isRunningAppReady}
                            runningAppId={props.runningAppId}
                            nDrones={props.nDrones} />
                    </Paper>
                </Grid>
                <Hidden only={['sm', 'xs']}>
                    <Grid className={classes.grid} item
                        md={constants.f_column}
                        sm={constants.o_column}
                        xs={constants.o_column}>
                        <Paper className={classes.paper}
                            elevation={constants.nominal_elevation}
                            square
                            variant="outlined">
                            <ConnexionStatus
                                isRunningAppReady={props.isRunningAppReady}
                                runningAppId={props.runningAppId}
                                isConnected={props.isConnected}
                            />
                        </Paper>
                    </Grid>
                </Hidden>
                <Hidden only={['sm', 'xs']}>
                    <Grid item className={classes.grid} item
                        md={constants.f_column}
                        sm={constants.o_column}
                        xs={constants.o_column}>
                        <Paper className={classes.paper}
                            elevation={constants.nominal_elevation}
                            square
                            variant="outlined">
                            <SwarmStatus dronesData={props.dronesData} />
                        </Paper>
                    </Grid>
                </Hidden>
            </Grid>
        </div>
    );
}
