//Copyright Calina Nicolas 2024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "usage.h"
#include "equalize.h"
//APPLY EDGE
void apply_edge(imageData *image)
{
    //calculates the new height and width of the image
    int newHeight = image->y2;
    int newWidth = image->x2;
    //calculates the starting  point of the selection
    int newEntry = image->x1;
    int newEntry2 = image->y1;
    //allocates memory for the new matrix
    rgb_values **newMatrix;
    matrix__dynamic_alloc((&newMatrix), newHeight, newWidth);
    //applies the edge filter
    for (int i = newEntry2; i < newHeight; i++)
    {
        for (int j = newEntry; j < newWidth; j++)
        {
            if ((i > 0) && (i < (int)image->height - 1) && (j > 0) && (j < (int)image->width - 1))
            {
                //it calculates the neighbours of a pixel and sums them toghether
                int sum_r = 0, sum_g = 0, sum_b = 0;
                int top_left_r = (-1) * image->valuesMatrix[i - 1][j - 1].r;
                sum_r += top_left_r;
                int top_r = (-1) * image->valuesMatrix[i - 1][j].r;
                sum_r += top_r;
                int top_right_r = (-1) * image->valuesMatrix[i - 1][j + 1].r;
                sum_r += top_right_r;
                int right_r = (-1) * image->valuesMatrix[i][j + 1].r;
                sum_r += right_r;
                int bottom_right_r = (-1) * image->valuesMatrix[i + 1][j + 1].r;
                sum_r += bottom_right_r;
                int bottom_r = (-1) * image->valuesMatrix[i + 1][j].r;
                sum_r += bottom_r;
                int bottom_left_r = (-1) * image->valuesMatrix[i + 1][j - 1].r;
                sum_r += bottom_left_r;
                int left_r = (-1) * image->valuesMatrix[i][j - 1].r;
                sum_r += left_r;
                int top_left_g = (-1) * image->valuesMatrix[i - 1][j - 1].g;
                sum_g += top_left_g;
                int top_g = (-1) * image->valuesMatrix[i - 1][j].g;
                sum_g += top_g;
                int top_right_g = (-1) * image->valuesMatrix[i - 1][j + 1].g;
                sum_g += top_right_g;
                int right_g = (-1) * image->valuesMatrix[i][j + 1].g;
                sum_g += right_g;
                int bottom_right_g = (-1) * image->valuesMatrix[i + 1][j + 1].g;
                sum_g += bottom_right_g;
                int bottom_g = (-1) * image->valuesMatrix[i + 1][j].g;
                sum_g += bottom_g;
                int bottom_left_g = (-1) * image->valuesMatrix[i + 1][j - 1].g;
                sum_g += bottom_left_g;
                int left_g = (-1) * image->valuesMatrix[i][j - 1].g;
                sum_g += left_g;
                int top_left_b = (-1) * image->valuesMatrix[i - 1][j - 1].b;
                sum_b += top_left_b;
                int top_b = (-1) * image->valuesMatrix[i - 1][j].b;
                sum_b += top_b;
                int top_right_b = (-1) * image->valuesMatrix[i - 1][j + 1].b;
                sum_b += top_right_b;
                int right_b = (-1) * image->valuesMatrix[i][j + 1].b;
                sum_b += right_b;
                int bottom_right_b = (-1) * image->valuesMatrix[i + 1][j + 1].b;
                sum_b += bottom_right_b;
                int bottom_b = (-1) * image->valuesMatrix[i + 1][j].b;
                sum_b += bottom_b;
                int bottom_left_b = (-1) * image->valuesMatrix[i + 1][j - 1].b;
                sum_b += bottom_left_b;
                int left_b = (-1) * image->valuesMatrix[i][j - 1].b;
                sum_b += left_b;
                int pixel_r = 8 * image->valuesMatrix[i][j].r;
                sum_r += pixel_r;
                int pixel_g = 8 * image->valuesMatrix[i][j].g;
                sum_g += pixel_g;
                int pixel_b = 8 * image->valuesMatrix[i][j].b;
                sum_b += pixel_b;
                //clamps the values between 0 and 255
                sum_r = clamp(sum_r, 0, 255);
                sum_g = clamp(sum_g, 0, 255);
                sum_b = clamp(sum_b, 0, 255);
                //changes the values of the pixel in the new matrix
                newMatrix[i][j].r = sum_r;
                newMatrix[i][j].g = sum_g;
                newMatrix[i][j].b = sum_b;
            }
        }
    }
    for (int i = newEntry2; i < newHeight; i++)
    {
        for (int j = newEntry; j < newWidth; j++)
        {
            if ((i > 0) && (i < (int)image->height - 1) && (j > 0) && (j < (int)image->width - 1))
            {
                //assigns the new matrix to the image
                image->valuesMatrix[i][j].r = newMatrix[i][j].r;
                image->valuesMatrix[i][j].g = newMatrix[i][j].g;
                image->valuesMatrix[i][j].b = newMatrix[i][j].b;
            }
        }
    }
    //deallocates the memory for the new matrix
    matrix_dynamic_dealloc(newMatrix, newHeight);
}
//APPLY SHARPEN
void apply_sharpen(imageData *image)
{
    //calculates the new height and width of the image
    int newHeight = image->y2;
    int newWidth = image->x2;
    //calculates the starting  point of the selection
    int newEntry = image->x1;
    int newEntry2 = image->y1;
    //allocates memory for the new matrix
    rgb_values **newMatrix;
    matrix__dynamic_alloc((&newMatrix), newHeight, newWidth);
    for (int i = newEntry2; i < newHeight; i++)
    {
        for (int j = newEntry; j < newWidth; j++)
        {
            if ((i > 0) && (i < (int)image->height - 1) && (j > 0) && (j < (int)image->width - 1))
            {
                //it calculates the neighbours of a pixel and sums them toghether
                int sum_r = 0, sum_g = 0, sum_b = 0;
                int top_left_r = 0 * image->valuesMatrix[i - 1][j - 1].r;
                sum_r += top_left_r;
                int top_r = (-1) * image->valuesMatrix[i - 1][j].r;
                sum_r += top_r;
                int top_right_r = 0 * image->valuesMatrix[i - 1][j + 1].r;
                sum_r += top_right_r;
                int right_r = (-1) * image->valuesMatrix[i][j + 1].r;
                sum_r += right_r;
                int bottom_right_r = 0 * image->valuesMatrix[i + 1][j + 1].r;
                sum_r += bottom_right_r;
                int bottom_r = (-1) * image->valuesMatrix[i + 1][j].r;
                sum_r += bottom_r;
                int bottom_left_r = 0 * image->valuesMatrix[i + 1][j - 1].r;
                sum_r += bottom_left_r;
                int left_r = (-1) * image->valuesMatrix[i][j - 1].r;
                sum_r += left_r;
                int top_left_g = 0 * image->valuesMatrix[i - 1][j - 1].g;
                sum_g += top_left_g;
                int top_g = (-1) * image->valuesMatrix[i - 1][j].g;
                sum_g += top_g;
                int top_right_g = 0 * image->valuesMatrix[i - 1][j + 1].g;
                sum_g += top_right_g;
                int right_g = (-1) * image->valuesMatrix[i][j + 1].g;
                sum_g += right_g;
                int bottom_right_g = 0 * image->valuesMatrix[i + 1][j + 1].g;
                sum_g += bottom_right_g;
                int bottom_g = (-1) * image->valuesMatrix[i + 1][j].g;
                sum_g += bottom_g;
                int bottom_left_g = 0 * image->valuesMatrix[i + 1][j - 1].g;
                sum_g += bottom_left_g;
                int left_g = (-1) * image->valuesMatrix[i][j - 1].g;
                sum_g += left_g;
                int top_left_b = 0 * image->valuesMatrix[i - 1][j - 1].b;
                sum_b += top_left_b;
                int top_b = (-1) * image->valuesMatrix[i - 1][j].b;
                sum_b += top_b;
                int top_right_b = 0 * image->valuesMatrix[i - 1][j + 1].b;
                sum_b += top_right_b;
                int right_b = (-1) * image->valuesMatrix[i][j + 1].b;
                sum_b += right_b;
                int bottom_right_b = 0 * image->valuesMatrix[i + 1][j + 1].b;
                sum_b += bottom_right_b;
                int bottom_b = (-1) * image->valuesMatrix[i + 1][j].b;
                sum_b += bottom_b;
                int bottom_left_b = 0 * image->valuesMatrix[i + 1][j - 1].b;
                sum_b += bottom_left_b;
                int left_b = (-1) * image->valuesMatrix[i][j - 1].b;
                sum_b += left_b;
                int pixel_r = 5 * image->valuesMatrix[i][j].r;
                sum_r += pixel_r;
                int pixel_g = 5 * image->valuesMatrix[i][j].g;
                sum_g += pixel_g;
                int pixel_b = 5 * image->valuesMatrix[i][j].b;
                sum_b += pixel_b;
                //clamps the values between 0 and 255
                sum_r = clamp(sum_r, 0, 255);
                sum_g = clamp(sum_g, 0, 255);
                sum_b = clamp(sum_b, 0, 255);
                //changes the values of the pixel in the new matrix
                newMatrix[i][j].r = sum_r;
                newMatrix[i][j].g = sum_g;
                newMatrix[i][j].b = sum_b;
            }
        }
    }
    for (int i = newEntry2; i < newHeight; i++)
    {
        for (int j = newEntry; j < newWidth; j++)
        {
            if ((i > 0) && (i < (int)image->height - 1) && (j > 0) && (j < (int)image->width - 1))
            {
                //assigns the new matrix to the image
                image->valuesMatrix[i][j].r = newMatrix[i][j].r;
                image->valuesMatrix[i][j].g = newMatrix[i][j].g;
                image->valuesMatrix[i][j].b = newMatrix[i][j].b;
            }
        }
    }
    //deallocates the memory for the new matrix
    matrix_dynamic_dealloc(newMatrix, newHeight);
}
//APPLY BLUR
void apply_blur(imageData *image)
{
    //calculates the new height and width of the image
    int newHeight = image->y2;
    int newWidth = image->x2;
    //calculates the starting  point of the selection
    int newEntry = image->x1;
    int newEntry2 = image->y1;
    //allocates memory for the new matrix
    rgb_values **newMatrix;
    matrix__dynamic_alloc((&newMatrix), newHeight, newWidth);
    for (int i = newEntry2; i < newHeight; i++)
    {
        for (int j = newEntry; j < newWidth; j++)
        {
            if ((i > 0) && (i < (int)image->height - 1) && (j > 0) && (j < (int)image->width - 1))
            {
                //it calculates the neighbours of a pixel and sums them toghether
                double sum_r = 0, sum_g = 0, sum_b = 0;
                double top_left_r = (1.0 / 9) * image->valuesMatrix[i - 1][j - 1].r;
                sum_r += top_left_r;
                double top_r = (1.0 / 9) * image->valuesMatrix[i - 1][j].r;
                sum_r += top_r;
                double top_right_r = (1.0 / 9) * image->valuesMatrix[i - 1][j + 1].r;
                sum_r += top_right_r;
                double right_r = (1.0 / 9) * image->valuesMatrix[i][j + 1].r;
                sum_r += right_r;
                double bottom_right_r = (1.0 / 9) * image->valuesMatrix[i + 1][j + 1].r;
                sum_r += bottom_right_r;
                double bottom_r = (1.0 / 9) * image->valuesMatrix[i + 1][j].r;
                sum_r += bottom_r;
                double bottom_left_r = (1.0 / 9) * image->valuesMatrix[i + 1][j - 1].r;
                sum_r += bottom_left_r;
                double left_r = (1.0 / 9) * image->valuesMatrix[i][j - 1].r;
                sum_r += left_r;
                double top_left_g = (1.0 / 9) * image->valuesMatrix[i - 1][j - 1].g;
                sum_g += top_left_g;
                double top_g = (1.0 / 9) * image->valuesMatrix[i - 1][j].g;
                sum_g += top_g;
                double top_right_g = (1.0 / 9) * image->valuesMatrix[i - 1][j + 1].g;
                sum_g += top_right_g;
                double right_g = (1.0 / 9) * image->valuesMatrix[i][j + 1].g;
                sum_g += right_g;
                double bottom_right_g = (1.0 / 9) * image->valuesMatrix[i + 1][j + 1].g;
                sum_g += bottom_right_g;
                double bottom_g = (1.0 / 9) * image->valuesMatrix[i + 1][j].g;
                sum_g += bottom_g;
                double bottom_left_g = (1.0 / 9) * image->valuesMatrix[i + 1][j - 1].g;
                sum_g += bottom_left_g;
                double left_g = (1.0 / 9) * image->valuesMatrix[i][j - 1].g;
                sum_g += left_g;
                double top_left_b = (1.0 / 9) * image->valuesMatrix[i - 1][j - 1].b;
                sum_b += top_left_b;
                double top_b = (1.0 / 9) * image->valuesMatrix[i - 1][j].b;
                sum_b += top_b;
                double top_right_b = (1.0 / 9) * image->valuesMatrix[i - 1][j + 1].b;
                sum_b += top_right_b;
                double right_b = (1.0 / 9) * image->valuesMatrix[i][j + 1].b;
                sum_b += right_b;
                double bottom_right_b = (1.0 / 9) * image->valuesMatrix[i + 1][j + 1].b;
                sum_b += bottom_right_b;
                double bottom_b = (1.0 / 9) * image->valuesMatrix[i + 1][j].b;
                sum_b += bottom_b;
                double bottom_left_b = (1.0 / 9) * image->valuesMatrix[i + 1][j - 1].b;
                sum_b += bottom_left_b;
                double left_b = (1.0 / 9) * image->valuesMatrix[i][j - 1].b;
                sum_b += left_b;
                double pixel_r = (1.0 / 9) * image->valuesMatrix[i][j].r;
                sum_r += pixel_r;
                double pixel_g = (1.0 / 9) * image->valuesMatrix[i][j].g;
                sum_g += pixel_g;
                double pixel_b = (1.0 / 9) * image->valuesMatrix[i][j].b;
                sum_b += pixel_b;
                //rounds the values as they are doubles and could have decimals
                sum_r = round(sum_r);
                sum_g = round(sum_g);
                sum_b = round(sum_b);
                //clamps the values between 0 and 255
                sum_r = clamp(sum_r, 0, 255);
                sum_g = clamp(sum_g, 0, 255);
                sum_b = clamp(sum_b, 0, 255);
                //changes the values of the pixel in the new matrix
                newMatrix[i][j].r = sum_r;
                newMatrix[i][j].g = sum_g;
                newMatrix[i][j].b = sum_b;
            }
        }
    }
    for (int i = newEntry2; i < newHeight; i++)
    {
        for (int j = newEntry; j < newWidth; j++)
        {
            if ((i > 0) && (i < (int)image->height - 1) && (j > 0) && (j < (int)image->width - 1))
            {
                //assigns the new matrix to the image
                image->valuesMatrix[i][j].r = newMatrix[i][j].r;
                image->valuesMatrix[i][j].g = newMatrix[i][j].g;
                image->valuesMatrix[i][j].b = newMatrix[i][j].b;
            }
        }
    }
    //deallocates the memory for the new matrix
    matrix_dynamic_dealloc(newMatrix, newHeight);
}

void apply_gaussian_blur(imageData *image)
{
    //calculates the new height and width of the image
    int newHeight = image->y2;
    int newWidth = image->x2;
    //calculates the starting  point of the selection
    int newEntry = image->x1;
    int newEntry2 = image->y1;
    //allocates memory for the new matrix
    rgb_values **newMatrix;
    matrix__dynamic_alloc((&newMatrix), newHeight, newWidth);
    for (int i = newEntry2; i < newHeight; i++)
    {
        for (int j = newEntry; j < newWidth; j++)
        {
            if ((i > 0) && (i < (int)image->height - 1) && (j > 0) && (j < (int)image->width - 1))
            {
                //it calculates the neighbours of a pixel and sums them toghether
                double sum_r = 0, sum_g = 0, sum_b = 0;
                double top_left_r = (1.0 / 16) * image->valuesMatrix[i - 1][j - 1].r;
                sum_r += top_left_r;
                double top_r = (2.0 / 16) * image->valuesMatrix[i - 1][j].r;
                sum_r += top_r;
                double top_right_r = (1.0 / 16) * image->valuesMatrix[i - 1][j + 1].r;
                sum_r += top_right_r;
                double right_r = (2.0 / 16) * image->valuesMatrix[i][j + 1].r;
                sum_r += right_r;
                double bottom_right_r = (1.0 / 16) * image->valuesMatrix[i + 1][j + 1].r;
                sum_r += bottom_right_r;
                double bottom_r = (2.0 / 16) * image->valuesMatrix[i + 1][j].r;
                sum_r += bottom_r;
                double bottom_left_r = (1.0 / 16) * image->valuesMatrix[i + 1][j - 1].r;
                sum_r += bottom_left_r;
                double left_r = (2.0 / 16) * image->valuesMatrix[i][j - 1].r;
                sum_r += left_r;
                double top_left_g = (1.0 / 16) * image->valuesMatrix[i - 1][j - 1].g;
                sum_g += top_left_g;
                double top_g = (2.0 / 16) * image->valuesMatrix[i - 1][j].g;
                sum_g += top_g;
                double top_right_g = (1.0 / 16) * image->valuesMatrix[i - 1][j + 1].g;
                sum_g += top_right_g;
                double right_g = (2.0 / 16) * image->valuesMatrix[i][j + 1].g;
                sum_g += right_g;
                double bottom_right_g = (1.0 / 16) * image->valuesMatrix[i + 1][j + 1].g;
                sum_g += bottom_right_g;
                double bottom_g = (2.0 / 16) * image->valuesMatrix[i + 1][j].g;
                sum_g += bottom_g;
                double bottom_left_g = (1.0 / 16) * image->valuesMatrix[i + 1][j - 1].g;
                sum_g += bottom_left_g;
                double left_g = (2.0 / 16) * image->valuesMatrix[i][j - 1].g;
                sum_g += left_g;
                double top_left_b = (1.0 / 16) * image->valuesMatrix[i - 1][j - 1].b;
                sum_b += top_left_b;
                double top_b = (2.0 / 16) * image->valuesMatrix[i - 1][j].b;
                sum_b += top_b;
                double top_right_b = (1.0 / 16) * image->valuesMatrix[i - 1][j + 1].b;
                sum_b += top_right_b;
                double right_b = (2.0 / 16) * image->valuesMatrix[i][j + 1].b;
                sum_b += right_b;
                double bottom_right_b = (1.0 / 16) * image->valuesMatrix[i + 1][j + 1].b;
                sum_b += bottom_right_b;
                double bottom_b = (2.0 / 16) * image->valuesMatrix[i + 1][j].b;
                sum_b += bottom_b;
                double bottom_left_b = (1.0 / 16) * image->valuesMatrix[i + 1][j - 1].b;
                sum_b += bottom_left_b;
                double left_b = (2.0 / 16) * image->valuesMatrix[i][j - 1].b;
                sum_b += left_b;
                double pixel_r = (4.0 / 16) * image->valuesMatrix[i][j].r;
                sum_r += pixel_r;
                double pixel_g = (4.0 / 16) * image->valuesMatrix[i][j].g;
                sum_g += pixel_g;
                double pixel_b = (4.0 / 16) * image->valuesMatrix[i][j].b;
                sum_b += pixel_b;
                //rounds the values as they are doubles and could have decimals
                sum_r = round(sum_r);
                sum_g = round(sum_g);
                sum_b = round(sum_b);
                //clamps the values between 0 and 255
                sum_r = clamp(sum_r, 0, 255);
                sum_g = clamp(sum_g, 0, 255);
                sum_b = clamp(sum_b, 0, 255);
                newMatrix[i][j].r = sum_r;
                newMatrix[i][j].g = sum_g;
                newMatrix[i][j].b = sum_b;
            }
        }
    }
    for (int i = newEntry2; i < newHeight; i++)
    {
        for (int j = newEntry; j < newWidth; j++)
        {
            if ((i > 0) && (i < (int)image->height - 1) && (j > 0) && (j < (int)image->width - 1))
            {
                //assigns the new matrix to the image
                image->valuesMatrix[i][j].r = newMatrix[i][j].r;
                image->valuesMatrix[i][j].g = newMatrix[i][j].g;
                image->valuesMatrix[i][j].b = newMatrix[i][j].b;
            }
        }
    }
    //deallocates the memory for the new matrix
    matrix_dynamic_dealloc(newMatrix, newHeight);
}

void apply(imageData *image, char **inputsMatrix, int *isLoaded, int nr)
{
    //checks if an image is loaded
    if ((*isLoaded) == 0)
    {
        printf("No image loaded\n");
        return;
    }
    //checks if the image is valid
    if (image == NULL)
    {
        printf("No image loaded\n");
        return;
    }
    //checks if the number of parameters is valid
    if (nr != 2)
    {
        printf("Invalid command\n");
        return;
    }
    //checks if the image is black and white and prints a message as we don't need to apply any filter
    if (strcmp(image->magicWord, "P2") == 0 || strcmp(image->magicWord, "P5") == 0)
    {
        printf("Easy, Charlie Chaplin\n");
        return;
    }
    //checks the type of filter to apply
    if (strcmp(inputsMatrix[1], "EDGE") == 0)
    {
        apply_edge(image);
        printf("APPLY EDGE done\n");
        return;
    }
    else if (strcmp(inputsMatrix[1], "SHARPEN") == 0)
    {
        apply_sharpen(image);
        printf("APPLY SHARPEN done\n");
    }
    else if (strcmp(inputsMatrix[1], "BLUR") == 0)
    {
        apply_blur(image);
        printf("APPLY BLUR done\n");
    }
    else if (strcmp(inputsMatrix[1], "GAUSSIAN_BLUR") == 0)
    {
        apply_gaussian_blur(image);
        printf("APPLY GAUSSIAN_BLUR done\n");
    }
    else
    {
        //if it does nothing then the parameter is invalid
        printf("APPLY parameter invalid\n");
    }
}
