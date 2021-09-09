import React from "react"
import ScatterPlot from "./ScatterPlot.js"

export default class LinearGraph extends React.Component {
    constructor(props) {
        super(props)
        this.state = {
            data: []
        }
        this.startDataGeneration = this.startDataGeneration.bind(this)
    }

    componentDidMount() {
        this.setState({data: []})
        this.startDataGeneration()
    }

    componentDidUpdate(prevProps) {
        if (this.props.dronesData !== prevProps.dronesData) {
          this.startDataGeneration();
        }
      }

    // Configuration des donnees
    startDataGeneration() {
        if (this.props.dronesData === 'None' || this.props.shouldResetMap) {
            this.setState({data: []})
            return
        }
        let newPoint = [];
        for (const droneId in this.props.dronesData['drones']) {
            newPoint.push({
                posX    : this.props.dronesData['drones'][droneId]['positionX'],
                posY    : this.props.dronesData['drones'][droneId]['positionY'],
                frontX  : this.props.dronesData['drones'][droneId]['frontX'],
                frontY  : this.props.dronesData['drones'][droneId]['frontY'],
                backX   : this.props.dronesData['drones'][droneId]['backX'],
                backY   : this.props.dronesData['drones'][droneId]['backY'],
                rightX  : this.props.dronesData['drones'][droneId]['rightX'],
                rightY  : this.props.dronesData['drones'][droneId]['rightY'],
                leftX   : this.props.dronesData['drones'][droneId]['leftX'],
                leftY   : this.props.dronesData['drones'][droneId]['leftY']
            })
        }
        this.setState({ data: [...this.state.data, newPoint] })
    }

    render() {
        return <ScatterPlot data={this.state.data} />
    }
}
