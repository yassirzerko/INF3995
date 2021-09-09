import React from 'react'
import PropTypes from 'prop-types';
import Grid from '@material-ui/core/Grid'


class DroneCard extends React.Component {
    constructor(props) {
        super(props);
    }

    setDel(turnOn) {
        this.props.setDel(3, turnOn)
    }


    render() {
        let batteryLevel
        if (this.props.powerLevel) {
            batteryLevel = this.props.powerLevel < 4.0 ? this.props.powerLevel : 4.0
        }
        return (
            <Grid container style={{ borderStyle: "solid", marginLeft: "10%" }}>
                <Grid item xs={12}> Numero du drone : {this.props.id}</Grid>
                <Grid item xs={12}> Niveau de batterie (V) : {
                    //this.props.powerLevel ? this.props.powerLevel.toFixed(2) : ' - '
                }</Grid>
                <Grid item xs={12}> Niveau de batterie (%): {
                    this.props.powerLevel ? (batteryLevel).toFixed(2) * 100 : ' - ' 
                }</Grid>
                <Grid item xs={12}> <button onClick={() => this.setDel(true)}>Allumer la led</button></Grid>
                <Grid item xs={12}> <button onClick={() => this.setDel(false)}>Eteindre la led </button></Grid>



            </Grid>

        );
    }
}


DroneCard.propTypes = {
    setDel: PropTypes.func,
    id: PropTypes.string,
    powerLevel: PropTypes.string,
    ledOn: PropTypes.bool
}

export default DroneCard;