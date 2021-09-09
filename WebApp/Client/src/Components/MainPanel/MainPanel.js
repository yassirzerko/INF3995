import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import Paper from '@material-ui/core/Paper';
import Grid from '@material-ui/core/Grid';
import DroneListSection from "../DroneListSection/DroneListSection.js";
import Accordion from '@material-ui/core/Accordion';
import AccordionSummary from '@material-ui/core/AccordionSummary';
import AccordionDetails from '@material-ui/core/AccordionDetails';
import Typography from '@material-ui/core/Typography';
import ExpandMoreIcon from '@material-ui/icons/ExpandMore';
import LinearGraph from '../Map/LinearGraph.js';
import * as constants from '../../Constants/constants.js';
import SwarmStatus from '../SwarmStatus/SwarmStatus.js';
import ConnexionStatus from '../ConnexionStatus/ConnexionStatus.js';
import Hidden from '@material-ui/core/Hidden';

const useStyles = makeStyles((theme) => ({
    paper: {
        padding: theme.spacing(constants.second_theme),
        backgroundColor: constants.background_grey,
    },
}));

export default function MainPanel(props) {
    const classes = useStyles();
    const [expanded, setExpanded] = React.useState('panelMap');

    const handleChange = (panel) => (event, newExpanded) => {
        setExpanded(newExpanded ? panel : false);
    };

    return (
        <div>
            <Grid container spacing={constants.none_space}>
                <Hidden only={['xl', 'lg', 'md']}>
                    <Grid item
                        md={constants.f_column}
                        sm={constants.o_column}
                        xs={constants.o_column}>
                        <Paper className={classes.paper}
                            elevation={constants.nominal_elevation}
                            square>
                            <Accordion square >
                                <AccordionSummary expandIcon={<ExpandMoreIcon />}>
                                    <Typography>Connexion Status</Typography>
                                </AccordionSummary>
                                <AccordionDetails>
                                    <ConnexionStatus
                                        isRunningAppReady={props.isRunningAppReady}
                                        runningAppId={props.runningAppId}
                                        isConnected={props.isConnected}
                                    />
                                </AccordionDetails>
                            </Accordion>
                        </Paper>
                    </Grid>
                </Hidden>
                <Hidden only={['xl', 'lg', 'md']}>
                    <Grid item
                        md={constants.f_column}
                        sm={constants.o_column}
                        xs={constants.o_column}>
                        <Paper className={classes.paper}
                            elevation={constants.nominal_elevation}
                            square>
                            <Accordion square >
                                <AccordionSummary expandIcon={<ExpandMoreIcon />}>
                                    <Typography className={classes.heading}>Swarm Status</Typography>
                                </AccordionSummary>
                                <AccordionDetails>
                                    <SwarmStatus dronesData={props.dronesData} />
                                </AccordionDetails>
                            </Accordion>
                        </Paper>
                    </Grid>
                </Hidden>
                <Grid item
                    xl={constants.t_column}
                    lg={constants.t_column}
                    md={constants.o_column}
                    sm={constants.o_column}
                    xs={constants.o_column}>
                    <Paper className={classes.paper}
                        elevation={constants.nominal_elevation}
                        square={true}>
                        <Accordion square expanded={expanded === 'panelMap'} onChange={handleChange('panelMap')}>
                            <AccordionSummary expandIcon={<ExpandMoreIcon />}>
                                <Typography>Swarm Mapping Environnement</Typography>
                            </AccordionSummary>
                            <AccordionDetails id="Map">
                                <Typography>
                                    <LinearGraph dronesData={props.dronesData} shouldUpdateMap = {props.shouldUpdateMap} shouldResetMap ={props.shouldResetMap}/>
                                </Typography>
                            </AccordionDetails>
                        </Accordion>
                    </Paper>
                </Grid>
                <Grid item
                    lg={constants.t_column}
                    md={constants.o_column}
                    sm={constants.o_column}
                    xs={constants.o_column}>
                    <Paper className={classes.paper}
                        elevation={constants.nominal_elevation}
                        square={true}>
                        <DroneListSection dronesData={props.dronesData} />
                    </Paper>
                </Grid>
                <Grid item xs={constants.o_column}>
                    <Paper className={classes.paper}
                        elevation={constants.nominal_elevation}
                        square={true}>
                        <Accordion square >
                            <AccordionSummary expandIcon={<ExpandMoreIcon />}>
                                <Typography className={classes.heading}>Swarm Console Log</Typography>
                            </AccordionSummary>
                            <AccordionDetails>
                                <Typography>
                                    {JSON.stringify(props.dronesData)}
                                </Typography>
                            </AccordionDetails>
                        </Accordion>
                    </Paper>
                </Grid>
            </Grid>
        </div>
    );
}