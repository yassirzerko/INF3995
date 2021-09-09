import './UserGuide.css'
import '../../App.css';
import { Footer } from "../../Components/Footer/Footer.js"
import { Navbar } from "../../Components/Navbar/Navbar.js"
import "./UserGuide.css"
import Button from '@material-ui/core/Button';
import React from 'react'
import Paper from '@material-ui/core/Paper';
import Grid from '@material-ui/core/Grid';
import * as constants from '../../Constants/constants.js';
import { withStyles } from '@material-ui/styles';
import InitialCommands from "../../Assets/SwarmCommands.png"


class UserGuide extends React.Component {

  render() {
    document.title = "Swarm Robotics - User Manual";
    const { classes } = this.props;
    return (
      <div>
        <Navbar currentActive="/user-manual" />
        <div className="UserGuide" currentActive="/user-manual">
          <h2>How to use the minimal drone navigation system ?</h2>
          <div className="Explanation">
            <p>This is a prototype for a minimal drone swarm navigation system for swarms of tiny
            flying drones using ARGoS simulation engine or Crazyflies with the Bitcraze Radio PA.
            Our prototype aims to demonstrate the great potential for exploring unknown,
            indoor environments. Tiny flying robots, like the Crazyflie, can move in narrow spaces,
            and their light weight makes them safe for operating around humans.
            The absence of external infrastructure implies that any positioning attempts must be
            performed by the robots themselves.State-of-the-art solutions, such as simultaneous
            localization and mapping, are still too resource demanding. This prototype uses a simpler version of the
            swarm gradient bug algorithm (SGBA), a minimal navigation solution that allows a swarm
            of tiny flying robots to autonomously explore an unknown environment and subsequently
            come back to the departure point. SGBA maximizes coverage by having robots travel in different
            directions away from the departure point. The robots navigate the environment and deal with
            static obstacles on the fly by means of visual odometry and wall-following behaviors.
          </p>
            <br></br>
            <p>
              To test our prototype, we enable the operator to choose between an ARGoS Simulation by clicking the
              start the simulation button or to choose to operate real life drones by clicking the Launch a swarm mission
              button. The user can also choose to consult previous logs of missions trough our databse.
          </p>
            <br></br>
            <p>
              The application was built by our team for the INF3995 course to illustrate by a proof-of-concept an exploration mission
          in which a swarm of crazyflies explore an unknow environnement and map it.</p>
            <Grid container spacing={constants.none_space}>
              <Grid item lg={constants.th_column}
                md={constants.o_column}
                sm={constants.o_column}
                xs={constants.o_column}>
                <Paper className={classes.paper}>
                  <article className="Card">
                    <h1>Gitlab code repository</h1>
                    <div>
                      <Button variant={constants.contained}
                        size={constants.size_large} href={"https://www.youtube.com/watch?v=sV4BOLxrwaU"}
                        target={"_blank"}>
                        Checkout our Gitlab repository
                    </Button>
                    </div>
                  </article>
                </Paper>
              </Grid>
              <Grid item lg={constants.th_column}
                md={constants.o_column}
                sm={constants.o_column}
                xs={constants.o_column}>
                <Paper className={classes.paper}>
                  <article className="Card">
                    <h1>Crazyflie Swarm Application Example </h1>
                    <div>
                      <Button variant={constants.contained}
                        size={constants.size_large} href={"https://www.youtube.com/watch?v=5XKBV-7i9_0&t=3s"}
                        target={"_blank"}>
                        Watch Exploration video
                    </Button>
                    </div>
                  </article>
                </Paper>
              </Grid>
              <Grid item lg={constants.th_column}
                md={constants.o_column}
                sm={constants.o_column}
                xs={constants.o_column}>
                <Paper className={classes.paper}>
                  <article className="Card">
                    <h1>ARGoS Simulation Video Example </h1>
                    <div>
                      <Button variant={constants.contained}
                        size={constants.size_large}
                        href={"https://www.youtube.com/watch?v=sV4BOLxrwaU"}
                        target={"_blank"}>
                        Wacth ARGoS simulation video
                    </Button>
                    </div>
                  </article>
                </Paper>
              </Grid>
            </Grid>
          </div>
          <div className="Explanation">
            <h2>Understanding the commands of the operator user interface</h2>
            <div className="Explanation">
              <Grid container spacing={constants.none_space}>
                <Grid item lg={constants.t_column}
                  md={constants.o_column}
                  sm={constants.o_column}
                  xs={constants.o_column}>
                  <p> To control the swarm of drones in the ARGoS simulation, 8 commands are at your disposal:</p>
                  <div class="liste">
                    <ul>
                      <li><strong>Start Mission</strong></li>
                      <p>This button enables a mission for the swarm. </p>
                      <br></br>
                      <li><strong>Return to Base</strong></li>
                      <p>This button sends a command to the drones to return to it initial position when the take-off button was clicked.</p>
                      <br></br>
                      <li><strong>Take-off</strong></li>
                      <p>This button makes the drone hover at a certain position.</p>
                      <br></br>
                      <li><strong>Land</strong></li>
                      <p>This button makes the drone land at their current position.</p>
                      <br></br>
                      <li><strong>Reset App</strong></li>
                      <p>This button restarts the app and drones.</p>
                      <br></br>
                      <li><strong>Start App</strong></li>
                      <p>This button starts the app with the correct number of drones.</p>
                      <br></br>
                      <li><strong>Select drone count</strong></li>
                      <p>This button communicates with the ARGoS simulation engine to provide the number of drones that will
                        take part in the simulation.
                      </p>
                      <br></br>
                      <li><strong>Software update</strong></li>
                      <p> This button is only made available for the crazyflie to re-flash it's firmware. </p>
                      <br></br>
                    </ul>
                  </div>
                </Grid>
                <Grid item lg={constants.t_column}
                  md={constants.o_column}
                  sm={constants.o_column}
                  xs={constants.o_column}>
                  <div>
                    <img src={InitialCommands} alt='Initial Swarm Commands state' class="responsive" />
                  </div>
                </Grid>

              </Grid>
            </div>
            <p>

            </p>
          </div>
        </div >
        <Footer />
      </div>
    );
  }
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

export default withStyles(styles)(UserGuide);

