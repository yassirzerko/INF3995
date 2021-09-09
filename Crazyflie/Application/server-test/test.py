"""
Simple example that connects to the first Crazyflie found, Sends commands and
receive responses

The protocol is:
 - 1 usigned short that represents the id of the command
 - The Crazyflie sends back a float
"""
import logging
import time
import sys
from threading import Thread

import struct

import cflib
from cflib.crazyflie import Crazyflie

logging.basicConfig(level=logging.ERROR)


class DroneController:

    def __init__(self, link_uri):
        """ Initialize and run the example with the specified link_uri """

        self._cf = Crazyflie()

        self._cf.connected.add_callback(self._connected)
        self._cf.disconnected.add_callback(self._disconnected)
        self._cf.connection_failed.add_callback(self._connection_failed)
        self._cf.connection_lost.add_callback(self._connection_lost)

        self._cf.appchannel.packet_received.add_callback(self._app_packet_received)

        self._cf.open_link(link_uri)

        print('Connecting to %s' % link_uri)

    def _connected(self, link_uri):
        """ This callback is called form the Crazyflie API when a Crazyflie
        has been connected and the TOCs have been downloaded."""
        # Start a separate thread to do the motor test.
        self._test_appchannel(4)

    def _connection_failed(self, link_uri, msg):
        """Callback when connection initial connection fails (i.e no Crazyflie
        at the specified address)"""
        print('Connection to %s failed: %s' % (link_uri, msg))

    def _connection_lost(self, link_uri, msg):
        """Callback when disconnected after a connection has been made (i.e
        Crazyflie moves out of range)"""
        print('Connection to %s lost: %s' % (link_uri, msg))

    def _disconnected(self, link_uri):
        """Callback when the Crazyflie is disconnected (called in all cases)"""
        print('Disconnected from %s' % link_uri)

    def _app_packet_received(self, data):
        (success, ) = struct.unpack("<f", data)
        print(f"Response Received : ", success)

    def _test_appchannel(self, command):
        data = struct.pack("<H", command)
        self._cf.appchannel.send_packet(data)
        print(f"Command Sent!")

if __name__ == '__main__':
    # Initialize the low-level drivers (don't list the debug drivers)
    cflib.crtp.init_drivers(enable_debug_driver=False)
    #controller = DroneController('radio://0/80/2M/E7E7E7E7E2')
    controller = DroneController('radio://0/80/2M/E7E7E7E7E7')
    pause = False
    while not pause :
        val = input("Type something\n")
        if val == 'T' :
            controller._test_appchannel(1)
        if val == 'L' :
            controller._test_appchannel(2)
        if val == 'ON' :
            controller._test_appchannel(6)
        if val == 'OFF' :
            controller._test_appchannel(7)
        if val == 'D' :
            controller._test_appchannel(0)
            controller._cf.close_link()
            pause = True
