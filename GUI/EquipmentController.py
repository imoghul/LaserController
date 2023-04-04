from tkinter import *
import math
import numpy as np
class Mnemonic:
    def __init__(self,root,command,title,min,max,write,read,set, get, num):
        
        # self.frame.pack(side=BOTTOM)
        self.command = command
        self.write = write
        self.read = read
        self.title = title + (f" {num}" if num else "")
        self.min = min
        self.max = max
        self.set = set
        self.get = get

        self.num = num

        self.frame = LabelFrame(root,text=self.title)

        if num:
            self.numFrame = Frame(self.frame)
            self.numLabel = Label(self.frame,text="Argument Value:")
            self.numSelector = Spinbox(self.numFrame, from_=min, to_=max)
            self.numLabel.pack(side = TOP)
            self.numSelector.pack(side=LEFT)
            self.numFrame.pack(side=TOP)

        if set:
            self.setFrame = Frame(self.frame)
            self.setSelector = Spinbox(self.setFrame, from_=0, to_=3)
            self.setButton = Button(
                self.setFrame,
                text="Set",
                command=lambda: self.setVal(self.setSelector.get()),
            )
            self.setButton.pack(side=LEFT)
            self.setSelector.pack(side=LEFT)
            self.setFrame.pack(side=TOP)
        if get:
            self.getFrame = Frame(self.frame)
            self.getButton = Button(
                self.getFrame,
                text="Get",
                command=lambda: self.getVal(),
            )
            self.label = Label(self.getFrame, text="")
            
            self.getButton.pack(side=LEFT)
            self.label.pack(side=LEFT)
            self.getFrame.pack(side=TOP)


    def setVal(self,val):
        string = "!"+self.command+(str(self.numSelector.get()) if self.num else "")+"="+val+"\r"
        print(string)
        ret = self.read(string.encode())
        if ret!=False:
            self.label.config(text=ret.decode())
        return ret
        # if True or not self.write(string.encode()): print(string)
    def getVal(self):
        string = "?"+self.command+str(self.numSelector.get() if self.num and self.command!="US" else "")+"\r"
        print(string)
        ret = self.read(string.encode())
        if ret!=False:
            self.label.config(text=ret.decode())
        return ret
       

class EquipmentController:
    def __init__(self,root, write, read):
        self.frame = Frame(root)
        self.frame.pack(side=TOP)

        self.mnemonics = []
        self.mnemonics.append([self.frame,"CH","Set-point high threshold",0,100,write, read,True,True,True])
        self.mnemonics.append([self.frame,"CL","Set-point low threshold",0,100,write, read,True,True,True])
        self.mnemonics.append([self.frame,"GA","Accept gauge error",0,100,write, read,True,True,True])
        self.mnemonics.append([self.frame,"GW","Switch gauge on/off",0,100,write, read,True,False,True])
        self.mnemonics.append([self.frame,"GV","Gauge Version",0,100,write, read,False,True,True])
        self.mnemonics.append([self.frame,"RC","Relay controlling gauge",1,2,write, read,True,True,True])
        self.mnemonics.append([self.frame,"TH","Link high threshold",0,100,write, read,True,True,False])
        self.mnemonics.append([self.frame,"TL","Link low threshold",0,100,write, read,True,True,False])
        self.mnemonics.append([self.frame,"US","Units",0,3,write, read,True,True,True])
        self.mnemonics.append([self.frame,"VL","Voltage",0,3,write, read,False,True,True])

        
        x = round(math.sqrt(len(self.mnemonics)))
        y = math.ceil(len(self.mnemonics)/x)
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
                # except:pass