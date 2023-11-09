# Take the card number as input
card_number = int(input("Card Number: "))
# card_number = 371449635398431  # Example card number

# Extract the first two digits of the card number
first_two_digits = card_number
while first_two_digits >= 100:
    first_two_digits //= 10

# Initialize flags for identifying card types
isAmex = False
isMasterCard = False

if first_two_digits == 37 or first_two_digits == 34:
    isAmex = True
elif 51 <= first_two_digits <= 55:
    isMasterCard = True

# Count the number of digits in the card number
temp = card_number
count = 0
while temp > 0:
    temp //= 10
    count += 1

# Create a list to store the individual digits
digits = [0] * count

# Reset temp and extract digits into the list
temp = card_number
for i in range(count - 1, -1, -1):
    digits[i] = temp % 10
    temp //= 10

# Multiply every other digit by 2, starting from the second-to-last digit
for i in range(count - 2, -1, -2):
    digits[i] *= 2

    # If the result is a two-digit number, add the digits together
    if digits[i] > 9:
        digits[i] = digits[i] % 10 + digits[i] // 10

# Calculate the sum of all the digits
sum_of_digits = sum(digits)

# Check if the last digit in the sum is 0 and identify the card type
if sum_of_digits % 10 == 0:
    if (count == 15 and digits[0] // 2 == 3 and (digits[1] == 4 or digits[1] == 7)) or (count == 15 and isAmex):
        print("AMEX")
    elif (count == 16 and digits[0] // 2 == 5 and 1 <= digits[1] <= 5) or (count == 16 and isMasterCard):
        print("MASTERCARD")
    elif (count == 13 or count == 16) and (digits[0] // 2 == 4 or digits[0] == 4):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
