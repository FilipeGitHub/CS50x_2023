#include "helpers.h"
#include <stdio.h>

// Change all black pixels to yellow
void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (image[i][j].rgbtBlue == 0)
            {
                image[i][j].rgbtBlue = 255;
            }
        }
    }

}