import React from 'react';
import Table from '@material-ui/core/Table';
import TableBody from '@material-ui/core/TableBody';
import TableCell from '@material-ui/core/TableCell';
import TableHead from '@material-ui/core/TableHead';
import TableRow from '@material-ui/core/TableRow';
import './SwarmStatus.css';
import { getDroneState } from '../../API/Socket/Utils'

function swarmStatus(status) {
    return { status }
}

function missionStatus(status) {
    return { status }
}

export default function SwarmStatus(props) {
    let status = 'DISCONNECTED'
    let droneNumber = 0
   
    if (props.dronesData && props.dronesData.swarm) {
        status = getDroneState(props.dronesData.swarm.state) 
        droneNumber = props.dronesData.swarm.nDrones
        if(droneNumber == 0) {
            status = "DISCONNECTED"
        }
    }
    let row1 = [
        swarmStatus(status),

    ];
    let row2 = [
        missionStatus(droneNumber),
    ];

    return (
        <Table className="SwarmStatusTable" size="small" aria-label="a dense table">
            <TableHead>
                <TableRow>
                    <TableCell align="center">Swarm Status</TableCell>
                </TableRow>
            </TableHead>
            <TableBody>
                {row1.map((row) => (
                    <TableRow>
                        <TableCell align ="center" >{row.status}</TableCell>
                    </TableRow>
                ))}
            </TableBody>
        <TableHead>
            <TableRow>
                <TableCell align="center">Number of drones</TableCell>
            </TableRow>
        </TableHead>
        <TableBody>
             {row2.map((row) => (
                <TableRow>
                    <TableCell align="center" >{row.status}</TableCell>
                </TableRow>
            ))}
        </TableBody>
    </Table>

    );
}
