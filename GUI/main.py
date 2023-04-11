import tkinter as tk
import tkinter.ttk as ttk

# settings
padding = 10

# main setup
window = tk.Tk()
frame = tk.Frame(master=window)
frame.grid(row=3, column=3)
window.columnconfigure([0, 1, 2], weight=1, minsize=20)
window.rowconfigure([0, 1, 2], weight=1, minsize=20)

# explanatory label
label1 = ttk.Label(master=window, text="Value:")
label1.grid(row=0, column=0, padx=padding, pady=padding, sticky="e")

# main label
label2 = ttk.Label(master=window, text="Hohoho")
label2.grid(row=0, column=1, padx=padding, pady=padding)


# changes value of button
def display_value():
    label2["text"] = "Changed"


# run button
button1 = ttk.Button(master=window, text="Clickity click", command=display_value)
button1.grid(row=1, column=1, padx=padding, pady=padding)

window.mainloop()