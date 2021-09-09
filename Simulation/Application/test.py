#Server
from flask import Flask, request, jsonify
from flask_cors import CORS
from flask_socketio import SocketIO, send, emit
import time, threading


#Server and socket configuration 
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
CORS(app)
socket = SocketIO(app, cors_allowed_origins = "*")
counter = 0

def ack():
    print('message was received!')

@socket.on("connect")
def connect() :
    print('Connected')

@socket.on("disconnect")
def disconnect() :
    print('disconnect')

@socket.on("connected")
def connected(message) :
    print('Connection Established!')
    time.sleep(3)
    socket.emit('command', message, callback=ack)

@socket.on("regularUpdate")
def dataUpdate(data) :
    global counter
    counter += 1
    print('Data received at ',  counter, 's')
    print(data)

@socket.on_error()
def error_handler(e) :
    print("Error :", e)

if __name__ == '__main__':
    socket.run(app, host = '0.0.0.0', debug = True)
    
