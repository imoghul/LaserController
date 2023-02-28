from tkinter import *
from serial_comms import serial_ports
import serial

class SerialPortSelector:
    def __init__(self,root,name):
        self.frame = Frame(root)
        self.frame.pack(side=LEFT)
        self.port = None
        self.portClicked = StringVar();
        self.label = Label(self.frame, text="")
        self.portButton = None
        self.portOptions = serial_ports()
        self.portClicked.set(self.portOptions[0])
        self.drop = OptionMenu(self.frame, self.portClicked, *self.portOptions)
        self.drop.pack(side = TOP)
        self.portButton = Button(self.frame, text=f"Select {name} Serial Port", command = self.callback).pack(side=BOTTOM)
        self.label.pack(side=TOP)

    def callback(self):
        selected_port = self.portClicked.get()
        if self.port != None and self.port.port == selected_port:
            return
        try:
            self.port = serial.Serial(selected_port, baudrate=115200, stopbits=1)
        except PermissionError:
            print("Port already opened")
            pass
        except Exception as e:
            self.port = None

        # for i in self.controllers:
        #     i.ser = self.port
        self.label.config(
            text=("Selected COM Port: " + selected_port)
            if self.port != None
            else 'Error connecting to port: "%s"' % selected_port
        )

    def getSer(self):
        return self.port

