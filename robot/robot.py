from time import time, sleep

import robot.motor
from robot.config import Config
from robot.algorithm import Algorithm
#from robot.serialTeensyToPi import SerialInput as SensorData

#       ALGO, SPEED, CAMERA, TESTING, TIME LIMIT 
class Robot():
    def __init__(self):
        self.conf = Config(None, 1, False, True, 10, 10)
        #self.sensorData = SensorData()
        #self.algo = Algorithm()
    def run(self):
        sleep(self.conf.orientationTime)
        # setup the timeLimit for shutting down the robot after some time
        startTime = int(time())
        runningTime = int(time())
        
        # main running loop
        while(runningTime - startTime <= self.conf.timeLimit):
            self.tick()
            runningTime = int(time())

    def arcTurn(self, angle):
        pass
    
    def moveStraight(self):
        pass

    # this function is called continuously while the robot is running 
    def tick(self):
        # Run This twice a secondish
        #self.sensorData.receiveData()

        #self.sensorData.receiveCamData() ## Access with self.sensorData.cam_data
        print("hello")
