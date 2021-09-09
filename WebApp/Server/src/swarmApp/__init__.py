from flask import Blueprint

swarmBluePrint = Blueprint('swarmBluePrint', __name__)

from . import routes