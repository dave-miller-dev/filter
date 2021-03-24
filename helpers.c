#include "helpers.h"
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each row of pixels.
    for (int x = 0; x < height; x++)
    {
        // Iterate through each pixel on the row.
        for (int y = 0; y < width; y++)
        {
            // Find the average value for the current pixel.
            float average = round((image[x][y].rgbtRed + image[x][y].rgbtGreen + image[x][y].rgbtBlue) / 3.0);

            // Apply the new value (average) to the current pixel.
            image[x][y].rgbtRed = (int) average;
            image[x][y].rgbtGreen = (int) average;
            image[x][y].rgbtBlue = (int) average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each row of pixels.
    for (int x = 0; x < height; x++)
    {
        // Iterate through each pixel on the row.
        for (int y = 0; y < width; y++)
        {
            // Take RGB values of current pixel, compute new values using sepia formula.
            float sepiaRed = round((0.393 * image[x][y].rgbtRed) + (0.769 * image[x][y].rgbtGreen) + (0.189 * image[x][y].rgbtBlue));
            float sepiaGreen = round((0.349 * image[x][y].rgbtRed) + (0.686 * image[x][y].rgbtGreen) + (0.168 * image[x][y].rgbtBlue));
            float sepiaBlue = round((0.272 * image[x][y].rgbtRed) + (0.534 * image[x][y].rgbtGreen) + (0.131 * image[x][y].rgbtBlue));

            // Checking if values are out of range for each RGB colour.
            if (sepiaRed > 255.0)
            {
                // If out of range, apply maximum value.
                sepiaRed = 255.0;
            }

            if (sepiaGreen > 255.0)
            {
                // If out of range, apply maximum value.
                sepiaGreen = 255.0;
            }

            if (sepiaBlue > 255.0)
            {
                // If out of range, apply maximum value.
                sepiaBlue = 255.0;
            }

            // Apply final RGB values back for each pixel.
            image[x][y].rgbtRed = (int) sepiaRed;
            image[x][y].rgbtGreen = (int) sepiaGreen;
            image[x][y].rgbtBlue = (int) sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < (width / 2); y++)
        {
            RGBTRIPLE temp = image[x][y];

            image[x][y] = image[x][width - (y + 1)];
            image[x][width - (y + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumRed;
    int sumGreen;
    int sumBlue;
    float counter;

    // Make a copy of the original image.
    RGBTRIPLE temp[height][width];

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            sumRed = 0;
            sumGreen = 0;
            sumBlue = 0;
            counter = 0.00;

            // Sum value of pixel and surround pixels. Stops if it goes outside the pic.
            for (int i = -1; i < 2; i++)
            {
                if (y + i < 0 || y + i > height - 1)
                {
                    continue;
                }

                for (int j = -1; j < 2; j++)
                {
                    if (x + j < 0 || x + j > width - 1)
                    {
                        continue;
                    }

                    sumRed += image[x + j][y + i].rgbtRed;
                    sumGreen += image[x + j][y + i].rgbtGreen;
                    sumBlue += image[x + j][y + i].rgbtBlue;
                    counter++;
                }
            }

            // Average the sum of values for RGB.
            temp[x][y].rgbtRed = round(sumRed / counter);
            temp[x][y].rgbtGreen = round(sumGreen / counter);
            temp[x][y].rgbtBlue = round(sumBlue / counter);
        }
    }

    //Apply values from temporary image to original.
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}
