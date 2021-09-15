import csv
from sys import argv

if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")

data = open(argv[1])
datar = csv.reader(data)  # creates an object that iterates over the csv file rows as lists
STRs = {}  # here it generates a dictionary which is gonna be filled with the STRs the program is going to look for
for lists in datar:
    if lists[0] == "name":
        for i in range(1, len(lists)):
            STRs[lists[i]] = 0
    break
seqfile = open(argv[2])  # opens the sequence file
sequence = seqfile.read()  # and reads it

for j in STRs:  # for each sequence stored in the STRs dictionary it looks for the max number of repetions
    maxrep = 0
    for i in range(len(sequence)):  # iterates through the sequence
        if sequence[i: i + len(j)] == j:  # if the substring is an STR
            rep = 0
            for h in range(i, len(sequence), len(j)):  # iterates through the sequence by blocks of the lenght of the STR
                if sequence[h: h + len(j)] == j:  # keeps adding to the variable rep
                    rep += 1
                elif rep > maxrep:  # until the STRs is over, than checks if the rep is the longest yet
                    maxrep = rep  # if so memorizes it
                    break
                else:  # else the maxrep stays the same
                    break
    STRs[j] = maxrep  # every STRs max repetetion gets memorized

# Closes the file utilized so far
seqfile.close()
data.close()

data = open(argv[1])  # open the file again
datadict = csv.DictReader(data)  # and reads it into a iterator of dictionaries


for dicts in datadict:  # for each dictionary
    check = 0
    for keys in dicts.keys():  # for each key in the dictionary
        for strs, rep in STRs.items():  # for each STRs
            if strs == keys:  # if the STR is the same
                if STRs[strs] == int(dicts[keys]):  # if the repetions are correct
                    check += 1  # register a success
                    break
    if check == len(dicts) - 1:  # if the person corresponding to the dictionary has all matches
        print(dicts['name'])  # prints his/her name and exit
        data.close()
        exit()
data.close()
print("No match")  # if no match is found prints "No match"
