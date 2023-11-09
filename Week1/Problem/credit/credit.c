#include <stdio.h>
#include <cs50.h>

int main(void) {
    long long card_number = get_long("Card Number: ");
    // long long card_number = 371449635398431;

    long long first_two_digits = card_number;
    while (first_two_digits >= 100) {
        first_two_digits /= 10;
    }

    int isAmex = 0;
    int isMasterCard = 0;

    if (first_two_digits == 37 || first_two_digits == 34) {
        isAmex = 1;
    } else if (first_two_digits >= 51 && first_two_digits <= 55) {
        isMasterCard = 1;
    }

    // Count the number of digits in the card number
    long long temp = card_number;
    int count = 0;
    while (temp > 0) {
        temp /= 10;
        count++;
    }

    // Create an integer array to store the individual digits
    int digits[count];

    // Reset temp and extract digits into the array
    temp = card_number;
    for (int i = count - 1; i >= 0; i--) {
        digits[i] = temp % 10;
        temp /= 10;
    }

    // Multiply every other digit by 2, starting from the second-to-last digit
    for (int i = count - 2; i >= 0; i -= 2) {
        digits[i] *= 2;

        // If the result is a two-digit number, add the digits together
        if (digits[i] > 9) {
            digits[i] = digits[i] % 10 + digits[i] / 10;
        }
    }

    // Calculate the sum of all the digits
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += digits[i];
    }

    // Check if the last digit in the sum is 0 and identify the card type
    if (sum % 10 == 0) {
        // printf("count is %d\n", count);
        // printf("digit[0] is %d\n", digits[0]);
        // printf("digit[1] is %d\n", digits[1]);
        if ((count == 15 && digits[0]/2 == 3 && (digits[1] == 4 || digits[1] == 7)) || (count == 15 && isAmex == 1)) {
            printf("AMEX\n");
        } else if ((count == 16 && digits[0]/2 == 5 && (digits[1] >= 1 && digits[1] <= 5)) || (count == 16 && isMasterCard == 1)) {
            printf("MASTERCARD\n");
        } else if ((count == 13 || count == 16) && (digits[0]/2 == 4 || digits[0] == 4)) {
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
    } else {
        printf("INVALID\n");
    }

    return 0;
}
