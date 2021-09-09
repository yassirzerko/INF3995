import './Home.css';

export function Introduction() {
  return (
    <div className="Introduction">
      <h2>How to use the minimal drone navigation system ?</h2>
      <div className="Intro-content">
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
      </div>
    </div >
  );
}
