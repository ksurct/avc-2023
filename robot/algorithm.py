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
    def __init__(self):
        self.section = 1
        self.obstacles = ["Blue", "yellow", "ramp", "tunnel"]
        self.objLastSeen = None
        
    def Section1(self):
        if self.objLastSeen == self.obstacles[0]:
            # sees the correct object
            # keep going
            pass
        else:
            # sees the wrong object
            # maybe change to section 2 
            pass
    
    def Section2(self):
        pass
    
    def Section3(self):
        pass
    
    def Section4(self):
        pass

    def Section5(self):
        pass

    def Section6(self):
        pass

    def Section7(self):
        pass

    def Section8(self):
        pass