#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long long ccnumber = get_long("What's your credit card number? ");
    printf("%lld\n", ccnumber);

    int d0 = ccnumber % 10;                    // Get DIGIT 1
    int d1 = ccnumber / 10 % 10;               // Get DIGIT 2
    int d2 = ccnumber / 100 % 10;              // Get DIGIT 3
    int d3 = ccnumber / 1000 % 10;             // Get DIGIT 4
    int d4 = ccnumber / 10000 % 10;            // Get DIGIT 5
    int d5 = ccnumber / 100000 % 10;           // Get DIGIT 6
    int d6 = ccnumber / 1000000 % 10;          // Get DIGIT 7
    int d7 = ccnumber / 10000000 % 10;         // Get DIGIT 8
    int d8 = ccnumber / 100000000 % 10;        // Get DIGIT 9
    int d9 = ccnumber / 1000000000 % 10;       // Get DIGIT 10
    int da = ccnumber / 10000000000 % 10;      // Get DIGIT 11
    int db = ccnumber / 100000000000 % 10;     // Get DIGIT 12
    int dc = ccnumber / 1000000000000 % 10;    // Get DIGIT 13
    int dd = ccnumber / 10000000000000 % 10;   // Get DIGIT 14
    int de = ccnumber / 100000000000000 % 10;  // Get DIGIT 15
    int df = ccnumber / 1000000000000000 % 10; // Get DIGIT 16

    // Determine the type of card

    // AMEX

    int amex;

    if (df == 0 && de == 3 && (dd == 4 || dd == 7))
    {
        amex = 1;
    }
    else
    {
        amex = 0;
    }

    // MASTERCARD

    int mastercard;

    if (df == 5 && (de == 1 || de == 2 || de == 3 || de == 4 || de == 5))
    {
        mastercard = 1;
    }
    else
    {
        mastercard = 0;
    }

    // VISA

    int visa;

    if (df == 4 || (df == 0 && de == 0 && dd == 0 && dc == 4))
    {
        visa = 1;
    }
    else
    {
        visa = 0;
    }

    // Detect non-consistent format as INVALID
    if (amex < 1 && mastercard < 1 && visa < 1)
    {
        printf("INVALID\n");
    }
    // Multiply every other digit by 2
    else
    {
        d1 *= 2;
        d3 *= 2;
        d5 *= 2;
        d7 *= 2;
        d9 *= 2;
        db *= 2;
        dd *= 2;
        df *= 2;

        // Separate the digits of every product
        int sd10 = d1 % 10;
        int sd11 = d1 / 10 % 10;
        int sd30 = d3 % 10;
        int sd31 = d3 / 10 % 10;
        int sd50 = d5 % 10;
        int sd51 = d5 / 10 % 10;
        int sd70 = d7 % 10;
        int sd71 = d7 / 10 % 10;
        int sd90 = d9 % 10;
        int sd91 = d9 / 10 % 10;
        int sdb0 = db % 10;
        int sdb1 = db / 10 % 10;
        int sdd0 = dd % 10;
        int sdd1 = dd / 10 % 10;
        int sdf0 = df % 10;
        int sdf1 = df / 10 % 10;

        // Add the digits of every produt

        int sdtotal = sd10 + sd11 + sd30 + sd31 + sd50 + sd51 + sd70 + sd71 + sd90 + sd91 + sdb0 +
                      sdb1 + sdd0 + sdd1 + sdf0 + sdf1;

        // Add the result to the numbers that weren't multiplied by 2

        int final_sum = sdtotal + d0 + d2 + d4 + d6 + d8 + da + dc + de;

        // Check if final_sum gives a valid result and show the type of card

        final_sum %= 10;
        if (final_sum == 0)
        {
            if (amex > 0)
            {
                printf("AMEX\n");
            }
            else if (mastercard > 0)
            {
                printf("MASTERCARD\n");
            }
            else if (visa > 0)
            {
                printf("VISA\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
