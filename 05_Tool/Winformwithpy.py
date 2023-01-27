from tkinter import *

root = Tk()
root.geometry("400x400")
root.title("Sample")
# root.iconbitmap("path")

#create label and positon of it
# Mylabel1 = Label(root, text="Hello World").grid(row=0, column=0)
# Mylabel2 = Label(root, text="Hello World").grid(row=1, column=1)
# Mylabel1.grid(row=0, column=0)
# Mylabel2.grid(row=1, column=1)

r = IntVar()



#have event
# Radiobutton(root, text="12V", variable=r, value = 1, command=lambda:clicked(r.get())).pack()
# Radiobutton(root, text="24V", variable=r, value = 2, command=lambda:clicked(r.get())).pack()
#not event
# Radiobutton(root, text="12V", variable=r, value = 1).pack()
# Radiobutton(root, text="24V", variable=r, value = 2).pack()
# myLabel = Label(root, r.get())
# myLabel.pack()

frame = Frame(root, width=500, height=400, bd=1)
frame.grid(row=0,column=0)
iframe1 = Frame(frame, bd=2, relief=SUNKEN)
v=IntVar()
Label(iframe1, text="Select Voltage").pack(side=TOP, anchor=W)
Radiobutton(iframe1, text='12V', variable=r,
            value=2).pack(side="top", anchor=W)
Radiobutton(iframe1, text='24V', variable=r,
            value=1).pack(side="top", anchor=W)

Button(iframe1, text='Select').pack(side="top", padx=40,pady=5)

iframe1.pack(expand=2, fill=X, pady=10, padx=5)


def clicked(value):
    myLabel = Label(root, text=value)
    myLabel.pack()

# btn = Button(root, text="Click Me",padx=20, pady=10, command=lambda:clicked(r.get()),fg="blue",bg="red")
# btn.pack()


root.mainloop()