import '../../App.css';
import "./Home.css";
import { Footer } from "../../Components/Footer/Footer.js";
import { Navbar } from "../../Components/Navbar/Navbar.js";
import { Introduction } from "./Introduction.js";
import Button from '@material-ui/core/Button';
import React from 'react';
import API from '../../API/Socket/API'
import { connectToServer } from '../../API/v1/API';
import { withStyles } from '@material-ui/styles';
import PropTypes from 'prop-types';
import Paper from '@material-ui/core/Paper';
import Grid from '@material-ui/core/Grid';
import * as constants from '../../Constants/constants.js';

class Home extends React.Component {
    constructor(props) {
        super(props)
        this.state = {
            isConnected: false
        }
    }

    componentDidMount() {
        this.initConnection()
    }

    initConnection() {
        connectToServer().then((response) => {
            if (!response) {
                this.handleConnectionError(response)
            }
            else {
                this.setState({
                    isConnected: true
                })
            }
        })
    }

    handleConnectionError(error) {
        if (this.state.isConnected) {
            alert('Erreur lors du traitement, reconnexion au serveur ... ')
            this.setState({
                isConnected: false
            })
        }
        this.initConnection()
    }

    render() {
        document.title = "Swarm Robotics";
        const connexionStatus = this.state.isConnected ? "Server connected" : "Server disconnected"
        const { classes } = this.props;
        return (
            <div>
                <Navbar currentActive="/home" />
                <div className="home">
                    <Grid container spacing={constants.none_space}>
                        <Grid item xs={constants.o_column}>
                            <Paper className={classes.paper}>
                                <p>{connexionStatus}</p>
                            </Paper>
                        </Grid>
                        <Grid item lg={constants.t_column}
                            md={constants.o_column}
                            sm={constants.o_column}
                            xs={constants.o_column}>
                            <Paper className={classes.paper}>
                                <article className="Card">
                                    <h1>ARGoS Simulation</h1>
                                    <div>
                                        <Button variant={constants.contained}
                                            size={constants.size_large}
                                            href={API.nameSpaces.argosSimulation}
                                            disabled={!this.state.isConnected}>
                                            Start the simulation
                                        </Button>
                                    </div>
                                </article>
                            </Paper>
                        </Grid>
                        <Grid item lg={constants.t_column}
                            md={constants.o_column}
                            sm={constants.o_column}
                            xs={constants.o_column}>
                            <Paper className={classes.paper}>
                                <article className="Card">
                                    <h1>Crazyflie Swarm Application </h1>
                                    <div>
                                        <Button variant={constants.contained}
                                            size= {constants.size_large}
                                            href={API.nameSpaces.swarmApp}
                                            disabled={!this.state.isConnected}>
                                            Launch a swarm mission
                                            </Button>
                                    </div>
                                </article>
                            </Paper>
                        </Grid>
                        <Grid item lg={constants.t_column}
                            md={constants.o_column}
                            sm={constants.o_column}
                            xs={constants.o_column}>
                            <Paper className={classes.paper}>
                                <article className="Card">
                                    <h1>DataBase: All Mission Logs</h1>
                                    <div>
                                        <Button variant={constants.contained}
                                            size= {constants.size_large}
                                            href={"http://localhost:5000" + API.appRoutes.getDataBase}
                                            disabled={!this.state.isConnected}>
                                            See All Logs
                                            </Button>
                                    </div>
                                </article>
                            </Paper>
                        </Grid>
                        <Grid item lg={constants.t_column}
                            md={constants.o_column}
                            sm={constants.o_column}
                            xs={constants.o_column}>
                            <Paper className={classes.paper}>
                                <article className="Card">
                                    <h1>DataBase: Last Mission Logs</h1>
                                    <div>
                                        <Button variant={constants.contained}
                                            size= {constants.size_large}
                                            href={"http://localhost:5000" + API.appRoutes.getLastSessionData}
                                            disabled={!this.state.isConnected}>
                                            See last exploration LOGS
                                            </Button>
                                    </div>
                                </article>
                            </Paper>
                        </Grid>
                        
                        <Grid item xs={constants.o_column}>
                            <Paper className={classes.paper}>
                                <Introduction />
                            </Paper>
                        </Grid>
                    </Grid>
                </div>
                <Footer />
            </div>
        );
    }
}

Home.propTypes = {
    classes: PropTypes.object.isRequired,
}

const styles = () => ({
    paper: {
        textAlign: constants.center,
        elevation: constants.second_elevation,
        padding: constants.nominal_padding,
        margin: constants.nominal_margin,
        background: constants.background_light,
    },
});

export default withStyles(styles)(Home);