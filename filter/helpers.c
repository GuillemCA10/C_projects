#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // 1. Iterate through every row
    for (int i = 0; i < height; i++)
    {
        // 2. Iterate through every pixel within that row
        for (int j = 0; j < width; j++)
        {
            // Get the average value of b, g, and r for each pixel
            BYTE average = (BYTE) round(
                (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // Set b, g, an r levels to the average value to convert to greyscale
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = average;
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
            BYTE originalRed = image[i][j].rgbtRed;
            BYTE originalGreen = image[i][j].rgbtGreen;
            BYTE originalBlue = image[i][j].rgbtBlue;

            double sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            double sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            double sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

            if (sepiaRed > 255)
                sepiaRed = 255;
            if (sepiaGreen > 255)
                sepiaGreen = 255;
            if (sepiaBlue > 255)
                sepiaBlue = 255;

            image[i][j].rgbtRed = (BYTE) round(sepiaRed);
            image[i][j].rgbtGreen = (BYTE) round(sepiaGreen);
            image[i][j].rgbtBlue = (BYTE) round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Pixel[0] of [height][width] should swap places with the last of the row. Pixel[1] with last -
    // 1, and so on.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE stored_pixel = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = image[i][j];
            image[i][j] = stored_pixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create an array that stores the original values of all pixels
    RGBTRIPLE ogpixel[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ogpixel[i][j] = image[i][j];
        }
    }
    // Create an array that will store the average values of a pixel and its neighbors
    RGBTRIPLE avpixel[height][width];

    // Take each individual r,g, and b subpixel and average its value with the value of all its
    // neighboring r,g, and b subpixels.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Filter middle pixels
            if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
            {
                avpixel[i][j].rgbtRed =
                    (BYTE) round((ogpixel[i - 1][j - 1].rgbtRed + ogpixel[i - 1][j].rgbtRed +
                                  ogpixel[i - 1][j + 1].rgbtRed + ogpixel[i][j - 1].rgbtRed +
                                  ogpixel[i][j].rgbtRed + ogpixel[i][j + 1].rgbtRed +
                                  ogpixel[i + 1][j - 1].rgbtRed + ogpixel[i + 1][j].rgbtRed +
                                  ogpixel[i + 1][j + 1].rgbtRed) /
                                 9.0);
                avpixel[i][j].rgbtGreen =
                    (BYTE) round((ogpixel[i - 1][j - 1].rgbtGreen + ogpixel[i - 1][j].rgbtGreen +
                                  ogpixel[i - 1][j + 1].rgbtGreen + ogpixel[i][j - 1].rgbtGreen +
                                  ogpixel[i][j].rgbtGreen + ogpixel[i][j + 1].rgbtGreen +
                                  ogpixel[i + 1][j - 1].rgbtGreen + ogpixel[i + 1][j].rgbtGreen +
                                  ogpixel[i + 1][j + 1].rgbtGreen) /
                                 9.0);
                avpixel[i][j].rgbtBlue =
                    (BYTE) round((ogpixel[i - 1][j - 1].rgbtBlue + ogpixel[i - 1][j].rgbtBlue +
                                  ogpixel[i - 1][j + 1].rgbtBlue + ogpixel[i][j - 1].rgbtBlue +
                                  ogpixel[i][j].rgbtBlue + ogpixel[i][j + 1].rgbtBlue +
                                  ogpixel[i + 1][j - 1].rgbtBlue + ogpixel[i + 1][j].rgbtBlue +
                                  ogpixel[i + 1][j + 1].rgbtBlue) /
                                 9.0);
            }
            // Filter left edge pixels
            if (i != 0 && i != height - 1 && j == 0)
            {
                avpixel[i][j].rgbtRed =
                    (BYTE) round((ogpixel[i - 1][j].rgbtRed + ogpixel[i - 1][j + 1].rgbtRed +
                                  ogpixel[i][j].rgbtRed + ogpixel[i][j + 1].rgbtRed +
                                  ogpixel[i + 1][j].rgbtRed + ogpixel[i + 1][j + 1].rgbtRed) /
                                 6.0);
                avpixel[i][j].rgbtGreen =
                    (BYTE) round((ogpixel[i - 1][j].rgbtGreen + ogpixel[i - 1][j + 1].rgbtGreen +
                                  ogpixel[i][j].rgbtGreen + ogpixel[i][j + 1].rgbtGreen +
                                  ogpixel[i + 1][j].rgbtGreen + ogpixel[i + 1][j + 1].rgbtGreen) /
                                 6.0);
                avpixel[i][j].rgbtBlue =
                    (BYTE) round((ogpixel[i - 1][j].rgbtBlue + ogpixel[i - 1][j + 1].rgbtBlue +
                                  ogpixel[i][j].rgbtBlue + ogpixel[i][j + 1].rgbtBlue +
                                  ogpixel[i + 1][j].rgbtBlue + ogpixel[i + 1][j + 1].rgbtBlue) /
                                 6.0);
            }
            // Filter right edge pixels
            if (i != 0 && i != height - 1 && j == width - 1)
            {
                avpixel[i][j].rgbtRed =
                    (BYTE) round((ogpixel[i - 1][j - 1].rgbtRed + ogpixel[i - 1][j].rgbtRed +
                                  ogpixel[i][j - 1].rgbtRed + ogpixel[i][j].rgbtRed +
                                  ogpixel[i + 1][j - 1].rgbtRed + ogpixel[i + 1][j].rgbtRed) /
                                 6.0);
                avpixel[i][j].rgbtGreen =
                    (BYTE) round((ogpixel[i - 1][j - 1].rgbtGreen + ogpixel[i - 1][j].rgbtGreen +
                                  ogpixel[i][j - 1].rgbtGreen + ogpixel[i][j].rgbtGreen +
                                  ogpixel[i + 1][j - 1].rgbtGreen + ogpixel[i + 1][j].rgbtGreen) /
                                 6.0);
                avpixel[i][j].rgbtBlue =
                    (BYTE) round((ogpixel[i - 1][j - 1].rgbtBlue + ogpixel[i - 1][j].rgbtBlue +
                                  ogpixel[i][j - 1].rgbtBlue + ogpixel[i][j].rgbtBlue +
                                  ogpixel[i + 1][j - 1].rgbtBlue + ogpixel[i + 1][j].rgbtBlue) /
                                 6.0);
            }
            // Filter top edge pixels
            if (i == 0 && j != 0 && j != width - 1)
            {
                avpixel[i][j].rgbtRed =
                    (BYTE) round((ogpixel[i][j - 1].rgbtRed + ogpixel[i][j].rgbtRed +
                                  ogpixel[i][j + 1].rgbtRed + ogpixel[i + 1][j - 1].rgbtRed +
                                  ogpixel[i + 1][j].rgbtRed + ogpixel[i + 1][j + 1].rgbtRed) /
                                 6.0);
                avpixel[i][j].rgbtGreen =
                    (BYTE) round((ogpixel[i][j - 1].rgbtGreen + ogpixel[i][j].rgbtGreen +
                                  ogpixel[i][j + 1].rgbtGreen + ogpixel[i + 1][j - 1].rgbtGreen +
                                  ogpixel[i + 1][j].rgbtGreen + ogpixel[i + 1][j + 1].rgbtGreen) /
                                 6.0);
                avpixel[i][j].rgbtBlue =
                    (BYTE) round((ogpixel[i][j - 1].rgbtBlue + ogpixel[i][j].rgbtBlue +
                                  ogpixel[i][j + 1].rgbtBlue + ogpixel[i + 1][j - 1].rgbtBlue +
                                  ogpixel[i + 1][j].rgbtBlue + ogpixel[i + 1][j + 1].rgbtBlue) /
                                 6.0);
            }
            // Filter bottom edge pixels
            if (i == height - 1 && j != 0 && j != width - 1)
            {
                avpixel[i][j].rgbtRed =
                    (BYTE) round((ogpixel[i - 1][j - 1].rgbtRed + ogpixel[i - 1][j].rgbtRed +
                                  ogpixel[i - 1][j + 1].rgbtRed + ogpixel[i][j - 1].rgbtRed +
                                  ogpixel[i][j].rgbtRed + ogpixel[i][j + 1].rgbtRed) /
                                 6.0);
                avpixel[i][j].rgbtGreen =
                    (BYTE) round((ogpixel[i - 1][j - 1].rgbtGreen + ogpixel[i - 1][j].rgbtGreen +
                                  ogpixel[i - 1][j + 1].rgbtGreen + ogpixel[i][j - 1].rgbtGreen +
                                  ogpixel[i][j].rgbtGreen + ogpixel[i][j + 1].rgbtGreen) /
                                 6.0);
                avpixel[i][j].rgbtBlue =
                    (BYTE) round((ogpixel[i - 1][j - 1].rgbtBlue + ogpixel[i - 1][j].rgbtBlue +
                                  ogpixel[i - 1][j + 1].rgbtBlue + ogpixel[i][j - 1].rgbtBlue +
                                  ogpixel[i][j].rgbtBlue + ogpixel[i][j + 1].rgbtBlue) /
                                 6.0);
            }
            // Filter top left corner pixel
            if (i == 0 && j == 0)
            {
                avpixel[i][j].rgbtRed =
                    (BYTE) round((ogpixel[i][j].rgbtRed + ogpixel[i][j + 1].rgbtRed +
                                  ogpixel[i + 1][j].rgbtRed + ogpixel[i + 1][j + 1].rgbtRed) /
                                 4.0);
                avpixel[i][j].rgbtGreen =
                    (BYTE) round((ogpixel[i][j].rgbtGreen + ogpixel[i][j + 1].rgbtGreen +
                                  ogpixel[i + 1][j].rgbtGreen + ogpixel[i + 1][j + 1].rgbtGreen) /
                                 4.0);
                avpixel[i][j].rgbtBlue =
                    (BYTE) round((ogpixel[i][j].rgbtBlue + ogpixel[i][j + 1].rgbtBlue +
                                  ogpixel[i + 1][j].rgbtBlue + ogpixel[i + 1][j + 1].rgbtBlue) /
                                 4.0);
            }
            // Filter top right corner pixel
            if (i == 0 && j == width - 1)
            {
                avpixel[i][j].rgbtRed =
                    (BYTE) round((ogpixel[i][j - 1].rgbtRed + ogpixel[i][j].rgbtRed +
                                  ogpixel[i + 1][j - 1].rgbtRed + ogpixel[i + 1][j].rgbtRed) /
                                 4.0);
                avpixel[i][j].rgbtGreen =
                    (BYTE) round((ogpixel[i][j - 1].rgbtGreen + ogpixel[i][j].rgbtGreen +
                                  ogpixel[i + 1][j - 1].rgbtGreen + ogpixel[i + 1][j].rgbtGreen) /
                                 4.0);
                avpixel[i][j].rgbtBlue =
                    (BYTE) round((ogpixel[i][j - 1].rgbtBlue + ogpixel[i][j].rgbtBlue +
                                  ogpixel[i + 1][j - 1].rgbtBlue + ogpixel[i + 1][j].rgbtBlue) /
                                 4.0);
            }
            // Filter bottom left corner pixel
            if (i == height - 1 && j == 0)
            {
                avpixel[i][j].rgbtRed =
                    (BYTE) round((ogpixel[i - 1][j].rgbtRed + ogpixel[i - 1][j + 1].rgbtRed +
                                  ogpixel[i][j].rgbtRed + ogpixel[i][j + 1].rgbtRed) /
                                 4.0);
                avpixel[i][j].rgbtGreen =
                    (BYTE) round((ogpixel[i - 1][j].rgbtGreen + ogpixel[i - 1][j + 1].rgbtGreen +
                                  ogpixel[i][j].rgbtGreen + ogpixel[i][j + 1].rgbtGreen) /
                                 4.0);
                avpixel[i][j].rgbtBlue =
                    (BYTE) round((ogpixel[i - 1][j].rgbtBlue + ogpixel[i - 1][j + 1].rgbtBlue +
                                  ogpixel[i][j].rgbtBlue + ogpixel[i][j + 1].rgbtBlue) /
                                 4.0);
            }
            // Filter bottom right corner pixel
            if (i == height - 1 && j == width - 1)
            {
                avpixel[i][j].rgbtRed =
                    (BYTE) round((ogpixel[i - 1][j - 1].rgbtRed + ogpixel[i - 1][j].rgbtRed +
                                  ogpixel[i][j - 1].rgbtRed + ogpixel[i][j].rgbtRed) /
                                 4.0);
                avpixel[i][j].rgbtGreen =
                    (BYTE) round((ogpixel[i - 1][j - 1].rgbtGreen + ogpixel[i - 1][j].rgbtGreen +
                                  ogpixel[i][j - 1].rgbtGreen + ogpixel[i][j].rgbtGreen) /
                                 4.0);
                avpixel[i][j].rgbtBlue =
                    (BYTE) round((ogpixel[i - 1][j - 1].rgbtBlue + ogpixel[i - 1][j].rgbtBlue +
                                  ogpixel[i][j - 1].rgbtBlue + ogpixel[i][j].rgbtBlue) /
                                 4.0);
            }
            // Replace image[i][j] with avpixel[i][j]
            image[i][j] = avpixel[i][j];
        }
    }

    return;
}
