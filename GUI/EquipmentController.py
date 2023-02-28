from tkinter import *

class Mnemonic:
    def __init__(self,root,command,title,min,max,getSer,set = True, get = True):
        self.frame = LabelFrame(root,text=title)
        self.frame.pack(side=BOTTOM)
        self.command = command
        self.getSer = getSer

        if set:
            self.setFrame = Frame(self.frame)
            self.numSelector = Spinbox(self.setFrame, from_=min, to_=max)
            self.setButton = Button(
                self.setFrame,
                text="Set",
                command=lambda: self.set(self.numSelector.get()),
            )
            self.setButton.pack(side=LEFT)
            self.numSelector.pack(side=LEFT)
            self.setFrame.pack(side=BOTTOM)
        if get:
            self.getFrame = Frame(self.frame)
            self.getButton = Button(
                self.frame,
                text="Get",
                command=lambda: self.get(),
            )
            self.label = Label(self.getFrame, text="")
            
            self.getButton.pack(side=LEFT)
            self.label.pack(side=LEFT)
            self.getFrame.pack(side=BOTTOM)

    def set(self,val):
        string = "!"+self.command+" "+val
        print(string)
        if self.getSer()!=None:
            self.getSer().write(string.encode())
    def get(self):
        string = "?"+self.command
        print(string)
        if self.getSer()!=None:
            self.getSer().write(string.encode())
            self.label.config(
                text = self.getSer().readline()
            )

class EquipmentController:
    def __init__(self,root, getSer):
        self.frame = Frame(root)
        self.frame.pack(side=TOP)

        self.mnemonics = []
        self.mnemonics.append(Mnemonic(self.frame,"CH","Set-point high threshold",0,100,getSer))
        self.mnemonics.append(Mnemonic(self.frame,"CL","Set-point low threshold",0,100,getSer))
        self.mnemonics.append(Mnemonic(self.frame,"GA","Accept gauge error",0,100,getSer))
        self.mnemonics.append(Mnemonic(self.frame,"GW","Switch gauge on/off",0,100,getSer,get=False))
        self.mnemonics.append(Mnemonic(self.frame,"GV","Gauge Version",0,100,getSer,set=False))
        self.mnemonics.append(Mnemonic(self.frame,"RC","Relay controlling gauge",1,2,getSer))
        self.mnemonics.append(Mnemonic(self.frame,"TH","Link high threshold",0,100,getSer))
        self.mnemonics.append(Mnemonic(self.frame,"TL","Link low threshold",0,100,getSer))
        self.mnemonics.append(Mnemonic(self.frame,"US","Units",0,3,getSer))
        self.mnemonics.append(Mnemonic(self.frame,"VL","Voltage",0,3,getSer,set=False))

        