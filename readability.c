#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int letters = 0;
    int words = 1;
    int sentences = 0;
    string s;

    // Prompt for user input longer than 1 character.
    do
    {
        s = get_string("Text: ");
    }
    while (strlen(s) < 1);

    // Check each character
    for (int i = 0, l = strlen(s); i < l; i++)
    {
        // Increment count if letter
        if (isalpha(s[i]))
        {
            letters++;
        }

        // Increment count if space
        if (isspace(s[i]))
        {
            words++;
        }

        // Increment count if end of sentence
        if (s[i] == '.' || s[i] == '?' || s[i] == '!')
        {
            sentences++;
        }
    }
    // Calculate amount of letters per 100 words.
    float letperhun = (float) letters / words * 100;

    // Calculate amount of sentences per 100 words.
    float senperhun = (float) sentences / words * 100;

    // Calculate grade and round number
    int grade = round(0.0588 * letperhun - 0.296 * senperhun - 15.8);

    // Print grade
    if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade > 1)
    {
        printf("Grade %i\n", grade);
    }
    else
    {
        printf("Before Grade 1\n");
    }
}