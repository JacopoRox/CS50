# This function take a string as an argument and counts the all the letters in that string


def letterscount(text):
    n = 0
    for i in range(len(text)):
        if ord(text[i]) in range(97, 123):
            n += 1
    return n

# This function take a string as an argument and counts the all the words in that string


def wordscount(text):
    words = 1
    for i in range(len(text)):
        if text[i] == chr(32):
            words += 1

    return words

# This function take a string as an argument and counts the number of characters that end a sentence (. / ? / !)


def sentencescount(text):
    sentences = 0
    for i in range(len(text)):
        if text[i] in [chr(33), chr(46), chr(63)]:
            sentences += 1

    return sentences


text = input("Text: ").lower()  # Prompt the user for a text and store the answer in a string

L = (letterscount(text) * 100 / wordscount(text))  # Calculate the number of letters per 100 words
S = (sentencescount(text) * 100 / wordscount(text))  # Calculate the number of sentences per 100 words

index = round(0.0588 * L - 0.296 * S - 15.8)  # Calculate the Coleman-Liau index and rounds it

# Prints out the previously optained Grade
if 1 <= index <= 16:
    print(f"Grade {index}")

elif index < 1:
    print("Before Grade 1")

elif index > 16:
    print("Grade 16+")