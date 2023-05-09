#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through every pixel, i = row, j = column
    for (int i = 0, h = height; i < h; i++)
    {
        for (int j = 0, w = width; j < w; j++)
        {
            // Calculate the average value of all colors
            int value = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            // Store average value in every RGB color
            image[i][j].rgbtRed = value;
            image[i][j].rgbtGreen = value;
            image[i][j].rgbtBlue = value;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through every pixel, i = row, j = column
    for (int i = 0, h = height; i < h; i++)
    {
        // Define w value and temporary array for accessibility in all loops
        int w = width - 1;
        RGBTRIPLE temp[width];

        // Set every pixel in its mirrored position in the temporary array, one row at a time
        for (int j = 0; j <= w; j++)
        {
            temp[w - j].rgbtRed = image[i][j].rgbtRed;
            temp[w - j].rgbtGreen = image[i][j].rgbtGreen;
            temp[w - j].rgbtBlue = image[i][j].rgbtBlue;
        }
        // Once a row is completely stored in the temp array, copie the values over to the corresponding row in the image array
        for (int k = 0; k <= w; k++)
        {
            image[i][k] = temp[k];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Define temp array, height and width variables for accessibility in the entire function
    RGBTRIPLE temp[height][width];
    int h = height;
    int w = width;

    // Loop through every pixel, i = row, j = column
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            // Set a variable with value = 0 for every RGB color
            float rval = 0;
            float gval = 0;
            float bval = 0;

            // Check if pixel is at upper left corner
            if (i == 0 && j == 0)
            {
                for (int k = i; k <= i + 1; k++)
                {
                    for (int l = j; l <= j + 1; l++)
                    {
                        // Within the 2x2 grid, add every color value to its corresponding variable
                        rval += image[k][l].rgbtRed;
                        gval += image[k][l].rgbtGreen;
                        bval += image[k][l].rgbtBlue;
                    }
                }
                // Set pixel value to average of this block for the corresponding color
                temp[i][j].rgbtRed = (int)round(rval / 4);
                temp[i][j].rgbtGreen = (int)round(gval / 4);
                temp[i][j].rgbtBlue = (int)round(bval / 4);
            }
            // Check if pixel is at upper right corner
            else if (i == 0 && j == w - 1)
            {
                for (int k = i; k <= i + 1; k++)
                {
                    for (int l = j - 1; l <= j; l++)
                    {
                        // Within the 2x2 grid, add every color value to its corresponding variable
                        rval += image[k][l].rgbtRed;
                        gval += image[k][l].rgbtGreen;
                        bval += image[k][l].rgbtBlue;
                    }
                }
                // Set pixel value to average of this block for the corresponding color
                temp[i][j].rgbtRed = (int)round(rval / 4);
                temp[i][j].rgbtGreen = (int)round(gval / 4);
                temp[i][j].rgbtBlue = (int)round(bval / 4);
            }
            // Check if pixel is at lower right corner
            else if (i == h - 1 && j == w - 1)
            {
                for (int k = i - 1; k <= i; k++)
                {
                    for (int l = j - 1; l <= j; l++)
                    {
                        // Within the 2x2 grid, add every color value to its corresponding variable
                        rval += image[k][l].rgbtRed;
                        gval += image[k][l].rgbtGreen;
                        bval += image[k][l].rgbtBlue;
                    }
                }
                // Set pixel value to average of this block for the corresponding color
                temp[i][j].rgbtRed = (int)round(rval / 4);
                temp[i][j].rgbtGreen = (int)round(gval / 4);
                temp[i][j].rgbtBlue = (int)round(bval / 4);
            }
            // Check if pixel is at lower left corner
            else if (i == h - 1 && j == 0)
            {
                for (int k = i - 1; k <= i; k++)
                {
                    for (int l = j; l <= j + 1; l++)
                    {
                        // Within the 2x2 grid, add every color value to its corresponding variable
                        rval += image[k][l].rgbtRed;
                        gval += image[k][l].rgbtGreen;
                        bval += image[k][l].rgbtBlue;
                    }
                }
                // Set pixel value to average of this block for the corresponding color
                temp[i][j].rgbtRed = (int)round(rval / 4);
                temp[i][j].rgbtGreen = (int)round(gval / 4);
                temp[i][j].rgbtBlue = (int)round(bval / 4);
            }
            // Check if pixel is at the top
            else if (i == 0)
            {
                for (int k = i; k <= i + 1; k++)
                {
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        // Within the 2x2 grid, add every color value to its corresponding variable
                        rval += image[k][l].rgbtRed;
                        gval += image[k][l].rgbtGreen;
                        bval += image[k][l].rgbtBlue;
                    }
                }
                // Set pixel value to average of this block for the corresponding color
                temp[i][j].rgbtRed = (int)round(rval / 6);
                temp[i][j].rgbtGreen = (int)round(gval / 6);
                temp[i][j].rgbtBlue = (int)round(bval / 6);
            }
            // Check if pixel is at the right end
            else if (j == w - 1)
            {
                for (int k = i - 1; k <= i + 1; k++)
                {
                    for (int l = j - 1; l <= j; l++)
                    {
                        // Within the 2x2 grid, add every color value to its corresponding variable
                        rval += image[k][l].rgbtRed;
                        gval += image[k][l].rgbtGreen;
                        bval += image[k][l].rgbtBlue;
                    }
                }
                // Set pixel value to average of this block for the corresponding color
                temp[i][j].rgbtRed = (int)round(rval / 6);
                temp[i][j].rgbtGreen = (int)round(gval / 6);
                temp[i][j].rgbtBlue = (int)round(bval / 6);
            }
            // Check if pixel is at the bottom
            else if (i == h - 1)
            {
                for (int k = i - 1; k <= i; k++)
                {
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        // Within the 2x2 grid, add every color value to its corresponding variable
                        rval += image[k][l].rgbtRed;
                        gval += image[k][l].rgbtGreen;
                        bval += image[k][l].rgbtBlue;
                    }
                }
                // Set pixel value to average of this block for the corresponding color
                temp[i][j].rgbtRed = (int)round(rval / 6);
                temp[i][j].rgbtGreen = (int)round(gval / 6);
                temp[i][j].rgbtBlue = (int)round(bval / 6);
            }
            // Check if pixel is at the left end
            else if (j == 0)
            {
                for (int k = i - 1; k <= i + 1; k++)
                {
                    for (int l = j; l <= j + 1; l++)
                    {
                        // Within the 2x2 grid, add every color value to its corresponding variable
                        rval += image[k][l].rgbtRed;
                        gval += image[k][l].rgbtGreen;
                        bval += image[k][l].rgbtBlue;
                    }
                }
                // Set pixel value to average of this block for the corresponding color
                temp[i][j].rgbtRed = (int)round(rval / 6);
                temp[i][j].rgbtGreen = (int)round(gval / 6);
                temp[i][j].rgbtBlue = (int)round(bval / 6);
            }
            // If the pixel is not an edge case, calculate the average value of all neighbouring pixels and itself in a 3x3 grid
            else
            {
                for (int k = i - 1; k <= i + 1; k++)
                {
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        // Within the 3x3 grid, add every color value to its corresponding variable
                        rval += image[k][l].rgbtRed;
                        gval += image[k][l].rgbtGreen;
                        bval += image[k][l].rgbtBlue;
                    }
                }
                // Set pixel value to average of this block for the corresponding color
                temp[i][j].rgbtRed = (int)round(rval / 9);
                temp[i][j].rgbtGreen = (int)round(gval / 9);
                temp[i][j].rgbtBlue = (int)round(bval / 9);
            }
        }
    }

    // Copy completed temporary array into the original image array
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Define temp array, height and width variables for accessibility in the entire function
    RGBTRIPLE temp[height][width];
    int h = height;
    int w = width;

    // Define arrays for gx and gy factors
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Loop over every pixel
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            // Set gx and gy variables for calculation the value per pixel
            int gxRed = 0;
            int gxGreen = 0;
            int gxBlue = 0;

            int gyRed = 0;
            int gyGreen = 0;
            int gyBlue = 0;

            // Loop over a 3x3 grid around our actual pixel
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // If pixel is outside of image height, skip iteration
                    if (i + k < 0 || i + k >= h)
                    {
                        continue;
                    }
                    // If pixel is outside of image width, skip iteration
                    if (j + l < 0 || j + l >= w)
                    {
                        continue;
                    }

                    // Within the grid, add every color value multiplied by its Gx or Gy factor to its corresponding variable
                    gxRed += image[i + k][j + l].rgbtRed * gx[k + 1][l + 1];
                    gxGreen += image[i + k][j + l].rgbtGreen * gx[k + 1][l + 1];
                    gxBlue += image[i + k][j + l].rgbtBlue * gx[k + 1][l + 1];

                    gyRed += image[i + k][j + l].rgbtRed * gy[k + 1][l + 1];
                    gyGreen += image[i + k][j + l].rgbtGreen * gy[k + 1][l + 1];
                    gyBlue += image[i + k][j + l].rgbtBlue * gy[k + 1][l + 1];
                }
            }

            // To avoid adding a positive to a negative number, take the square root of the square of each gx and gy value and add them together. Round the sum.
            int rval = round(sqrt(gxRed * gxRed + gyRed * gyRed));
            int gval = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int bval = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));

            // If the color value exceeds 255 then set it to 255.
            temp[i][j].rgbtRed = rval > 255 ? 255 : rval;
            temp[i][j].rgbtGreen = gval > 255 ? 255 : gval;
            temp[i][j].rgbtBlue = bval > 255 ? 255 : bval;
        }
    }

    // Copy completed temporary array into the original image array
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }

    return;
}
