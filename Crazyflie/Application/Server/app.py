from flask import Flask, jsonify
from flask import request
from flask_cors import CORS
import subprocess

app = Flask(__name__)
CORS(app)
loadProc = None

@app.route('/buildCode')
def buildCode():
    retrunCode = subprocess.run(
        'cd .. && make all', universal_newlines=True, stderr=subprocess.PIPE, shell=True)
    return jsonify(retrunCode.stderr == '')


@app.route('/softwareUpdate')
def softwareUpdate():
    global loadProc
    index = request.args.get('index')
    baseURI = 'radio://0/56/2M/E7E7E7E70'
    crazyFlieId = f's{index}'
    loadCommand = ['python3', '-m', 'cfloader',
                   'flash', '../cf2.bin', 'stm32-fw', '-w']
    uri = f'{baseURI}{index}'
    loadCommand.append(uri)
    loadProc = subprocess.Popen(
        loadCommand,
        universal_newlines=True)
    return jsonify(True)


@app.route('/getReturnCode')
def getReturnCode():
    global loadProc
    try:
        loadTimeout = 1.0
        returnCode = loadProc.communicate(timeout=loadTimeout)
        return jsonify(True)
    except subprocess.TimeoutExpired:
        loadProc.kill()
        return jsonify(False)


if __name__ == "__main__":
    app.run(debug=True, host='0.0.0.0', port=4000)
