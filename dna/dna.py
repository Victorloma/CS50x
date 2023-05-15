import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python input.csv dna-sequence.txt")

    # TODO: Read database file into a variable
    persons = []
    file = sys.argv[1]
    with open(file) as f:
        input = csv.DictReader(f)
        for row in input:
            persons.append(row)

    # TODO: Read DNA sequence file into a variable
    f = open(sys.argv[2], "r")
    dna = f.read()

    # TODO: Find longest match of each STR in DNA sequence
    profile = {}
    keys = persons[0].keys()

    for key in keys:
        if key != "name":
            profile[key] = str(longest_match(dna, key))

    # TODO: Check database for matching profiles
    for person in persons:
        name = person.pop("name")
        if person == profile:
            print(name)
            return

    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
