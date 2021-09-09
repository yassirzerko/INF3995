from flask import Blueprint

mainBluePrint = Blueprint('mainBluePrint', __name__)

from . import routes
