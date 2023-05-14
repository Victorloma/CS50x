# import cs50 library function get_string
from cs50 import get_string


def main():
    # Initialize variables
    letters = 0
    words = 1
    sentences = 0
    text = get_input()

    # Check for character occurences
    for char in text:
        if char.isalpha():
            letters += 1
        if char.isspace():
            words += 1
        if char == "." or char == "?" or char == "!":
            sentences += 1

    letperhun = letters / words * 100
    senperhun = sentences / words * 100

    # Calculate grade with Coleman-Liau index
    grade = round(0.0588 * letperhun - 0.296 * senperhun - 15.8)

    # Print result
    if grade > 16:
        print("Grade 16+")
    elif grade > 1:
        print("Grade {}".format(grade))
    else:
        print("Before Grade 1")


# Get user input function
def get_input():
    while True:
        s = get_string("Text: ")
        if s:
            return s


if __name__ == "__main__":
    main()