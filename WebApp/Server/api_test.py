import unittest

from flask_socketio import SocketIO

import pytest
from src import create_app
from src.simulationApp.routes import appManager


class TestSocket(unittest.TestCase):

    @classmethod
    def setUpClass(self):
        self.app = create_app()
        self.socketio = SocketIO(self.app)

    def test_connect(self):
        client = self.socketio.test_client(self.app)
        client2 = self.socketio.test_client(self.app)
        self.assertTrue(client.is_connected())
        self.assertTrue(client2.is_connected())
        self.assertNotEqual(client.eio_sid, client2.eio_sid)
        client.disconnect()
        self.assertFalse(client.is_connected())

    ###################### For Index #################
    # check for response 200
    def test_index(self):
        tester = self.app.test_client(self)
        response = tester.get("/")
        statuscode = response.status_code
        self.assertEqual(statuscode, 200)

        # check the content
    def test_index_content(self):
        tester = self.app.test_client(self)
        response = tester.get("/")
        self.assertEqual(response.content_type, "application/json")

    ############################ For Argo simultaion #################
    # check the content

    def test_argosSimulation_content(self):
        tester = self.app.test_client(self)
        response = tester.get("/argosSimulation")
        self.assertEqual(response.content_type, "text/html; charset=utf-8")

     ########################### For Swarm APP ############

        ################### For Get Database #############
    # check for response 200

    def test_getDataBase(self):
        tester = self.app.test_client(self)
        response = tester.get("/getDataBase")
        statuscode = response.status_code
        self.assertEqual(statuscode, 200)

    # check the content

    def test_getDataBase_content(self):
        tester = self.app.test_client(self)
        response = tester.get("/getDataBase")
        self.assertEqual(response.content_type, "application/json")

        ################## For Reset Database #####################
    # check for response 200

    def test_resetDataBase(self):
        tester = self.app.test_client(self)
        response = tester.get("/resetDataBase")
        statuscode = response.status_code
        self.assertEqual(statuscode, 200)

    # check the content
    def test_resetDataBase_content(self):
        tester = self.app.test_client(self)
        response = tester.get("/resetDataBase")
        self.assertEqual(response.content_type, "application/json")

        ###############For Last session data ##################
    # check for response 200

    def test_getLastSessionData(self):
        tester = self.app.test_client(self)
        response = tester.get("/getLastSessionData")
        statuscode = response.status_code
        self.assertEqual(statuscode, 200)

    # check the content
    def test_getLastSessionData_content(self):
        tester = self.app.test_client(self)
        response = tester.get("/getLastSessionData")
        self.assertEqual(response.content_type, "application/json")


if __name__ == '__main__':

    unittest.main()
