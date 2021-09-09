import math

def distanceCheck(d):
    if d>0 and d<200:
        d = d/100
    else:
        d = 1000
    return d



#drone=Drone(2,2,34,4,5,6,3)
def mainMappingComputing(data):
    f0 = front(data['front'],data['orientation'],data['positionX'],data['positionY'])
    b0 = back(data['back'],data['orientation'],data['positionX'],data['positionY'])
    l0 = left(data['left'],data['orientation'],data['positionX'],data['positionY'])
    r0 = right(data['right'],data['orientation'],data['positionX'],data['positionY'])
    mappingData = {
        'mappingData':{
            "positionX": data['positionX'],
            "positionY": data['positionY'],
            "frontX": f0[0],
            "frontY": f0[1],
            "backX": b0[0],
            "backY": b0[1],
            "leftX": l0[0],
            "leftY": l0[1],
            "rightX": r0[0],
            "rightY": r0[1],
        }
    }
    print("MAP", mappingData)
    return mappingData



def convertAngles(Θ):
    return math.radians(Θ)

# Compute front obstacle coordinates
def front(d, heading,x,y):
    d = distanceCheck(d)
    radHeading = convertAngles(heading)
    xObstacle = math.sin(radHeading)*(-d) + x
    yObstacle = math.cos(radHeading)*(d) + y
    return [xObstacle,yObstacle]

# Compute front obstacle coordinates
def back(d, heading,x,y):
    d = distanceCheck(d)
    radHeading = convertAngles(heading)
    xObstacle = math.sin(radHeading)*(d) + x
    yObstacle = math.cos(radHeading)*(-d) + y
    return [xObstacle,yObstacle]

# Compute right obstacle coordinates
def right(d, heading,x,y):
    d = distanceCheck(d)
    radHeading = convertAngles(heading)
    xObstacle = math.cos(radHeading)*(d) + x
    yObstacle = math.sin(radHeading)*(d) + y
    return [xObstacle,yObstacle]

# Compute left obstacle coordinates
def left(d, heading,x,y):
    d = distanceCheck(d)
    radHeading = convertAngles(heading)
    xObstacle = math.cos(radHeading)*(-d) + x
    yObstacle = math.sin(radHeading)*(-d) + y
    return [xObstacle,yObstacle]
