import serial
import tkinter as tk
import serial.tools.list_ports

class SerialUI:
    def __init__(self, master):
        self.master = master
        self.master.title("Serial Connection")

        # Create a label for the COM port selection
        self.com_label = tk.Label(self.master, text="Select COM Port:")
        self.com_label.pack()

        # Create a dropdown menu for selecting the COM port
        com_options = [comport.device for comport in serial.tools.list_ports.comports()]
        self.com_var = tk.StringVar()
        self.com_var.set(com_options[0])
        self.com_dropdown = tk.OptionMenu(self.master, self.com_var, *com_options)
        self.com_dropdown.pack()

        # Create a label for the baud rate selection
        self.baud_label = tk.Label(self.master, text="Select Baud Rate:")
        self.baud_label.pack()

        # Create a dropdown menu for selecting the baud rate
        baud_options = [9600, 115200, 57600, 38400]
        self.baud_var = tk.StringVar()
        self.baud_var.set(baud_options[0])
        self.baud_dropdown = tk.OptionMenu(self.master, self.baud_var, *baud_options)
        self.baud_dropdown.pack()

        # Create a button for connecting to the serial port
        self.connect_button = tk.Button(self.master, text="Connect", command=self.connect_serial)
        self.connect_button.pack()

    def connect_serial(self):
        # Get the selected COM port and baud rate
        com_port = self.com_var.get()
        baud_rate = int(self.baud_var.get())

        # Open the serial port
        ser = serial.Serial(com_port, baud_rate, timeout=1)

        # Do something with the serial port, such as reading or writing data

        # Close the serial port
        ser.close()

# Create the main window and start the event loop
root = tk.Tk()
app = SerialUI(root)
root.mainloop()
