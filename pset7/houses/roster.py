from cs50 import SQL
from sys import argv

if len(argv) != 2:  # Checks for the correct amount of argv
    print("Usage: python roster.py house")
    exit()

db = SQL("sqlite:///students.db")
# Reads all the info the program is going to print from the table
roster = db.execute("SELECT first, middle, last, birth  FROM students WHERE house = ? ORDER BY last, first", argv[1])
# For each students prints out the info
for student in roster:
    if student["middle"] == None:  # If the student has no middle name it is not printed out
        print(student["first"], student["last"] + ",", "born", student["birth"])

    else:
        print(student["first"], student["middle"], student["last"], student["birth"])
