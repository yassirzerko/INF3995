import math

DEFAULT_DISTANCE = 10000
TWO_PI = 360


def mapGenerateData(dronesData, argos):
    generatedData = dict()
    for key in dronesData:
        data = dronesData[key]
        frontObstacle = getFrontObstaclePos(data["front"], data["yaw"],
                                            data["positionX"], data["positionY"], argos)
        backObstacle = getBackObstaclePos(data["back"], data["yaw"],
                                          data["positionX"], data["positionY"], argos)
        leftObstacle = getLeftObstaclePos(data["left"], data["yaw"],
                                          data["positionX"], data["positionY"], argos)
        rightObstacle = getRightObstaclePos(data["right"], data["yaw"],
                                            data["positionX"], data["positionY"], argos)
        generatedData[key] = getGeneratedData(
            data, frontObstacle, backObstacle, leftObstacle, rightObstacle)
    return generatedData

# Compute front obstacle coordinates
def getFrontObstaclePos(distance, heading, x, y, argos):
    frontAngle = 0
    if argos:
        return computeArgosObstacles(distance, heading, x, y, [-1, 1])
    return computeObstaclePosition(distance, heading, x, y, frontAngle)

# Compute front obstacle coordinates
def getBackObstaclePos(distance, heading, x, y, argos):
    backAngle = math.pi
    if argos:
        return computeArgosObstacles(distance, heading, x, y, [1, -1])
    return computeObstaclePosition(distance, heading, x, y, backAngle)

# Compute right obstacle coordinates
def getRightObstaclePos(distance, heading, x, y, argos):
    rightAngle = 3*math.pi/2
    if argos:
        return computeArgosObstacles(distance, heading, x, y, [1, 1])
    return computeObstaclePosition(distance, heading, x, y, rightAngle)

# Compute left obstacle coordinates
def getLeftObstaclePos(distance, heading, x, y, argos):
    leftAngle = math.pi/2
    if argos:
        return computeArgosObstacles(distance, heading, x, y, [-1, -1])
    return computeObstaclePosition(distance, heading, x, y, leftAngle)


def normalizeAngle(angle):
    if angle < 0:
        angle += TWO_PI
    return math.radians(angle)


def computeObstaclePosition(distance, yaw, x, y, angle):
    if not distance or not yaw or not x or not y:
        return [DEFAULT_DISTANCE, DEFAULT_DISTANCE]

    minDistanceThreshold = 0
    maxDistanceThreshold = 10

    if distance < minDistanceThreshold or distance > maxDistanceThreshold:
        return [DEFAULT_DISTANCE, DEFAULT_DISTANCE]

    radYaw = normalizeAngle(yaw) + angle
    xObstacle = math.cos(radYaw)*(distance) + x
    yObstacle = math.sin(radYaw)*(distance) + y
    return [xObstacle, yObstacle]


def computeArgosObstacles(distance, heading, x, y, coef):
    minDistanceThreshold = 0
    maxDistanceThreshold = 500
    divFactor = 100
    if distance > minDistanceThreshold and distance < maxDistanceThreshold:
        distance /= divFactor
    else:
        return [DEFAULT_DISTANCE, DEFAULT_DISTANCE]
    radHeading = math.radians(heading)
    if coef[0] == coef[1]:  # If right or left
        xObstacle = distance * math.cos(radHeading) * coef[0] + x
        yObstacle = distance * math.sin(radHeading) * coef[1] + y
    else:
        xObstacle = distance * math.sin(radHeading) * coef[0] + x
        yObstacle = distance * math.cos(radHeading) * coef[1] + y
    return [xObstacle, yObstacle]


def getGeneratedData(data, frontObstacle, backObstacle, leftObstacle, rightObstacle):
    return {
        "positionX": data["positionX"],
        "positionY": data["positionY"],
        "velocityX": data["velocityX"],
        "velocityY": data["velocityY"],
        "state": data["state"],
        "batteryLevel": data["batteryLevel"],
        "frontX": frontObstacle[0],
        "frontY": frontObstacle[1],
        "backX": backObstacle[0],
        "backY": backObstacle[1],
        "leftX": leftObstacle[0],
        "leftY": leftObstacle[1],
        "rightX": rightObstacle[0],
        "rightY": rightObstacle[1]
    }
