from cs50 import get_int

# This function operates on thirteen digits numbers


def thirteen(number):

    x = 100
    digits = 0
    others = 0
    while x < 10**13:
        a = int((number % x) / (x / 10)) * 2  # doubles each other digit
        a1 = a % 10
        a2 = (a % 100) / 10
        others = others + int(a1) + int(a2)  # and stores the digits from the double in a variable called others
        x *= 100

    y = 10
    while y < 10**14:
        b = int((number % y) / (y / 10))  # also stores the digits not previously doubled in a variable called digits
        digits = digits + b
        y *= 100
    # if the card is valid prints out VISA
    if (digits + others) % 10 == 0 and int(number / 10**12) == 4:
        print("VISA")
    else:
        print("INVALID")

# This function operates on fifteen digits numbers


def fifteen(number):

    x = 100
    digits = 0
    others = 0
    while x < 10**15:
        a = int((number % x) / (x / 10)) * 2  # doubles each other digit
        a1 = a % 10
        a2 = (a % 100) / 10
        others = others + int(a1) + int(a2)  # and stores the digits from the double in a variable called others
        x *= 100

    y = 10
    while y < 10**16:
        b = int((number % y) / (y / 10))
        digits = digits + b  # also stores the digits not previously doubled in a variable called digits
        y *= 100
    # if the card is valid prints out AMEX
    if (digits + others) % 10 == 0:
        if int(number / 10**13) == 34 or int(number / 10**13) == 37:
            print("AMEX")
        else:
            print("INVALID")
    else:
        print("INVALID")

# This function operates on sixteen digits numbers


def sixteen(number):

    x = 100
    digits = 0
    others = 0
    while x < 10**17:
        a = int((number % x) / (x / 10)) * 2  # doubles each other digit
        a1 = a % 10
        a2 = (a % 100) / 10
        others = others + int(a1) + int(a2)  # and stores the digits from the double in a variable called others
        x *= 100

    y = 10
    while y < 10**16:
        b = int((number % y) / (y / 10))
        digits = digits + b  # also stores the digits not previously doubled in a variable called digits
        y *= 100
    # if the card is valid prints out MASTERCARD or VISA depending of the first digits
    if (digits + others) % 10 == 0:
        if int(number / 10**14) > 50 and int(number / 10**14) < 56:
            print("MASTERCARD")
        elif int((number / 10**15)) == 4:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


while True:
    number = get_int("Number: ")
    if number >= 0:
        break
# The correct function is called upon a number of the correct size
if number >= 10**12 and number < 10**13:
    thirteen(number)
elif number >= 10**14 and number < 10**15:
    fifteen(number)
elif number >= 10**15 and number < 10**16:
    sixteen(number)
else:
    print("INVALID")  # if the number as an invalid size prints out INVALID