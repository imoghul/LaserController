from tkinter import *

# import serial
default = "CW"


class ToggleButton(Button):
    def __init__(self, parent, command, *args, **kwargs):
        Button.__init__(self, parent, *args, **kwargs)
        self["text"] = default
        self.commandToRun = command
        self["command"] = self.toggle

    def toggle(self):
        if self["text"] == "CW":
            self["text"] = "CCW"
        else:
            self["text"] = "CW"
        self.commandToRun(self["text"])


class MotorController:
    def __init__(self, root, num, write, read):
        self.frame = Frame(root)
        self.frame.pack(side=TOP)
        self.num = num
        self.write = write
        self.read = read
        self.dir = default

        self.revsSelector = Spinbox(self.frame, from_=0, to_=1000)
        self.startButton = Button(
            self.frame,
            text="Start Motor " + str(num),
            command=lambda: self.command(self.revsSelector.get(), self.dir),
        )

        self.dirButton = ToggleButton(self.frame, command=self.setDir)
        self.stopButton = Button(
            self.frame,
            text="Stop Motor " + str(num),
            command=lambda: self.command(0, 0),
        )

        self.startButton.pack(side=LEFT)
        self.revsSelector.pack(side=LEFT)
        self.dirButton.pack(side=LEFT)
        self.stopButton.pack(side=LEFT)

    def setDir(self, x):
        self.dir = x

    def dirToNum(self, dir):
        if dir == "CW":
            return 1
        elif dir == "CCW":
            return 2
        else:
            return 0

    def command(self, revs, dir):
        
        string = "%d %d %d\r\n" % (
            int(self.num),
            int(self.dirToNum(dir)),
            int(revs),
        )
        if not self.write(string.encode()):
            pass#print(string)# raise Exception("No serial port defined")



class EncoderController:
    def __init__(self, root, read, logger = None):
        self.frame = Frame(root)
        self.frame.pack(side=TOP)
        self.read = read
        self.dir = default
        self.logger = logger

        self.startButton = Button(
            self.frame,
            text="Get Encoder ",
            command=lambda: self.command(),
        )
        self.label = Label(self.frame,text="")


        self.startButton.pack(side=TOP)
        self.label.pack(side=BOTTOM)

    def log(self,val):
        if(self.logger!=None):self.logger.info(val)

    def command(self):
        string = "e\r\n"
        ret = self.read(string.encode())
        
        returnString = (ret.decode().replace('\r','').replace('\n','') if ret!=False else "nothing because serial port is not connected yet")
        commandString = string.replace('\r','').replace('\n','')
        self.log(f"\n\tExecuted command to get encoder value\n\tGot back {returnString}")

        if ret!=False:
            self.label.config(text=ret.decode())
        return ret