#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{

    // Prompt user for text                                             SOLVED
    string text = get_string("Text: ");

    // Group characters into full words (count the number of words)     SOLVED

    int wordcount = 1;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            wordcount += 1;
        }
    }

    // Count the number of letters (needs notletter counter)             SOLVED

    // not letter char counter

    int notletter = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((text[i] < 'A') || (text[i] > 'Z' && text[i] < 'a') || (text[i] > 'z'))
        {
            notletter += 1;
        }
    }

    // letter calculator
    int letcount = strlen(text);
    letcount -= notletter;

    // Count the number of sentences

    int sentcount = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((text[i] == '.' || text[i] == '?' || text[i] == '!'))
        {
            sentcount += 1;
        }
    }

    // Calculate average number of letters per 100 words & average number of sentences per 100 words

    float L;
    float S;

    L = ((float) letcount  / wordcount) * 100;
    S = ((float) sentcount / wordcount) * 100;

    /*Calculate reading level (OG formula index = 0.0588 * L - 0.296 * S - 15.8),
    where L is the average number of letters per 100 words in the text,
    and S is the average number of sentences per 100 words in the text.*/

    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = (int) round(index);

    // Print result
    if (grade >= 1 && index < 16)
    {
        printf("Grade %i\n", grade);
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}
