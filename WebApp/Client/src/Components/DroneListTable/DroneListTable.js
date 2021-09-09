import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import Paper from '@material-ui/core/Paper';
import Table from '@material-ui/core/Table';
import TableBody from '@material-ui/core/TableBody';
import TableCell from '@material-ui/core/TableCell';
import TableContainer from '@material-ui/core/TableContainer';
import TableHead from '@material-ui/core/TableHead';
import TableRow from '@material-ui/core/TableRow';
import { getDroneState } from '../../API/Socket/Utils'

const columns = [
  { id: 'id', label: 'Drone ID', width:'100%' },
  { id: 'status', label: 'Drone Status'},
  {
    id: 'battery',
    label: 'Battery Level (%)',
    align:'center',
  },
  {
    id: 'speed',
    label: 'Speed (m/s)',
    align: 'right',
  },
];

const createRow = (id, status, battery, speed) => {
  return {id, status, battery, speed}
} 

const useStyles = makeStyles({
  root: {
    width: '100%',
    display: "flex",
  },
  container: {
    maxHeight: 440,
    width: '100%',
  },
  paper:{
    display: "flex",
    width: '100%',
    flexShrink: 0,
    
  },
});

export default function StickyHeadTable(props) {
  const classes = useStyles();
  const [page, setPage] = React.useState(0);
  const [rowsPerPage, setRowsPerPage] = React.useState(10);

  
  let rows = [];
  let dataToDisplay = props.dronesData.drones ? props.dronesData.drones : {}
  for (let droneId in dataToDisplay) {
    const state = dataToDisplay[droneId]['state']
    const batteryLevel = dataToDisplay[droneId]['batteryLevel']
    const velocityX = dataToDisplay[droneId]['velocityX']
    const velocityY = dataToDisplay[droneId]['velocityY']
    const velocity = velocityX !== undefined && velocityY !== undefined ? Math.sqrt(Math.pow(velocityX, 2) + Math.pow(velocityY, 2)) : '-'
    rows.push(createRow(droneId, getDroneState(state), batteryLevel, velocity))
  }
  
  return (
    <Paper className={classes.root}>
      <TableContainer className={classes.container}>
        <Table>
          <TableHead>
            <TableRow>
              {columns.map((column) => (
                <TableCell
                  key={column.id}
                  align={column.align}
                  style={{ minWidth: column.minWidth }}
                >
                  {column.label}
                </TableCell>
              ))}
            </TableRow>
          </TableHead>
          <TableBody>
            {rows.slice(page * rowsPerPage, page * rowsPerPage + rowsPerPage).map((row) => {
              return (
                <TableRow hover role="checkbox" tabIndex={-1} key={row.code}>
                  {columns.map((column) => {
                    const value = row[column.id];
                    return (
                      <TableCell key={column.id} align={column.align}>
                        {column.format && typeof value === 'number' ? column.format(value) : value}
                      </TableCell>
                    );
                  })}
                </TableRow>
              );
            })}
          </TableBody>
        </Table>
      </TableContainer>
    </Paper>
  );
}