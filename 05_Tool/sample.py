from tkinter import *
import serial

ws1 = Tk()
ws1.title("PKM Configuration")
ws1.geometry('450x250')

frame_one = LabelFrame(ws1, text='Voltage Output')
frame_one.grid(row=1, column=2, padx=10)
frame_two = LabelFrame(ws1, text='Switch Signal')
frame_two.grid(row=1, column=3)
frame_three = LabelFrame(ws1, text='Connect USB')
frame_three.grid(row=1, column=1,padx=10)

Label(frame_three, text="COM: ").pack()

def doDisable():
    btn_run.configure(state="disabled")
def doEnable():
    btn_run.configure(state="active")

com_select = Text(frame_three, height = 1, width = 6)
com_select.pack()

btn_usb_text = StringVar()
btn_usb = Button(frame_three, textvariable = btn_usb_text, command=lambda:f_connect_usb( com_select.get("1.0", "end-1c"))).pack(side="top", padx=40,pady=5)
btn_usb_text.set("Connect")

group_vol = IntVar()
group_sw_sig = IntVar()
Radiobutton(frame_one, text='0V', variable=group_vol, value=1).pack()
Radiobutton(frame_one, text='12V', variable=group_vol, value=1).pack()
Radiobutton(frame_one, text='24V', variable=group_vol, value=2).pack()
btn_vol_text = StringVar()
btn_vol = Button(frame_one, textvariable= btn_vol_text, command=lambda:f_sel_voltage( group_vol.get()))
btn_vol_text.set("OK")
btn_vol.pack(side="top", padx=40,pady=5)

Radiobutton(frame_two, text='ST uC Programming', variable=group_sw_sig, value=3).pack(anchor=W)
Radiobutton(frame_two, text='BLE Programming', variable=group_sw_sig, value=4).pack(anchor=W)
Radiobutton(frame_two, text='UWB Programming', variable=group_sw_sig, value=5).pack(anchor=W)
Radiobutton(frame_two, text='Not Use', variable=group_sw_sig, value=6).pack(anchor=W)
btn_run = Button(frame_two, text='Run', state="disabled")
btn_run.pack(side="top", padx=40,pady=5)

def f_connect_usb(value):
    if btn_usb_text.get() == "Connect":
        com = "COM" + value
        ser = serial.Serial(com,115200)  # open serial port
        print(ser.name)         # check which port was really used
        btn_usb_text.set("Disconnect")
        return ser
    else:
        com = "COM" + value
        ser = serial.Serial(com,115200)  # open serial port
        ser.close()
        btn_usb_text.set("Connect")


def f_sel_voltage(value):
    if btn_usb_text.get() == "OK":
        ser.write('1')     # write a string
        btn_usb_text.set("Edit")
    else:
        ser.write('1')
        btn_usb_text.set("OK")



ws1.mainloop()