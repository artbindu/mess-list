# Mess List - Run Guide

Use a terminal in the project root (Git Bash or macOS/Linux shell).

## Description

This was the **first project of my life**, which I created when I joined **MAC in late 2016**. At the time, I was living in a **hostel**, and we faced significant difficulties during **end-of-month hostel expense calculations**. There were **six members**, multiple expense categories, daily meal entries, and several other cost parameters. Completing the monthly calculations and sharing them with everyone typically took **4–10 days of struggle**.

Observing this recurring problem, I started wondering: *why should this be so difficult? Can we simplify the process and avoid the stress and confusion at the end of every month?* With this idea in mind, I decided to create a **simple and clean solution** that could make the calculation process easier and more accurate.

Initially, convincing people to adopt this new approach was challenging. However, once the hostel members understood the benefits, they began relying on me to complete the calculations **quickly and without errors**. The first version of the project used **basic text-based input** processed through a **C/C++ program** (`cpp-takeoutput`). Later, after learning Python, I improved the solution by introducing **Excel-based inputs** (`python-takeinput`), making it much more user-friendly so that anyone could use it easily.

Overall, it was a **great learning experience**, and we genuinely enjoyed using the system—it saved time, reduced errors, and eliminated the usual end-of-month chaos.


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

