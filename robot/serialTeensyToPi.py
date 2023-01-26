import serial as s 
import json
from time import sleep

class SerialInput(object):
    
    def __init__(self):
        self.serial = s.Serial(port='/dev/ttyACM0', baudrate=115200)
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
        line = json.loads(self.ser.readline().decode('utf-8').rstrip())
        # print(line)
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

    def recieveCamData(self):
        pass
        
    def pingTeensy(self):
        self.serial.write(b'r')

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.flush()
    ser = SerialInput()

    while True:
        ser.receiveData()
        sleep(1)
