from cs50 import get_int


def pyramid(height):
    tmp = 1
    while tmp <= height:
        print(" " * (height - tmp), end="")  # prints the correct amount of spaces
        print("#" * tmp, end="")  # prints the correct amount of #s per level
        print("  ", end="")  # prints the gap between the #s
        print("#" * tmp)  # prints the correct amount of #s again and a new line
        tmp += 1


while True:
    height = get_int("Height:\n")  # prompt the user for a positive int
    if height > 0 and height < 9:  # if it is not in the correct range it keeps prompting
        break

pyramid(height)
