import argparse
import math
import numpy as np
from pythonosc import dispatcher
from pythonosc import osc_server
import serial
import time

#set up serial output on port 9600
serout = serial.Serial()
serout.port = 'COM3'


def eeg_handler(unused_addr, args, ch1, ch2, ch3, ch4):
    print("EEG (uV) per channel: ", ch1, ch2, ch3, ch4)
    #right = ch1 + ch2
    #left = ch3 + ch4
    right = ch2
    left = ch4


    if (right>left):
        print("Right is larger")
        serout.write(1) #1 if right larger
    elif (right<left):
        print("Left is larger")
        serout.write(0) #0 if left larger
    else:
        print ("theyre both the same")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--ip",
                        default="127.0.0.1",
                        help="The ip to listen on")
    parser.add_argument("--port",
                        type=int,
                        default=7000,
                        help="The port to listen on")
    args = parser.parse_args()

    dispatcher = dispatcher.Dispatcher()
    dispatcher.map("/debug", print)
    dispatcher.map("/muse/elements/alpha_relative", eeg_handler, "EEG")

    server = osc_server.ThreadingOSCUDPServer(
        (args.ip, args.port), dispatcher)
    print("Serving on {}".format(server.server_address))
    server.serve_forever()