#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Define the color you want to use for replacing black pixels
    RGBTRIPLE newColor;
    newColor.rgbtRed = 255;   // Red component
    newColor.rgbtGreen = 0;   // Green component
    newColor.rgbtBlue = 0;    // Blue component

    // Iterate through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Check if the pixel is black (all color channels are 0)
            if (image[i][j].rgbtRed == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtBlue == 0)
            {
                // Replace the black pixel with the new color
                image[i][j] = newColor;
            }
        }
    }
}
