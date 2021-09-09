from flask import Blueprint

argosSimulationBluePrint = Blueprint('argosSimulationBluePrint', __name__)

from . import routes
