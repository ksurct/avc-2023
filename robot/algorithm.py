#from robot.serialTeensyToPi import SerialInput as SensorData
class Algorithm(object):
    def __init__(self):
        pass

    def turnLeft(self):
        pass
        #do stuff here

    def turnRight(self):
        pass
        #do stuff here

    def goStraight(self):
        pass
        #do stuff here

class HardCodeAlgo(object):
    def __init__(self, sensorData):
        self.section = 1
        self.obstacles = ["blue", "yellow", "ramp", "tunnel", "end"]
        self.objLastSeen = None
        self.sensorData = sensorData

        self.distGoneInSec = 0
        self.angleTurnedInSec = 0

        # To know how far to go in each section feet
        # will have to add on some distance in calculations to go around not through the objects 
        self.section1Dist = 20
        self.section2Dist = 31.62 #sqrt(30^2+10^2)
        self.section3Dist = 31.62 #sqrt(30^2+10^2)
        self.section4Dist = 18 # the ramp is 2 feet long
        self.section5Dist = 20 # may need adjusting after landing
        self.section6Dist = 30
        self.section7Dist = 30
        self.section8Dist = 20

        # To know how much to turn at the end of each section degrees (Counter clockwise is positive)
        self.section1Angle = -108.4 ## Turn 1 Outer
        self.section2Angle = 36.5 ## Turn 2 Inner
        self.section3Angle = -71.6 ## Turn 3 Outer
        self.section4Angle = 0 ## RAMP
        self.section5Angle = -90 ## Turn 4 Outer
        self.section6Angle = 0 ## TUNNEL
        self.section7Angle = -90 ## Turn 5 Outer
        self.section8Angle = 0 ## END
        
    def calculate(self, ):
        pass
        
    def Section1(self): ## Get around the first turn we want to go to the left of the first bucket
        if self.objLastSeen == self.obstacles[0]:
            # sees the correct object
            # keep going
            pass
        else:
            # sees the wrong object
            # maybe change to section 2 
            pass
    
    def Section2(self): ## Get around the second interior obtuse turn on the right of the bucket
        if self.objLastSeen == self.obstacles[1]:
            # sees the correct object
            # keep going
            pass
        else:
            # sees the wrong object
            # maybe change to section 2 
            pass
    
    def Section3(self): ## Go around the third turn we want to go to the left of the bucket
        if self.objLastSeen == self.obstacles[0]:
            # sees the correct object
            # keep going
            pass
        else:
            # sees the wrong object
            # maybe change to section 2 
            pass
    
    def Section4(self): ## RAMP
        pass

    def Section5(self):
        if self.objLastSeen == self.obstacles[0]:
        
            # sees the correct object
            # keep going
            pass
        else:
            # sees the wrong object
            # maybe change to section 2 
            pass

    def Section6(self):
        if self.objLastSeen == self.obstacles[3]:
            # sees the correct object
            # keep going
            pass
        else:
            # sees the wrong object
            # maybe change to section 2 
            pass

    def Section7(self):
        if self.objLastSeen == self.obstacles[0]:
            # sees the correct object
            # keep going
            pass
        else:
            # sees the wrong object
            # maybe change to section 2 
            pass

    def Section8(self):
        if self.objLastSeen == self.obstacles[4]:
            # sees the correct object
            # keep going
            pass
        else:
            # sees the wrong object
            # maybe change to section 2 
            pass