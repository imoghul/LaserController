#!/usr/bin/python

from tkinter import *
from serial_comms import *

from MotorController import MotorController
from EquipmentController import *
from SerialPortSelector import SerialPortSelector

def setupGUI():
    # Create object
    root = Tk()

    # Adjust size
    root.geometry("700x600")
    root.title("Control Panel")

    serialFrame = LabelFrame(root, text="Serial Port")
    serialFrame.pack()

    motorFrame = LabelFrame(root, text="Motor Control")
    motorFrame.pack(side=TOP)

    equipmentFrame = LabelFrame(root, text="Equipment Control")
    equipmentFrame.pack(side=TOP)

    motorPortSelector = SerialPortSelector(serialFrame,"Motor")
    equipmentPortSelector = SerialPortSelector(serialFrame,"Equipment")

    # def getMotorPort(): return motorPortSelector.port
    # def getEquipmentPort(): return equipmentPortSelector.port

    motors = 5
    motorControllers = []

    for i in range(motors):
        motorControllers.append(MotorController(motorFrame, i + 1, motorPortSelector.write,motorPortSelector.readCommand))
    
    EquipmentController(equipmentFrame,equipmentPortSelector.write,equipmentPortSelector.readCommand);
    



    return root


if __name__ == "__main__":
    setupGUI().mainloop()