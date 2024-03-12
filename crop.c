//Copyright Calina Nicolas 2024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usage.h"
#include "load.h"
#include "save.h"

void crop(imageData *image, int *isLoaded)
{
    //checks if an image is loaded or valid
    if (image == NULL || (*isLoaded) == 0)
    {
        printf("No image loaded\n");
        return;
    }
    //calculates the new height and width
    int newHeight = image->y2 - image->y1;
    int newWidth = image->x2 - image->x1;
    //allocates memory for the new matrix
    rgb_values **newMatrix;
    matrix__dynamic_alloc((&newMatrix), newHeight, newWidth);
    //puts the values of the selection in an auxiliary matrix
    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            newMatrix[i][j] = image->valuesMatrix[i + image->y1][j + image->x1];
        }
    }
    //deallocates the memory for the old matrix
    matrix_dynamic_dealloc(image->valuesMatrix, image->height);
    //changes the height and width and matrix of the image
    image->height = newHeight;
    image->width = newWidth;
    image->y2 -= image->y1;
    image->x2 -= image->x1;
    image->y1 = 0;
    image->x1 = 0;
    //assigns the new matrix to the image
    image->valuesMatrix = newMatrix;

    printf("Image cropped\n");
}
