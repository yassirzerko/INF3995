import React, { useEffect } from 'react';
import './ControlHeader.css';
import { Controls } from '../Controls/Controls.js'
import * as math from '../../Constants/math.js'

export function ControlHeader(props) {
    const [scrolled, setScrolled] = React.useState(false);
    const handleScroll = () => {
        const offset = window.scrollY;
        if (offset > math.zero) {
            setScrolled(true);
        }
        else {
            setScrolled(false);
        }
    }
    useEffect(() => {
        window.addEventListener('scroll', handleScroll)
    })
    let controlheaderClasses = ['navbar'];
    if (scrolled) {
        controlheaderClasses.push('scrolled');
    }
    return (
        <header className={controlheaderClasses.join(" ")}>
                <Controls 
                    isConnected = {props.isConnected} 
                    isRunningAppReady = {props.isRunningAppReady} 
                    sendCommand = {props.sendCommand} 
                    onChangeNDrones = {props.onChangeNDrones}
                    startApp = {props.startApp} 
                    stopApp = {props.stopApp}
                    softwareUpdate = {props.softwareUpdate}
                    runningAppId = {props.runningAppId}
                    dronesData = {props.dronesData}
                    nDrones = {props.nDrones}/>
        </header>
    )
}
