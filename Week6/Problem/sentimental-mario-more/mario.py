while True:
    try:
        h = int(input("Height: "))
        if 1 <= h <= 8:
            break
        else:
            print("Height must be between 1 and 8.")
    except ValueError:
        print("Invalid input. Please enter a valid integer between 1 and 8.")

for i in range(0, h):
    n_spaces = h - (i + 1)
    n_blocks = i + 1

    print(" " * n_spaces, end="")
    print("#" * n_blocks, end="")
    print("  ", end="")
    print("#" * n_blocks)
