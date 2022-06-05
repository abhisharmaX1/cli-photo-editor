#include "helpers.h"
#include <math.h>

void swap(BYTE* a, BYTE* b);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int k = round((image[i][j].rgbtBlue +  image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = k;
            image[i][j].rgbtGreen = k;
            image[i][j].rgbtRed = k;

        }

    }


    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // TODO write the sepia function, make a copy first
            int r = image[i][j].rgbtRed, g = image[i][j].rgbtGreen, b = image[i][j].rgbtBlue;

            //not directly placed into image as may be greater than 255 and can't be stored in a byte.
            int sepiared = round(.393 * r + .769 * g + .189 * b);
            int sepiagreen = round(.349 * r + .686 * g + .168 * b);
            int sepiablue = round(.272 * r + .534 * g + .131 * b);

            // making sure each value is between 0 and 255
            if (sepiared > 255)
            {
                sepiared = 255;
            }
            if (sepiagreen > 255)
            {
                sepiagreen = 255;
            }
            if (sepiablue > 255)
            {
                sepiablue = 255;
            }

            //finally can be placed into image
            image[i][j].rgbtRed = sepiared;
            image[i][j].rgbtGreen = sepiagreen;
            image[i][j].rgbtBlue = sepiablue;

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j].rgbtRed, &image[i][width - j - 1].rgbtRed);
            swap(&image[i][j].rgbtGreen, &image[i][width - j - 1].rgbtGreen);
            swap(&image[i][j].rgbtBlue, &image[i][width - j - 1].rgbtBlue);

        }

    }

    return;
}

//Defining the swap function
void swap(BYTE *a, BYTE *b)
{
    BYTE tmp = *a;
    *a = *b;
    *b = tmp;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Making a copy of the original pixels
    RGBTRIPLE img[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img[i][j].rgbtRed = image[i][j].rgbtRed;
            img[i][j].rgbtGreen = image[i][j].rgbtGreen;
            img[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    
    //Modifying each pixel one by one
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r;
            int g;  
            int b; 
           
            if (i == 0)
            {
                // upper left most pixel
                if (j == 0)
                {
                    r = round((img[i][j].rgbtRed + img[i][j + 1].rgbtRed + img[i + 1][j].rgbtRed + img[i + 1][j + 1].rgbtRed) / 4.0);
                    g = round((img[i][j].rgbtGreen + img[i][j + 1].rgbtGreen + img[i + 1][j].rgbtGreen + img[i + 1][j + 1].rgbtGreen) / 4.0);
                    b = round((img[i][j].rgbtBlue + img[i][j + 1].rgbtBlue + img[i + 1][j].rgbtBlue + img[i + 1][j + 1].rgbtBlue) / 4.0);
                }
                // upper right most pixel
                else if (j == width - 1)
                {
                    r = round((img[i][j].rgbtRed + img[i][j - 1].rgbtRed + img[i + 1][j].rgbtRed + img[i + 1][j - 1].rgbtRed)/4.0);
                    g = round((img[i][j].rgbtGreen + img[i][j - 1].rgbtGreen + img[i + 1][j].rgbtGreen + img[i + 1][j - 1].rgbtGreen)/4.0);
                    b = round((img[i][j].rgbtBlue + img[i][j - 1].rgbtBlue + img[i + 1][j].rgbtBlue + img[i + 1][j - 1].rgbtBlue)/4.0);
                }
                // remaining pixels on the first row
                else 
                {
                    r = round((img[i][j - 1].rgbtRed + img[i][j].rgbtRed + img[i][j + 1].rgbtRed + img[i + 1][j - 1].rgbtRed + img[i + 1][j].rgbtRed + img[i + 1][j + 1].rgbtRed) / 6.0);
                    g = round((img[i][j - 1].rgbtGreen + img[i][j].rgbtGreen + img[i][j + 1].rgbtGreen + img[i + 1][j - 1].rgbtGreen + img[i + 1][j].rgbtGreen + img[i + 1][j + 1].rgbtGreen) / 6.0);
                    b = round((img[i][j - 1].rgbtBlue + img[i][j].rgbtBlue + img[i][j + 1].rgbtBlue + img[i + 1][j - 1].rgbtBlue + img[i + 1][j].rgbtBlue + img[i + 1][j + 1].rgbtBlue) / 6.0);
                }
            }
            else if (i == height - 1)
            {
                // lower left most pixel 
                if (j == 0)
                {
                    r = round((img[i - 1][j].rgbtRed + img[i - 1][j + 1].rgbtRed + img[i][j].rgbtRed + img[i][j + 1].rgbtRed) / 4.0);
                    g = round((img[i - 1][j].rgbtGreen + img[i - 1][j + 1].rgbtGreen + img[i][j].rgbtGreen + img[i][j + 1].rgbtGreen) / 4.0);
                    b = round((img[i - 1][j].rgbtBlue + img[i - 1][j + 1].rgbtBlue + img[i][j].rgbtBlue + img[i][j + 1].rgbtBlue) / 4.0);
                }
                // lower right most pixel
                else if (j == width - 1)
                {
                    r = round((img[i - 1][j - 1].rgbtRed + img[i - 1][j].rgbtRed  + img[i][j - 1].rgbtRed + img[i][j].rgbtRed) / 4.0);
                    g = round((img[i - 1][j - 1].rgbtGreen + img[i - 1][j].rgbtGreen + img[i][j - 1].rgbtGreen + img[i][j].rgbtGreen) / 4.0);
                    b = round((img[i - 1][j - 1].rgbtBlue + img[i - 1][j].rgbtBlue  + img[i][j - 1].rgbtBlue + img[i][j].rgbtBlue) / 4.0);
                }
                // remaining pixels on the last row
                else
                {
                   r = round((img[i - 1][j - 1].rgbtRed + img[i - 1][j].rgbtRed + img[i - 1][j + 1].rgbtRed + img[i][j - 1].rgbtRed + img[i][j].rgbtRed + img[i][j + 1].rgbtRed) / 6.0);
                   g = round((img[i - 1][j - 1].rgbtGreen + img[i - 1][j].rgbtGreen + img[i - 1][j + 1].rgbtGreen + img[i][j - 1].rgbtGreen + img[i][j].rgbtGreen + img[i][j + 1].rgbtGreen) / 6.0);
                   b = round((img[i - 1][j - 1].rgbtBlue + img[i - 1][j].rgbtBlue + img[i - 1][j + 1].rgbtBlue + img[i][j - 1].rgbtBlue + img[i][j].rgbtBlue + img[i][j + 1].rgbtBlue) / 6.0);
                }
            }
            // remaining pixels on left most column
            else if (j == 0)
            {
                r = round((img[i - 1][j].rgbtRed + img[i - 1][j + 1].rgbtRed + img[i][j].rgbtRed + img[i][j + 1].rgbtRed + img[i + 1][j].rgbtRed + img[i + 1][j + 1].rgbtRed) / 6.0);
                g = round((img[i - 1][j].rgbtGreen + img[i - 1][j + 1].rgbtGreen + img[i][j].rgbtGreen + img[i][j + 1].rgbtGreen + img[i + 1][j].rgbtGreen + img[i + 1][j + 1].rgbtGreen) / 6.0);
                b = round((img[i - 1][j].rgbtBlue + img[i - 1][j + 1].rgbtBlue + img[i][j].rgbtBlue + img[i][j + 1].rgbtBlue + img[i + 1][j].rgbtBlue + img[i + 1][j + 1].rgbtBlue) / 6.0);
            }
            // remaining pixels on right most column
            else if (j == width - 1)
            {
                r = round((img[i - 1][j - 1].rgbtRed + img[i - 1][j].rgbtRed + img[i][j - 1].rgbtRed + img[i][j].rgbtRed + img[i + 1][j - 1].rgbtRed + img[i + 1][j].rgbtRed) / 6.0);
                g = round((img[i - 1][j - 1].rgbtGreen + img[i - 1][j].rgbtGreen + img[i][j - 1].rgbtGreen + img[i][j].rgbtGreen + img[i + 1][j - 1].rgbtGreen + img[i + 1][j].rgbtGreen) / 6.0);
                b = round((img[i - 1][j - 1].rgbtBlue + img[i - 1][j].rgbtBlue + img[i][j - 1].rgbtBlue + img[i][j].rgbtBlue + img[i + 1][j - 1].rgbtBlue + img[i + 1][j].rgbtBlue) / 6.0);

            }
            // remaining pixels
            else
            {
                r = round((img[i - 1][j - 1].rgbtRed + img[i - 1][j].rgbtRed + img[i - 1][j + 1].rgbtRed + img[i][j - 1].rgbtRed + img[i][j].rgbtRed + img[i][j + 1].rgbtRed + img[i + 1][j - 1].rgbtRed + img[i + 1][j].rgbtRed + img[i + 1][j + 1].rgbtRed)/9.0);
                g = round((img[i - 1][j - 1].rgbtGreen + img[i - 1][j].rgbtGreen + img[i - 1][j + 1].rgbtGreen + img[i][j - 1].rgbtGreen + img[i][j].rgbtGreen + img[i][j + 1].rgbtGreen + img[i + 1][j - 1].rgbtGreen + img[i + 1][j].rgbtGreen + img[i + 1][j + 1].rgbtGreen)/9.0);
                b = round((img[i - 1][j - 1].rgbtBlue + img[i - 1][j].rgbtBlue + img[i - 1][j + 1].rgbtBlue + img[i][j - 1].rgbtBlue + img[i][j].rgbtBlue + img[i][j + 1].rgbtBlue + img[i + 1][j - 1].rgbtBlue + img[i + 1][j].rgbtBlue + img[i + 1][j + 1].rgbtBlue)/9.0);
            }
           
              image[i][j].rgbtRed = r;
              image[i][j].rgbtGreen = g;
              image[i][j].rgbtBlue = b;
        }
    }
    
    return;
}
