import tkinter as tk
import tkinter.ttk as ttk

# settings
import serial as serial

padding = 10

# main setup
window = tk.Tk()
frame = tk.Frame(master=window)
frame.grid(row=3, column=3)
window.columnconfigure([0, 1, 2], weight=1, minsize=20)
window.rowconfigure([0, 1, 2], weight=1, minsize=20)

# explanatory label
label1 = ttk.Label(master=window, text="    ")
label1.grid(row=0, column=0, padx=padding, pady=padding, sticky="e")

# main label
label2 = ttk.Label(master=window, text="Voltage")
label2.grid(row=0, column=1, padx=padding, pady=padding)


# # start communication
# def start_com():
#     ser = serial.Serial()
#     ser.baudrate = 9600
#     ser.port = 'COM3'
#     ser.open()
#     # begin communication
#     ser.write(bytes('0', "utf-8"))


# changes value of button
def display_value():
    ser = serial.Serial()
    ser.baudrate = 9600
    ser.port = 'COM3'
    ser.open()
    while True:
        # begin communication
        s = ser.read(7)
        # print(s)
        if s:
            # label2["text"] = f"{s}"
            decoded = s.decode(encoding='utf-8')
            nline = decoded.find("\n")
            label2.config(text=f"Value of ADC: {int(decoded[:nline])/51}V")
            window.after(10, label2.update())
            # label2["text"] = f"{int.from_bytes(s, 'big')}"
            return


# run button
button1 = ttk.Button(master=window, text="Get value", command=display_value)
button1.grid(row=1, column=1, padx=padding, pady=padding)

window.mainloop()
