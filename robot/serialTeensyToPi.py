import serial as s 
import json
from time import sleep

# magnetometer, Camera, Encoder, Lidar Sensor?, accelerometer 
class SerialInput(object):
    
    def __init__(self):
        self.serial = s.Serial(port='/dev/ttyACM0', baudrate=115200)

        # self.mag = [0.0,0.0,0.0,0.0] ## x,y,z,course
        # self.encoder = 0.0
        # self.sonar = [-1,-1,-1,-1,-1] ## left, front left, front, front right, right
        # self.accel = [0.0,0.0,0.0] ## x,y,z
        self.cam_data = None

        self.serial.flush()
        self.fr_data = -1
        self.fl_data = -1
        self.f_data = -1
        self.l_data = -1
        self.r_data = -1
        self.accelX= 0.0
        self.accelY= 0.0
        self.accelZ= 0.0
        self.magCourse = 0.0
        self.magX = 0.0
        self.magY = 0.0
        self.magZ = 0.0

    def receiveData(self):
        self.pingTeensy()
        line = json.loads(self.serial.readline().decode('utf-8').rstrip())
        # print(line) ## DEBUGGING
#        self.sonar[0] = line['l_data']
#        self.sonar[0] = line['fl_data']
#        self.sonar[0] = line['f_data']
#        self.sonar[0] = line['fr_data']
#        self.sonar[0] = line['r_data']
#        self.accel[0] = line['accelX']
#        self.accel[1] = line['accelY']
#        self.accel[2] = line['accelZ']
#        self.mag[0] = line['magX']
#        self.mag[1] = line['magY']
#        self.mag[2] = line['magZ']
#        self.mag[3] = line['magCourse']

        self.fr_data = line['fr_data']
        self.fl_data = line['fl_data']
        self.f_data = line['f_data']
        self.l_data = line['l_data']
        self.r_data = line['r_data']
        self.accelX = line['accelX']
        self.accelY = line['accelY']
        self.accelZ = line['accelZ']
        self.magCourse = line['magCourse']
        self.magZ = line['magX']
        self.magY = line['magY']
        self.magZ = line['magZ']

    def receiveCamData(self):
        pass ## put camera data/picture into self.cam_data
        
    def pingTeensy(self):
        self.serial.write(b'r')

if __name__ == '__main__':
    ser = s.Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.flush()
    ser = SerialInput()

    while True:
        ser.receiveData()
        sleep(1)
