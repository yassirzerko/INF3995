import { BrowserRouter as Router, Switch, Route } from "react-router-dom"
import  Operator  from "./Pages/Operator/Operator.js";
import Home from "./Pages/Home/Home.js"
import React from 'react';
import "./App.css";
import API from "../src/API/Socket/API"
import UserGuide from "./Pages/UserGuide/UserGuide.js"

function App() {
  return (
    <Router>
      <Switch>
        <Route path=  {API.nameSpaces.swarmApp}> <Operator nameSpace = {API.nameSpaces.swarmApp}/></Route>
        <Route path= {API.nameSpaces.argosSimulation}> <Operator nameSpace = {API.nameSpaces.argosSimulation}/></Route>
        <Route path= "/about"> <UserGuide /></Route>
        <Route path= "/"> <Home /> </Route>
      </Switch>
    </Router>
    

  );
}

export default App;
