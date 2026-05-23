#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text: ");

    // not letter char counter

    int notletter = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((text[i] < 'A') || (text[i] > 'Z' && text[i] < 'a') || (text[i] > 'z'))
        {
            notletter += 1;
        }
    }
    printf("notletter %i\n", notletter);


    // letter calculator
    int letcount = strlen(text);
    letcount -= notletter; printf("letcount - notletter %i\n", letcount);
}
