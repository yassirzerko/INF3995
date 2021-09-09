import React from 'react';
import Table from '@material-ui/core/Table';
import TableBody from '@material-ui/core/TableBody';
import TableCell from '@material-ui/core/TableCell';
import TableHead from '@material-ui/core/TableHead';
import TableRow from '@material-ui/core/TableRow';
import './DroneStatusSummary.css'

function droneStatus(status, qt) {
    return { status, qt }
}

const column1 = [
    droneStatus('Ready', '-'),
    droneStatus('Flying', '-'),
    droneStatus('Landing', '-')
];
const column2 = [
    droneStatus('Return to base', '-'),
    droneStatus('Crashed', '-'),
    droneStatus('Updating', '-')
];

export default function DroneStatusTable() {
    return (
        <div className="row">
            <div className="column">
                <Table size="small" aria-label="a dense table">
                    <TableHead>
                        <TableRow>
                            <TableCell>Drone Status</TableCell>
                            <TableCell align="left">#</TableCell>
                        </TableRow>
                    </TableHead>
                    <TableBody>
                        {column1.map((row) => (
                            <TableRow>
                                <TableCell >{row.status}</TableCell>
                                <TableCell align="left">{row.qt}</TableCell>
                            </TableRow>
                        ))}
                    </TableBody>
                </Table>
            </div>
            <div className="column">
                <Table size="small" aria-label="a dense table">
                    <TableHead>
                        <TableRow>
                            <TableCell>Drone Status</TableCell>
                            <TableCell align="left">#</TableCell>
                        </TableRow>
                    </TableHead>
                    <TableBody>
                        {column2.map((row) => (
                            <TableRow>
                                <TableCell >{row.status}</TableCell>
                                <TableCell align="left">{row.qt}</TableCell>
                            </TableRow>
                        ))}
                    </TableBody>
                </Table>
            </div>
        </div>
    );
}
