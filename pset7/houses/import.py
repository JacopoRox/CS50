import csv
from cs50 import SQL
from sys import argv

if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit()
db = SQL("sqlite:///students.db")
db.execute("DELETE FROM students")  # Clears the table

with open(argv[1], "r") as file:  # Open the file
    iterator = csv.DictReader(file)
    for dicts in iterator:  # Iterates through the dictionaries
        namelist = dicts["name"].split()  # Splits the name
        # Save each student inside the table recording his/her middle name as None if he/she doesn't have one
        if len(namelist) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       namelist[0], namelist[1], namelist[2], dicts["house"], dicts["birth"])
        else:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       namelist[0], None, namelist[1], dicts["house"], dicts["birth"])