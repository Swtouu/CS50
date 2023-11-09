import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print('Usage: python dna.py database_name.csv sequence_name.txt')
        return

    # TODO: Read database file into a variable
    with open(sys.argv[1], 'r') as database:
        db = list(csv.DictReader(database))
        # print(db)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as dna_sequence:
        dna = dna_sequence.read()
        # print(dna)

    STRs = list(db[0].keys())[1:]
    print(STRs)

    # TODO: Find longest match of each STR in DNA sequence
    matches = {STR: str(longest_match(dna, STR)) for STR in STRs}

    # TODO: Check database for matching profiles
    for detail in db:
        name = detail['name']
        del detail['name']

        if matches == detail:
            print(name)
            return

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
