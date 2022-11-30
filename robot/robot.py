from time import time

import robot.motor
from robot.config import Config
#from robot.serialTeensyToPi import SerialInput as SensorData

conf = Config(None, 1, False, True, 10)
class Robot():
    def __init__(self):
        pass
#        self.sensordata = SensorData()
    def run(self):
        # setup the timeLimit for shutting down the robot after some time
        startTime = int(time())
        runningTime = int(time())
        
        # main running loop
        while(runningTime - startTime <= conf.timeLimit):
            self.tick()
            runningTime = int(time())

    # this function is called continuously while the robot is running 
    def tick(self):
#        self.sensordata.receiveData()
        print("hello")
