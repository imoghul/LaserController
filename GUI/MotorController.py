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
    def __init__(self, root, num, getSer):
        self.frame = Frame(root)
        self.frame.pack(side=TOP)
        self.num = num
        self.getSer = getSer
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
        if self.getSer() != None:
            self.getSer().write(string.encode())
        else:
            print(string)# raise Exception("No serial port defined")
