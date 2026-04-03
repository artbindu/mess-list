# Python Input Module Setup

This module converts Excel input into a TXT file used by the C++ output program.

## Install Python (If Not Installed)

Check first:

python --version

If command is not found, install Python:

- macOS (Homebrew):

brew install python

- macOS (Homebrew): Specific Python version:

brew reinstall python@3.14

- Windows:

Download and install from https://www.python.org/downloads/
Important: enable the "Add Python to PATH" option during setup.

After installation, verify:

python --version

## Required Package

The code imports:
- openpyxl

Install it with pip:

python -m pip install openpyxl

## Recommended: Use a Virtual Environment

From project root:

python -m venv .venv
source .venv/bin/activate
python -m pip install --upgrade pip
python -m pip install openpyxl

On Windows PowerShell, activate with:

.venv\Scripts\Activate.ps1

## Verify Installation

Run this check:

python -c "import openpyxl; print('openpyxl installed')"

## Run Script

From project root:

python python-takeinput/main.py

When prompted, enter file name without extension (example: demo).
The script expects input at data/<name>.xlsx and writes data/<name>.txt.
