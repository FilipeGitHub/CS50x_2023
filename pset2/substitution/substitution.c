#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// W asci A to 66
// Z to 90
// a to 97  -----26
// z to 122

int main(int argc, string argv[])
{
    if ((argc != 2) || strlen(argv[1]) != 26)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }

    }

    //repeted caracters
    int count = 0;
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        count = 0;
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                count++;
            }
        }
        if (count > 1)
        {
            printf("Key must not contain repeated caracters.\n");
            return 1;
        }
    }


    string plaintext = get_string("plaintext: ");
    int asciiCode;
    int magicNum;

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (islower(plaintext[i]))
            {
                magicNum = 97;
                asciiCode = plaintext[i] - 97;
                plaintext[i] = tolower(argv[1][asciiCode]);
            }
            else
            {
                magicNum = 66;
                asciiCode = plaintext[i] - 66;
                plaintext[i] = toupper(argv[1][asciiCode + 1]);
            }
        }
    }
    printf("ciphertext: %s\n", plaintext);
}