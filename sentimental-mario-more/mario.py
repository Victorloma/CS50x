# Import get_int function from cs50 library
from cs50 import get_int


def main():
    # Run get_height function
    h = get_height()
    # Loop over height range
    for i in range(h):
        # Set initial space
        init_space = " " * (h - i - 1)
        # Calculate amount of blocks
        blocks = "#" * (i + 1)
        # Print line of spaces and blocks
        print(f"{init_space}{blocks}  {blocks}")


# Get user input for desired height
def get_height():
    # Keep asking until height is in range
    while True:
        h = get_int("Height: ")
        if h > 0 and h < 9:
            return h


# Run program
main()