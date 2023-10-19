#include "helpers.h"
#include <math.h>
#include <stdlib.h>

typedef uint8_t bool;
#define true 1
#define false 0


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    uint8_t avg;
    float sum;
    for(int i  = 0; i < height; i++)
    {
        for(int j  = 0; j < width; j++)
        {
            sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            avg = round(sum/3);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[width];
    for(int i  = 0; i < height; i++)
    {
        for(int j  = 0; j < width; j++)
        {
            temp[j] =  image[i][j];
        }
        for(int j  = 0; j < width; j++)
        {
            image[i][j] = temp[width - j -1];
        }
    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumBlue;
    int sumGreen;
    int sumRed;
    float counter;
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            counter = 0.00;

            for (int k = -1; k < 2; k++)
            {
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }

                    sumBlue += image[j + k][i + h].rgbtBlue;
                    sumGreen += image[j + k][i + h].rgbtGreen;
                    sumRed += image[j + k][i + h].rgbtRed;
                    counter++;
                }
            }

            temp[j][i].rgbtBlue = round(sumBlue / counter);
            temp[j][i].rgbtGreen = round(sumGreen / counter);
            temp[j][i].rgbtRed = round(sumRed / counter);
        }
    }

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
            image[j][i].rgbtRed = temp[j][i].rgbtRed;
        }
    }
}


int limit(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    float sumBlueY;
    float sumGreenY;
    float sumRedY;
    float sumBlueX;
    float sumGreenX;
    float sumRedX;
    float modifierX;
    float modifierY;

    RGBTRIPLE temp[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            //Resets values for every pixel
            sumBlueY = 0.0;
            sumGreenY = 0.0;
            sumRedY = 0.0;
            sumBlueX = 0.0;
            sumGreenX = 0.0;
            sumRedX = 0.0;

            for (int k = -1; k < 2; k++)
            {
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }

                    modifierX = (k + 1 * k - k * abs(h));
                    modifierY = (h + 1 * h - h * abs(k));

                    sumBlueX += image[j + k][i + h].rgbtBlue * modifierX;
                    sumGreenX += image[j + k][i + h].rgbtGreen * modifierX;
                    sumRedX += image[j + k][i + h].rgbtRed * modifierX;

                    sumBlueY += image[j + k][i + h].rgbtBlue * modifierY;
                    sumGreenY += image[j + k][i + h].rgbtGreen * modifierY;
                    sumRedY += image[j + k][i + h].rgbtRed * modifierY;
                }
            }

            temp[j][i].rgbtBlue = limit(round(sqrt(sumBlueX * sumBlueX + sumBlueY * sumBlueY)));
            temp[j][i].rgbtGreen = limit(round(sqrt(sumGreenX * sumGreenX + sumGreenY * sumGreenY)));
            temp[j][i].rgbtRed = limit(round(sqrt(sumRedX * sumRedX + sumRedY * sumRedY)));
        }
    }

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
            image[j][i].rgbtRed = temp[j][i].rgbtRed;
        }
    }
}
