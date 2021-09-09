from flask import Flask
from flask_socketio import SocketIO
from flask_cors import CORS
from src.API.API import NameSpaces
from tinydb import TinyDB

socket = SocketIO(cors_allowed_origins = "*")
db = TinyDB('db.json')

def create_app(debug = True):
    app = Flask(__name__)
    app.config['SECRET_KEY'] = 'secret!'
    app.config['JSON_SORT_KEYS'] = False
    CORS(app)

    from .simulationApp import argosSimulationBluePrint
    app.register_blueprint(argosSimulationBluePrint, url_prefix = NameSpaces.argosSimulation)

    from .main import mainBluePrint 
    app.register_blueprint(mainBluePrint)

    from .swarmApp import swarmBluePrint
    app.register_blueprint(swarmBluePrint, url_prefix = NameSpaces.swarmApp)

    socket.init_app(app, host = '0.0.0.0', debug = debug)           
    return app
    