//Copyright Calina Nicolas 2024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usage.h"
#include "load.h"
#include "save.h"

//checks if the number is a power of 2
int ispower2(int num)
{
    if (num <= 0)
    {
        return 0;
    }
    while (num > 1)
    {
        if (num % 2 != 0)
        {
            return 0;
        }
        num /= 2;
    }
    return 1;
}

void histogram(int *isLoaded, imageData *image, char **inputsMatrix, int nr)
{
    if ((*isLoaded) == 0)
    {
        printf("No image loaded\n");
        return;
    }
    if (nr != 3)
    {
        printf("Invalid command\n");
        return;
    }
    //makes the conversion from char to int from the user input
    int y = atoi(inputsMatrix[1]);
    int x = atoi(inputsMatrix[2]);
    //checks if the image is black and white
    if (strcmp(image->magicWord, "P3") == 0 || strcmp(image->magicWord, "P6") == 0)
    {
        printf("Black and white image needed\n");
        return;
    }
    //checks if the number of stars is valid
    if (ispower2(x) == 0)
    {
        printf("Invalid set of parameters\n");
        return;
    }
    //checks if the number of stars and bins is valid
    if (x < 2 || x > 256 || y < 2 || y > 256)
    {
        printf("Invalid set of parameters\n");
        return;
    }
    //allocates memory for the histogram matrix
    int *histogram_matrix = (int *)calloc(256, sizeof(int));
    if (histogram_matrix == NULL)
    {
        printf("Failed to allocate memory for histogram matrix\n");
        return;
    }
    //calculates the bin size
    int bin_size = 256 / x;
    //calculates the frequency of pixel inside each bin
    for (int i = 0; i < (int)image->height; i++)
    {
        for (int j = 0; j < (int)image->width; j++)
        {
            int bin_index = image->valuesMatrix[i][j].r / bin_size;
            histogram_matrix[bin_index]++;
        }
    }
    //find the maximum value of a bin
    int max = 0;
    for (int i = 0; i < x; i++)
    {
        if (histogram_matrix[i] > max)
        {
            max = histogram_matrix[i];
        }
    }
    int starNumber;
    //calculates the starNumber and prints the histogram
    for (int i = 0; i < x; i++)
    {
        starNumber = (int)((histogram_matrix[i] * y) / max);
        printf("%d", starNumber);
        printf("\t");
        printf("|");
        printf("\t");
        for (int j = 0; j < starNumber; j++)
        {
            printf("*");
        }
        printf("\n");
    }
    //free the memory for the histogram matrix
    free(histogram_matrix);
}
