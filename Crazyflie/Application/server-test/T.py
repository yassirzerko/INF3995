from cflib.drivers.crazyradio import Crazyradio
import time

cr = Crazyradio()

cr.set_channel(56)
cr.set_data_rate(cr.DR_2MPS)

while True:
    val = input("Type something\n")
    if val == 'T' : 
        command = 0x01
    if val == 'L' : 
        command = 0x02
    if val == 'E' : 
        command = 0x08
    
    # Send multicast packet to P2P port 7
    cr.set_address((0xff,0xe7,0xe7,0xe7,0xe7))
    #cr.set_ack_enable(True)
    cr.send_packet( (0xff, 0x80, 0x63, command) )
    time.sleep(0.01)