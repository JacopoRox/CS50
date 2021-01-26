#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {   
            // Iterates through all the pixels and changes all the colours to the average of blue, green and red
            double avg = ((double) image[i][j].rgbtBlue + (double) image[i][j].rgbtGreen + (double) image[i][j].rgbtRed) / 3;
            int a = round(avg);
            image[i][j].rgbtBlue = a;
            image[i][j].rgbtGreen = a;
            image[i][j].rgbtRed = a;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {    
            // Iterates through all the pixels and changes it with is respective in the other half of the picture
            RGBTRIPLE temp = image[i][j]; // Temp is an array that stores the value of one of the pixel to be changed
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{   
    // Generates an exact copy of the image
    RGBTRIPLE duplicate[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            duplicate[i][j] = image[i][j];
        }
    }
    
    // Use the copy of the picture to get the values that this function use to blur the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avgBlue = 0;
            int avgGreen = 0;
            int avgRed = 0;
            int pixels = 0;
            for (int k = -1; k < 2; k++) // This loop goes through the 3x3 square around a pixel
            {
                for (int h = -1; h < 2; h++)
                {   
                    // As long as it does not exit the borders of the image
                    if (i + k >= 0 && i + k < height && j + h >= 0 && j + h < width)
                    {
                        avgBlue += duplicate[i + k][j + h].rgbtBlue;
                        avgGreen += duplicate[i + k][j + h].rgbtGreen;
                        avgRed += duplicate[i + k][j + h].rgbtRed;
                        pixels++; // If the pixel is not outside the border the number of pixels to average is updated
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            // Sets each colour value to the average
            image[i][j].rgbtBlue = round((float) avgBlue / pixels);
            image[i][j].rgbtGreen = round((float) avgGreen / pixels);
            image[i][j].rgbtRed = round((float) avgRed / pixels);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{   
    // Generates an exact copy of the image
    RGBTRIPLE duplicate[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            duplicate[i][j] = image[i][j];
        }
    }
    
    // Use the copy of the picture to get the values that this function use to blur the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int GxBlue = 0;
            int GxGreen = 0;
            int GxRed = 0;

            int GyBlue = 0;
            int GyGreen = 0;
            int GyRed = 0;

            // Calculate Gx for each colour
            for (int k = -1; k < 2; k++)
            {
                for (int h = -1; h < 2; h += 2)
                {
                    if (i + k < 0 || i + k >= height || j + h < 0 || j + h >= width)
                    {
                        continue;
                    }

                    else if (k != 0)
                    {
                        GxBlue += duplicate[i + k][j + h].rgbtBlue * h;
                        GxGreen += duplicate[i + k][j + h].rgbtGreen * h;
                        GxRed += duplicate[i + k][j + h].rgbtRed * h;
                    }

                    else
                    {
                        GxBlue += duplicate[i + k][j + h].rgbtBlue * h * 2;
                        GxGreen += duplicate[i + k][j + h].rgbtGreen * h * 2;
                        GxRed += duplicate[i + k][j + h].rgbtRed * h * 2;
                    }
                }
            }

            // Calculate Gy for each colour
            for (int k = -1; k < 2; k += 2)
            {
                for (int h = -1; h < 2; h++)
                {
                    if (i + k < 0 || i + k >= height || j + h < 0 || j + h >= width)
                    {
                        continue;
                    }

                    else if (h != 0)
                    {
                        GyBlue += duplicate[i + k][j + h].rgbtBlue * k;
                        GyGreen += duplicate[i + k][j + h].rgbtGreen * k;
                        GyRed += duplicate[i + k][j + h].rgbtRed * k;
                    }

                    else
                    {
                        GyBlue += duplicate[i + k][j + h].rgbtBlue * k * 2;
                        GyGreen += duplicate[i + k][j + h].rgbtGreen * k * 2;
                        GyRed += duplicate[i + k][j + h].rgbtRed * k * 2;
                    }
                }
            }
            // Set the values of the colours to the square root of the respective Gx^2 + Gy^2
            if (round(sqrt((double)(pow(GxBlue, 2) + pow(GyBlue, 2)))) <= 255)
            {
                image[i][j].rgbtBlue = round(sqrt((double)(pow(GxBlue, 2) + pow(GyBlue, 2))));
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }

            if (round(sqrt((double)(pow(GxGreen, 2) + pow(GyGreen, 2)))) <= 255)
            {
                image[i][j].rgbtGreen = round(sqrt((double)(pow(GxGreen, 2) + pow(GyGreen, 2))));
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }
            
            if (round(sqrt((double)(pow(GxRed, 2) + pow(GyRed, 2)))) <= 255)
            {
                image[i][j].rgbtRed = round(sqrt((double)(pow(GxRed, 2) + pow(GyRed, 2))));
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }    
        }
    }
}