#!/usr/bin/python

from tkinter import *
from serial_comms import *

from MotorController import MotorController


# Change the label text
def portButtonClick(port, portClicked, label, motorButtons):

    selected_port = portClicked.get()
    if port[0] != None and port[0].port == selected_port:
        return
    try:
        port[0] = serial.Serial(selected_port, baudrate=115200, stopbits=1)
    except PermissionError:
        print("Port already opened")
        pass
    except Exception as e:
        port[0] = None

    for i in motorButtons:
        i.ser = port[0]
    label.config(
        text=("Selected COM Port: " + selected_port)
        if port[0] != None
        else 'Error connecting to port: "%s"' % selected_port
    )


def setupGUI():
    # Create object
    root = Tk()

    # Adjust size
    root.geometry("400x250")
    root.title("Control Panel")
    serialFrame = LabelFrame(root, text="Serial Port")
    serialFrame.pack()
    motorFrame = LabelFrame(root, text="Motor Control")
    motorFrame.pack(side=TOP)

    port = [None]
    portClicked = StringVar()
    label = Label(serialFrame, text="")
    portButton = None
    motorButtons = []

    motors = 5

    # Dropdown menu options
    portOptions = serial_ports()

    # initial menu text
    portClicked.set(portOptions[0])

    # Create Dropdown menu
    drop = OptionMenu(serialFrame, portClicked, *portOptions)
    drop.pack(side=TOP)

    # Create button, it will change label text
    portButton = Button(
        serialFrame,
        text="Select COM Port",
        command=lambda: portButtonClick(port, portClicked, label, motorButtons),
    ).pack(side=TOP)

    # Create Label
    label.pack(side=TOP)

    for i in range(motors):
        motorButtons.append(MotorController(motorFrame, i + 1, port[0]))

    return root


if __name__ == "__main__":
    setupGUI().mainloop()
