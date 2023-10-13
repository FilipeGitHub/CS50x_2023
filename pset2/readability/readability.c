#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string text;
    do
    {
        text = get_string("Text: ");
    }
    while (strlen(text) == 0);

    double letters = 0;
    double words = 1;
    double senteces = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters += 1;
        }
        else if (isspace(text[i]))
        {
            words += 1;
        }
        else if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))
        {
            senteces += 1;
        }
    }

    double l = (letters / words) * 100;
    double s = (senteces / words) * 100;

    int index = round(0.0588 * l - 0.296 * s - 15.8);
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}