import React, { Component } from 'react';
import  {MenuItems} from "./MenuItems";
import logo from "../../Assets/swarm.svg";
import './Navbar.css'

export class Navbar extends Component {
    state={ clicked: false}

    handleClick = () => {
        this.setState({clicked: !this.state.clicked})
    }

    render(){
        return (
            <nav className="NavbarItems">
                    <a href="/"><img className="navbar-logo-other" alt="logo" src={logo} title="Minimal Swarm Drone Navigation System" /></a>
                    <a href="/"><h1 className="navbar-logo">Minimal Drone Swarm Navigation System</h1></a>
                    <a href="/"><img className="navbar-logo-mobile" alt="logo" src={logo} title="Minimal Swarm Drone Navigation System" /></a>
                <div className="menu-icon" onClick={this.handleClick}>
                    <i className={this.state.clicked ? 'fas fa-times': 'fas fa-bars'}></i>
                </div>
                <ul className={this.state.clicked ? 'nav-menu active': 'nav-menu'}>
                    {MenuItems.map((item,index)=>{
                        return (
                        <li key={index}>
                            <a className={item.cName} href={item.url} >
                                {item.title}
                            </a>
                        </li>
                        )
                    })}
                </ul>
            </nav>
        )
    }
}

export default Navbar