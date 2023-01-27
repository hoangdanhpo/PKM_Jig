from tkinter import *
import serial

root = Tk()
root.geometry("400x400")
root.title("PKM Configuration")
# root.iconbitmap("path")
##################################################################################
voltage = [
    ("12V", 1),
    ("24V", 2),
]
sw_signal = [
    ("ST uC Programming", 3),
    ("BLE Programming", 4),
    ("UWB Programming", 5),
    ("Not Use", 6),
]
##################################################################################
vol = IntVar()
sw_sig = IntVar()

def clicked(value):
    print(value)
    myLabel.pack()
    # Button(iframe1, text='Re-Select',fg="blue",bg="red").pack(side="top", padx=40,pady=5)
##################################################################################
frame11 = Frame(root, width=500, height=400, bd=1)
frame11.grid(row=0,column=0)
iframe111 = Frame(frame11, bd=3, relief="groove")

Label(iframe111, text="Connect USB").pack(side=TOP, anchor=W)
Label(iframe111, text="COM: ").pack(side="left", anchor=W)
Text(iframe111, height = 1, width = 6).pack(side="left", anchor=W)
Label(iframe111, text="     Baudrate: ").pack(side="left", anchor=W)
Text(iframe111, height = 1, width = 6).pack(side="left", anchor=W)

Button(iframe111, text='Connect').pack(side="top", padx=40,pady=5)

iframe111.pack(expand=2, fill=X, pady=10, padx=5)

##################################################################################
frame = Frame(root, width=500, height=400, bd=1)
frame.grid(row=3,column=0)
iframe1 = Frame(frame, bd=3, relief="groove")

Label(iframe1, text="Select Voltage").pack(side=TOP, anchor=W)

for txt, val in voltage:
    Radiobutton(iframe1, text=txt, variable=vol, value=val).pack(side="top", anchor=W)

Button(iframe1, text='Select', command=lambda:clicked(vol.get())).pack(side="top", padx=40,pady=5)

iframe1.pack(expand=2, fill=X, pady=10, padx=5)

##################################################################################
frame1 = Frame(root, width=500, height=400, bd=1)
frame1.grid(row=6,column=0)
iframe11 = Frame(frame1, bd=3, relief="groove")

Label(iframe11, text="Switch Signal").pack(side=TOP, anchor=W)

for txt, val in sw_signal:
    Radiobutton(iframe11, text=txt, variable=sw_sig, value=val).pack(side="top", anchor=W)

Button(iframe11, text='Select').pack(side="top", padx=40,pady=5)

iframe11.pack(expand=2, fill=X, pady=5, padx=5)





root.mainloop()