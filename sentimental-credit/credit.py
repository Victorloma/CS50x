# Import cs50 library
from cs50 import get_int


def main():
    # Execute prompt for user input
    cardnum = get_cardnum()
    # Cast cardnum to string for easy comparison
    cardstr = str(cardnum)
    # Calculate length of card number
    length = len(cardstr)

    # Initiate checksum
    sum = 0
    cardcpy = cardnum

    # Loop through every character
    for i in range(length):
        # For every second character add modulo of 10
        if i % 2 == 0:
            sum += cardcpy % 10
        # When character count is uneven add every digit of the double of the modulo of 10
        else:
            dig = cardcpy % 10 * 2
            sum += dig // 10 + dig % 10
        # Divide cardcpy by 10 and floor the value to an integer,
        # this makes the next iteration of the loop work with the next digit
        cardcpy //= 10

    # Check card length and starting digits. Print AMEX, MASTERCARD, VISA or INVALID
    if (sum % 10 == 0) and (sum > 0):
        # Check if card is MASTERCARD
        if (length == 16) and (cardstr[0:2] in ['51', '52', '53', '54', '55']):
            print("MASTERCARD")
        # Otherwise check if card is AMEX
        elif (length == 15) and (cardstr[0:2] in ['34', '37']):
            print("AMEX")
        # Otherwise check if card is VISA
        elif (length in [13, 16]) and (cardstr[0] == '4'):
            print("VISA")
        # Otherwise card is INVALID
        else:
            print("INVALID")
    # If sum == 0 and remainder != 0 => card is INVALID
    else:
        print("INVALID")


# Prompt for input
def get_cardnum():
    while True:
        cardnum = get_int("Number: ")
        if cardnum > 0:
            return cardnum


main()