import {getResponseData}  from './Utils'

const API = "http://0.0.0.0:5000"

async function connectToServer() {
    const url = API
    return getResponseData(url)
}

//radioFound que pour tester
async function initRadioConnection() {
    const url = API + "/initRadioConnection"
    return getResponseData(url)
}

async function startSimulation () {
    const url = API+'/startSimulation'
    return getResponseData(url)
}

async function setDel(delId, turnOn) {
    const url = API+"/setDel?" + `delId=${delId}&turnOn=${turnOn}`
    return getResponseData(url)
}

async function disconnectDrones() {
    const url = API +"/disconnectDrones"
    return getResponseData(url)
}

async function getState() {
    const url = API + "/getState"
    return getResponseData(url)
}

export {connectToServer, startSimulation, setDel, initRadioConnection, disconnectDrones, getState}