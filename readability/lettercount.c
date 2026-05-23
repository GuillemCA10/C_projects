#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text: ");

    // wordcount calculator
    int wordcount = 1;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            wordcount += 1;
        }
    }
    // letter calculator
    int length = strlen(text);
    length = length - (wordcount - 1);
    printf("%i\n", length);
}
