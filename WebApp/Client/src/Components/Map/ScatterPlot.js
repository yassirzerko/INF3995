import React from "react"
import { scaleLinear, axisLeft, axisBottom, select } from "d3"
import './Map.css'

const dronesColors = [
  "rgba(255, 0, 0, .9)",
  "rgba(0, 255, 255, 1)",
  "rgba(0, 255, 0, 1)",
  "rgba(0, 0, 255, 1)",
  "rgba(255, 0, 255, 1)",
]

const BLACK_COLOR = "rgba(0, 0, 0, 1)"
const POINT_RAYON = 3
const MAX_WIDTH = 10
const MAX_HEIGHT = 10



export default class ScatterPlot extends React.Component {
  constructor(props) {
    super(props)

    let w = this.MapWidthCondition(window.innerWidth)
    console.log("Width sent to map",w)
    console.log("Window size",window.innerWidth)

    this.margin = { top: 20, right: 15, bottom: 60, left: 25 }
    this.width = w 
    this.height = 600 - this.margin.top - this.margin.bottom
    this.scaleX = scaleLinear()
      .domain([
        0, MAX_WIDTH
      ])
      .range([0, this.width])
    this.scaleY = scaleLinear()
      .domain([
        MAX_HEIGHT, 0
      ])
      .range([0, this.height])
  }

  MapWidthCondition(width) {
    if (width >= 1450)
      width = 700
    else if (width >= 1200 && width < 1450)
      width = 550
    else if (width >= 1150 && width < 1200)
      width = width / 2 - 200
    else
      width = width - 100
    return width
  }

  renderPoint(x, y, color, r) {
    return <g>
      <circle
        cx={this.scaleX(x)}
        cy={this.scaleY(y)}
        r={r}
        style={{ fill: color }}
      />
    </g>
  }

  renderDronesPoints() {
    let points = []
    for (const dronesData of this.props.data) {
      let counter = 0
      for (const droneId in dronesData) {
        const droneData = dronesData[droneId]
        points.push(this.renderPoint(droneData.posX, droneData.posY, dronesColors[counter++], POINT_RAYON))
        points.push(this.renderPoint(droneData.frontX, droneData.frontY, BLACK_COLOR, POINT_RAYON))
        points.push(this.renderPoint(droneData.backX, droneData.backY, BLACK_COLOR, POINT_RAYON))
        points.push(this.renderPoint(droneData.rightX, droneData.rightY, BLACK_COLOR, POINT_RAYON))
        points.push(this.renderPoint(droneData.leftX, droneData.leftY, BLACK_COLOR, POINT_RAYON))
      }
    }
    return points
  }

  render() {
    //let w = this.MapWidthCondition(window.innerWidth)
    const margin = this.margin
    const width   = this.width
    //const width = this.MapWidthCondition(window.innerWidth)
    const height = this.height

    const points = this.renderDronesPoints()

    return (
      <div>
        <svg
          width={width + margin.right + margin.left}
          height={height + margin.top + margin.bottom}
          className="chart"
        >
          <g
            //className="main"
            transform={"translate(" + margin.left + "," + margin.top + ")"}
            width={width}
            height={height}
          >
            {points}
            <Axis
              axis="x"
              transform={"translate(0," + height + ")"}
              scale={axisBottom()
                .ticks(20)
                .tickSize(-height)
                .scale(this.scaleX)}
            />
            <Axis
              axis="y"
              transform="translate(0,0)"
              scale={axisLeft()
                .ticks(20)
                .tickSize(-width)
                .scale(this.scaleY)}
            />
          </g>
        </svg>
      </div>
    )
  }
}

class Axis extends React.Component {
  componentDidMount() {
    const node = this.refs[this.props.axis]
    select(node)
      .call(this.props.scale)
      .selectAll(this.props.ticksSize)

  }

  render() {
    return (
      <g
        className="main date y x "
        transform={this.props.transform}
        ref={this.props.axis}
      />
    )
  }
}
