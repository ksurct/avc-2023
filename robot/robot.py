import motor
import config
from serialTeensyToPi import SerialInput as SensorData

class Robot():
    
    # Two public functions  
    def __init__(self):
        pass
        self.sensordata = SensorData()
    def run(self):
        while(True):
            self.tick()

    
    def __tick(self):
        self.sensordata.receiveData()