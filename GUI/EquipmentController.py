from tkinter import *
import math
class Mnemonic:
    def __init__(self,root,command,title,min,max,write,read,set = True, get = True):
        self.frame = LabelFrame(root,text=title)
        # self.frame.pack(side=BOTTOM)
        self.command = command
        self.write = write
        self.read = read
        self.title = title
        self.min = min
        self.max = max
        self.set = set
        self.get = get

        if set:
            self.setFrame = Frame(self.frame)
            self.numSelector = Spinbox(self.setFrame, from_=min, to_=max)
            self.setButton = Button(
                self.setFrame,
                text="Set",
                command=lambda: self.setVal(self.numSelector.get()),
            )
            self.setButton.pack(side=LEFT)
            self.numSelector.pack(side=LEFT)
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
    def resetRoot(self,root):
        self.__init__(root,self.command,self.title,self.min,self.max,self.write,self.read,self.set, self.get)

    def setVal(self,val):
        string = "!"+self.command+" "+val+"\r\n"
        self.write(string.encode())
    def getVal(self):
        string = "?"+self.command+"\r\n"
        ret = self.read(string.encode())
        print(ret)
        if ret!=False:
            self.label.config(text=str(ret))
        return ret
       

class EquipmentController:
    def __init__(self,root, write, read):
        self.frame = Frame(root)
        self.frame.pack(side=TOP)

        self.mnemonics = []
        self.mnemonics.append(Mnemonic(self.frame,"CH","Set-point high threshold",0,100,write, read))
        self.mnemonics.append(Mnemonic(self.frame,"CL","Set-point low threshold",0,100,write, read))
        self.mnemonics.append(Mnemonic(self.frame,"GA","Accept gauge error",0,100,write, read))
        self.mnemonics.append(Mnemonic(self.frame,"GW","Switch gauge on/off",0,100,write, read,get=False))
        self.mnemonics.append(Mnemonic(self.frame,"GV","Gauge Version",0,100,write, read,set=False))
        self.mnemonics.append(Mnemonic(self.frame,"RC","Relay controlling gauge",1,2,write, read))
        self.mnemonics.append(Mnemonic(self.frame,"TH","Link high threshold",0,100,write, read))
        self.mnemonics.append(Mnemonic(self.frame,"TL","Link low threshold",0,100,write, read))
        self.mnemonics.append(Mnemonic(self.frame,"US","Units",0,3,write, read))
        self.mnemonics.append(Mnemonic(self.frame,"VL","Voltage",0,3,write, read,set=False))

        y = round(math.sqrt(len(self.mnemonics)))
        x = math.ceil(len(self.mnemonics)/y)

        for i in range(y):
            currFrame = Frame(self.frame)
            currFrame.pack(side=LEFT)
            for j in range(x):
                try:
                    self.mnemonics[i*y+j].resetRoot(currFrame)
                    self.mnemonics[i*y+j].frame.pack(side=TOP)
                except:pass