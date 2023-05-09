#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Prompt for input
    long cardnum = -1;
    do
    {
        cardnum = get_long("Number: ");
    }
    while (cardnum < 0);

    //Calculate checksum
    int sum = 0;

    //Sum of every other digit starting with second to last
    for (long i = 100; i < cardnum * 10; i *= 100)
    {
        long rem = ((cardnum % i) / (i / 10)) * 2;
        if (rem >= 10)
        {
            sum += rem % 10;
            sum += rem / 10;
        }
        else
        {
            sum += rem;
        }
    }

    //Add remaining digits to sum
    for (long i = 10; i < cardnum * 10; i *= 100)
    {
        long rem = ((cardnum % i) / (i / 10));
        if (rem > 10)
        {
            sum += rem % 10;
            sum += rem / 10;
        }
        else
        {
            sum += rem;
        }
    }

    // Check card length and starting digits. Print AMEX, MASTERCARD, VISA or INVALID
    if ((sum % 10 == 0) && (sum > 0))
    {
        // Check if card is MASTERCARD
        if ((cardnum <= 5599999999999999) && (cardnum >= 5100000000000000))
        {
            printf("MASTERCARD\n");
        }
        // Otherwise check if card is AMEX
        else if ((cardnum >= 340000000000000 && cardnum <= 349999999999999) || (cardnum >= 370000000000000 && cardnum <= 379999999999999))
        {
            printf("AMEX\n");
        }
        // Otherwise check if card is VISA
        else if ((cardnum >= 4000000000000 && cardnum <= 4999999999999) || (cardnum >= 4000000000000000 && cardnum <= 4999999999999999))
        {
            printf("VISA\n");
        }
        // Otherwise card is INVALID
        else
        {
            printf("INVALID\n");
        }
    }
    // If sum == 0 and remainder != 0 => card is INVALID
    else
    {
        printf("INVALID\n");
    }
}