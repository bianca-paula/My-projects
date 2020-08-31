#Simple login app

import tkinter as tk

gui = tk.Tk()
gui.geometry("250x100")
gui['background']= '#FFE4E1'

title = tk.Label(gui, text ="Login")
title.config(font =("Courier", 14))
title.config(bg='white')
title.grid()

username_variable = tk.StringVar()
password_variable = tk.StringVar()

def submit():
    username = usernameInput.get()
    password = password_variable.get()

    print("Username : " + username)
    print("TPassword : " + password)

    username_variable.set("")
    password_variable.set("")



username_label = tk.Label(gui, text='Username', font=('calibre', 10, 'bold'))
username_label.config(bg='white')
usernameInput = tk.Entry(gui, textvariable=username_variable, font = ('calibre', 10, 'normal'))

password_label = tk.Label(gui, text='Password', font=('calibre', 10, 'bold'))
password_label.config(bg='white')
passwordInput = tk.Entry(gui, textvariable=password_variable, font=('calibre', 10, 'normal'), show='*')

submitButton = tk.Button(gui, text='Submit', command=submit)

username_label.grid(row=1, column=0)
usernameInput.grid(row=1, column=1)
password_label.grid(row=2, column=0)
passwordInput.grid(row=2, column=1)
submitButton.grid(row=3, column=1)

gui.mainloop()