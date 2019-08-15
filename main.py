import sys
import MeCab
import tkinter as tk
from tkinter import messagebox as mbox

# GUI 処理
window = tk.Tk()
window.title("形態素解析")
window.geometry("400x300")

#ラベル
label = tk.Label(window, text="入力")
label.pack()

#テキストボックス
textbox = tk.Entry(window)
textbox.pack()
textbox.insert(tk.END,"")

#ボタン処理
text = ""
def On_Click():
    gui_text = textbox.get()
    m = MeCab.Tagger("")

    text = m.parse(gui_text)

    mbox.showinfo("入力文字解析", text)

#ボタン作成
OK_Button = tk.Button(window, text="入力", command=On_Click)
OK_Button.pack()

window.mainloop()