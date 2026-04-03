# Mess List - Run Guide

Use a terminal in the project root (Git Bash or macOS/Linux shell).

## 1) Prepare input Excel file

Update `data/demo.xlsx` with your data.

If you have data-format issues, check `data/README.md`.

## 2) Generate TXT input using Python

Run:

`python python-takeinput/main.py`

When prompted for input name, use: `demo`

This generates `data/demo.txt`.

## 3) Verify TXT file formatting

Open `data/demo.txt` in a text editor (for example, Notepad) and verify the content.

## 4) Compile and run C++ output program

Use the latest C++ version (`messlist_v2.0.1.cpp`):

Compile:

`c++ -o cpp-takeoutput/messlist_v2.0.1 cpp-takeoutput/messlist_v2.0.1.cpp`

Run:

`./cpp-takeoutput/messlist_v2.0.1`

## 5) Save final output

Copy the terminal output and save it in your desired output file for `demo`.

