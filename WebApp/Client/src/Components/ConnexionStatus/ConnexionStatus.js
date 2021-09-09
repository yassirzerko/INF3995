import React from 'react';
import Table from '@material-ui/core/Table';
import TableBody from '@material-ui/core/TableBody';
import TableCell from '@material-ui/core/TableCell';
import TableHead from '@material-ui/core/TableHead';
import TableRow from '@material-ui/core/TableRow';
import API from '../../API/Socket/API.js';


function connexionStatus(name, status) {
    return { name, status };
}

const rows = [
    connexionStatus('Server', 'Connected'),
    connexionStatus('RadioPA', 'Disconnected'),
    connexionStatus('ARGoS', 'Connected'),
]

export default function ConnexionStatus(props) {

    return (
        <Table size="small" aria-label="a dense table">
            <TableHead>
                <TableRow>
                    <TableCell>Connexion</TableCell>
                    <TableCell align="right">Status</TableCell>
                </TableRow>
            </TableHead>
            <TableBody>
                <TableRow>
                    <TableCell component="th" scope="row">
                        {'Server'}
                    </TableCell>
                    <TableCell align="right">{props.isConnected ? 'Connected' : 'Disconnected'}</TableCell>
                </TableRow>
                <TableRow>
                    <TableCell component="th" scope="row">
                        {props.runningAppId == API.appsId.simulationApp ? 'ARGoS Simulationtion' : 'Crazyflie Swarm Application'}
                    </TableCell>
                    <TableCell align="right">{props.isRunningAppReady ? 'Ready' : 'Not Ready'}</TableCell>
                </TableRow>
            </TableBody>
        </Table>
    );
}
