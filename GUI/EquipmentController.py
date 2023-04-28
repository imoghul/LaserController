from tkinter import *
import math
import numpy as np
class Mnemonic:
    # command is the mneumonic for the guauge command
    # title is the description of the mneumonic
    # min/max ar the minimum/maximum value for the spinbox
    # write/read are the functions to use the serial port
    # set/get are booleans for whether this mneumonic allows setting/getting
    # num is a boolean of whether there is an argument
    # logger is the logger
    # useArgForGet is a boolean of whether or not to include the argument for get commands
    def __init__(self,root,command,title,min,max,write,read,set, get, num,logger,useArgForGet=True):
        
        # self.frame.pack(side=BOTTOM)
        self.command = command
        self.write = write
        self.read = read
        self.title = title #+ (f" {num}" if num else "")
        self.min = min
        self.max = max
        self.set = set
        self.get = get
        self.useArgForGet = useArgForGet
        self.num = num
        self.logger = logger
        self.frame = LabelFrame(root,text=self.title)

        if num:
            self.numFrame = Frame(self.frame)
            self.numLabel = Label(self.frame,text="Argument Value:")
            self.numSelector = Spinbox(self.numFrame, from_=0, to_=100)
            self.numLabel.pack(side = TOP)
            self.numSelector.pack(side=LEFT)
            self.numFrame.pack(side=TOP)

        if set:
            self.setFrame = Frame(self.frame)
            self.setLabel = Label(self.frame,text="Set Value:")
            self.setSelector = Spinbox(self.setFrame, from_=min, to_=max)
            self.setButton = Button(
                self.setFrame,
                text="Set",
                command=lambda: self.setVal(self.setSelector.get()),
            )
            self.setLabel.pack(side = TOP)
            self.setButton.pack(side=LEFT)
            self.setSelector.pack(side=LEFT)
            self.setFrame.pack(side=TOP)
        if get:
            self.getFrame = Frame(self.frame)
            self.getLabel = Label(self.frame,text="Get Value:")
            self.getButton = Button(
                self.getFrame,
                text="Get",
                command=lambda: self.getVal(),
            )
            self.label = Label(self.getFrame, text="")
            self.getLabel.pack(side = TOP)
            self.getButton.pack(side=TOP)#LEFT xor TOP
            self.label.pack(side=BOTTOM)#LEFT xor BOTTOM
            self.getFrame.pack(side=TOP)

    def log(self,val):
        if(self.logger!=None):self.logger.info(val)
    def setVal(self,val):
        string = "!"+self.command+(str(self.numSelector.get()) if self.num else "")+"="+val+"\r"
        ret = self.read(string.encode())

        returnString = (ret.decode().replace('\r','').replace('\n','') if ret!=False else "nothing because serial port is not connected yet")
        commandString = string.replace('\r','').replace('\n','')
        self.log(f"\n\tExecuted following command: {commandString}\n\tGot back {returnString}")

        if ret!=False:
            self.label.config(text=ret.decode())
        return ret
    def getVal(self):
        string = "?"+self.command+str(self.numSelector.get() if self.num and self.useArgForGet else "")+"\r"
        # print(string)
        ret = self.read(string.encode())

        returnString = (ret.decode().replace('\r','').replace('\n','') if ret!=False else "nothing because serial port is not connected yet")
        commandString = string.replace('\r','').replace('\n','')
        self.log(f"\n\tExecuted following command: {commandString}\n\tGot back {returnString}")

        if ret!=False:
            self.label.config(text=ret.decode())
        return ret
       

class EquipmentController:
    def __init__(self,root, write, read, logger = None):
        self.frame = Frame(root)
        self.frame.pack(side=TOP)

        self.mnemonics = []
        self.mnemonics.append([self.frame,"CH","Set-point high threshold",0,100,write, read,True,True,True,logger])
        self.mnemonics.append([self.frame,"CL","Set-point low threshold",0,100,write, read,True,True,True,logger])
        self.mnemonics.append([self.frame,"GW","Switch gauge on/off",0,100,write, read,True,False,True,logger])
        self.mnemonics.append([self.frame,"GA","Accept gauge error",0,100,write, read,True,True,True,logger])
        self.mnemonics.append([self.frame,"GV","Gauge Version",0,100,write, read,False,True,True,logger])
        self.mnemonics.append([self.frame,"VL","Voltage",0,3,write, read,False,True,True,logger])
        self.mnemonics.append([self.frame,"RC","Relay controlling gauge",1,2,write, read,True,True,True,logger])
        self.mnemonics.append([self.frame,"TH","Link high threshold",0,100,write, read,True,True,False,logger])
        self.mnemonics.append([self.frame,"TL","Link low threshold",0,100,write, read,True,True,False,logger])
        self.mnemonics.append([self.frame,"US","Units",0,3,write, read,True,True,True,logger,False])
        

        # create objects in squar(ish) formation
        y = round(math.sqrt(len(self.mnemonics)))
        x = math.ceil(len(self.mnemonics)/y)
        filler = x*y-len(self.mnemonics)

        self.mnemonics+=[None]*filler
        self.mnemonics = [self.mnemonics[i*y:(i+1)*y] for i in range(x)]
        
      
        for col in self.mnemonics:
            currFrame = Frame(self.frame)
            currFrame.pack(side=LEFT)
            for val in col:
                if val==None:continue
                val[0] = currFrame
                temp = Mnemonic(*val)
                temp.frame.pack(side=TOP)
                