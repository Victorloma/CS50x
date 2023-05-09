#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Prompt for height:
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //Loop to make pyramid
    for (int i = height - 1; i >= 0; i--)
    {
        //Print starting whitespaces every line
        for (int j = 0; j < i; j++)
        {
            printf(" ");
        }

        //Print first set of hashes of the line
        for (int h = 0; h < height - i; h++)
        {
            printf("#");
        }

        //Print spacing between sets of hashes
        printf("  ");

        // Print first set of hashes of the line
        for (int h = 0; h < height - i; h++)
        {
            printf("#");
        }

        //Print next line
        printf("\n");
    }
}