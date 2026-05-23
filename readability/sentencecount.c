#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text: ");

    // Count sentences

    int sentcount = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((text[i] == '.' || text[i] == ';'|| text[i] == '?' || text[i] == '!'))
        {
            sentcount += 1;
        }
    }

printf("%i\n", sentcount);
}

