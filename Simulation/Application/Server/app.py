from flask import Flask, jsonify
from flask import request
from flask_cors import CORS
import subprocess
import sys
import random
import os
import signal


app = Flask(__name__)
CORS(app)

LAUNCH_SCRIPT = "../launch.sh"
MAX_SEED = 1000
process = None


@app.route('/startSimulation')
def startSimulation():
    global process
    nDrones = request.args.get('nDrones')
    batterySeed = random.random() * MAX_SEED
    try:
        returnCode = subprocess.call(
            ['sh', LAUNCH_SCRIPT, str(nDrones), str(batterySeed)], timeout=3.0)
    except subprocess.TimeoutExpired:
        return jsonify(False)
    process = subprocess.Popen('cd .. && argos3 -c experiments/crazyflie_controlling.argos',
                               preexec_fn=os.setsid,
                               shell=True)
    return jsonify(True)


@app.route('/stopSimulation')
def stopSimulation():
    global process
    try:
        process.communicate(timeout=1.0)
        return jsonify(False)
    except subprocess.TimeoutExpired:
        os.killpg(os.getpgid(process.pid), signal.SIGTERM)
        process.kill()
        return jsonify(True)


if __name__ == "__main__":
    app.run(debug=True, host='0.0.0.0', port=2000)
