#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for text
    string text = get_string("Text: ");

    // Group characters into full words (count the number of words)

    int wordcount = 1;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            wordcount += 1;
        }
    }

    printf("%i\n", wordcount);
}
