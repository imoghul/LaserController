#!/usr/bin/python
from tkinter.filedialog import askopenfilename
from tkinter import *
from serial_comms import *
import logging
from MotorController import MotorController, EncoderController
from EquipmentController import *
from SerialPortSelector import SerialPortSelector
# logger = None

def chooseLogFile():
    return askopenfilename(title="Please select a log file")

def setupGUI(logger):
    # Create object
    root = Tk()
    
    # Adjust size
    root.geometry("1200x1000")
    root.title("Control Panel")

    serialFrame = LabelFrame(root, text="Serial Port")
    serialFrame.pack()

    motorFrame = LabelFrame(root, text="Motor Control")
    motorFrame.pack(side=TOP)

    equipmentFrame = LabelFrame(root, text="Equipment Control")
    equipmentFrame.pack(side=TOP)

    refreshButton = Button(
                serialFrame,
                text="Refresh Serial Ports",
                command=lambda: [motorPortSelector.removePort(),equipmentPortSelector.removePort(),motorPortSelector.updatePorts(),equipmentPortSelector.updatePorts()],
            )

    refreshButton.pack(side=BOTTOM)

    motorPortSelector = SerialPortSelector(serialFrame,"Motor",115200)
    equipmentPortSelector = SerialPortSelector(serialFrame,"Equipment",9200,ending=b'\r')

    

    motors = 5
    motorControllers = []

    for i in range(motors):
        motorControllers.append(MotorController(motorFrame, i + 1, motorPortSelector.write,motorPortSelector.readCommand))

    EncoderController(motorFrame,motorPortSelector.readCommand, logger = logger)
    
    EquipmentController(equipmentFrame,equipmentPortSelector.write,equipmentPortSelector.readCommand, logger = logger);
    
    return root


if __name__ == "__main__":

    FORMAT = '%(asctime)s : %(message)s'
    formatter = logging.Formatter(FORMAT)
    # create logger with 'spam_application'
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)
    # create file handler which logs even debug messages
    fh = logging.FileHandler(chooseLogFile())
    fh.setLevel(logging.INFO)
    fh.setFormatter(formatter)
    logger.addHandler(fh)
    

    root = setupGUI(logger)
    root.lift()
    root.attributes('-topmost',True)
    root.after_idle(root.attributes,'-topmost',False)
    root.mainloop()