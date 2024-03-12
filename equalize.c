//Copyright Calina Nicolas 2024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "usage.h"
#include "load.h"
#include "save.h"
//function for clamping the values
double clamp(double number, double min, double max)
{
    if (number < min)
    {
        return min;
    }
    else if (number > max)
    {
        return max;
    }
    else
    {
        return number;
    }
}

void equalize(imageData *image, int *isLoaded)
{   
    //checks if an image is loaded
    if ((*isLoaded) == 0)
    {
        printf("No image loaded\n");
        return;
    }
    //checks if the image is black and white
    if (strcmp(image->magicWord, "P3") == 0 || strcmp(image->magicWord, "P6") == 0)
    {
        printf("Black and white image needed\n");
        return;
    }
    double Area;
    Area = image->height * image->width;
    int *pixel_frequency = (int *)calloc(256, sizeof(int));
    //checks the frequency of each pixel
    for (int i = 0; i < (int)image->height; i++)
    {
        for (int j = 0; j < (int)image->width; j++)
        {
            pixel_frequency[image->valuesMatrix[i][j].r]++;
        }
    }
    //calculates the sum of the pixel frequency
    double *sum_pixel_freq = (double *)calloc(256, sizeof(double));
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            sum_pixel_freq[i] += pixel_frequency[j];
        }
    }
    //calculates the new value for each pixel
    for (int i = 0; i < 256; i++)
    {
        sum_pixel_freq[i] = (double)((sum_pixel_freq[i] / Area) * 255);
    }
    //changes the value of each pixel
    for (int i = 0; i < (int)image->height; i++)
    {
        for (int j = 0; j < (int)image->width; j++)
        {
            //here it clamps the values between 0 and 255 and rounds it
            image->valuesMatrix[i][j].r = round(clamp(sum_pixel_freq[image->valuesMatrix[i][j].r], 0, 255));
        }
    }
    //freeing the pixel frequency and sum of pixel frequency matrices
    free(pixel_frequency);
    free(sum_pixel_freq);
    printf("Equalize done\n");
}
