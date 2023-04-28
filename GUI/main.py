#!/usr/bin/python
from tkinter.filedialog import askopenfilename
from tkinter import *
from serial_comms import *
import logging
from MotorController import MotorController, EncoderController
from EquipmentController import *
from SerialPortSelector import SerialPortSelector
# logger = None

# prompt for the logger file
def chooseLogFile():
    return askopenfilename(title="Please select a log file")

def setupGUI(logger):
    # Create object
    root = Tk()
    
    # Adjust size
    root.geometry("1200x1000")
    root.title("Control Panel")

    # create frame to hole serial port widgets
    serialFrame = LabelFrame(root, text="Serial Port")
    serialFrame.pack()
    # and for motors
    motorFrame = LabelFrame(root, text="Motor Control")
    motorFrame.pack(side=TOP)
    # and for gauge
    equipmentFrame = LabelFrame(root, text="Equipment Control")
    equipmentFrame.pack(side=TOP)

    # create refresh button
    refreshButton = Button(
                serialFrame,
                text="Refresh Serial Ports",
                command=lambda: [motorPortSelector.removePort(),equipmentPortSelector.removePort(),motorPortSelector.updatePorts(),equipmentPortSelector.updatePorts()],
            )

    refreshButton.pack(side=BOTTOM)

    # create serial port selectors in the serialFrame
    motorPortSelector = SerialPortSelector(serialFrame,"Motor",115200)
    equipmentPortSelector = SerialPortSelector(serialFrame,"Equipment",9200,ending=b'\r') # the gauge only uses CR at the end of messages, so set ending to CR

    

    motors = 5
    motorControllers = []

    for i in range(motors):
        motorControllers.append(MotorController(motorFrame, i + 1, motorPortSelector.write,motorPortSelector.readCommand)) # create motor controllers

    EncoderController(motorFrame,motorPortSelector.readCommand, logger = logger) # Create encoder button
    
    EquipmentController(equipmentFrame,equipmentPortSelector.write,equipmentPortSelector.readCommand, logger = logger) # create guauge controller
    
    return root


if __name__ == "__main__":

    # create and configure logger
    FORMAT = '%(asctime)s : %(message)s'
    formatter = logging.Formatter(FORMAT)
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)
    fh = logging.FileHandler(chooseLogFile())
    fh.setLevel(logging.INFO)
    fh.setFormatter(formatter)
    logger.addHandler(fh)
    
    root = setupGUI(logger)
    # set the window to be at the top
    root.lift()
    root.attributes('-topmost',True)
    root.after_idle(root.attributes,'-topmost',False)
    # start program
    root.mainloop()