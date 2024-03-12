//Copyright Calina Nicolas 2024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usage.h"

//function for reading the user input and storing it in a matrix of words
void file_names(char ***namesMatrix, char *user_input, int *nr)
{
    (*namesMatrix) = (char **)malloc(100 * sizeof(char *));
    for (int i = 0; i < 100; i++)
    {
        (*namesMatrix)[i] = (char *)malloc(100 * sizeof(char));
        (*namesMatrix)[i][0] = '\0';
    }
    char *p = strtok(user_input, " \n");
    (*nr) = 0;
    while (p != NULL)
    {
        strcpy((*namesMatrix)[*nr], p);
        (*nr)++;
        p = strtok(NULL, " \n");
    }
}
//freeing the memory allocated for the matrix of words
void free_fileName(char **namesMatrix)
{
    for (int i = 0; i < 100; i++)
    {
        free(namesMatrix[i]);
    }
    free(namesMatrix);
}
//allocationg memory for the matrix of pixels
void matrix__dynamic_alloc(rgb_values ***matrix, int rows, int cols)
{
    (*matrix) = (rgb_values **)malloc(rows * sizeof(rgb_values *));
    for (int i = 0; i < rows; i++)
    {
        (*matrix)[i] = (rgb_values *)malloc(cols * sizeof(rgb_values));
    }
    
}
//freeing the memory allocated for the matrix of pixels
void matrix_dynamic_dealloc(rgb_values **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    matrix = NULL;
}
/////////////////
// MATRIX READ //
/////////////////

//reading the matrix of pixels from the file greyscale ascii
void matrix_read_grey(rgb_values ***matrix, int rows, int cols, FILE *imageFile)
{
    int pixel_values;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fscanf(imageFile, "%d", &pixel_values);
            (*matrix)[i][j].r = (unsigned char)pixel_values;
        }
    }
}
//reading the matrix of pixels from the file rgb ascii
void matrix_read_rgb(rgb_values ***matrix, int rows, int cols, FILE *imageFile)
{
    int pixel_values;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fscanf(imageFile, "%d", &pixel_values);
            (*matrix)[i][j].r = (unsigned char)pixel_values;
            fscanf(imageFile, "%d", &pixel_values);
            (*matrix)[i][j].g = (unsigned char)pixel_values;
            fscanf(imageFile, "%d", &pixel_values);
            (*matrix)[i][j].b = (unsigned char)pixel_values;
        }
    }
}

//reading the matrix of pixels from the file greyscale binary
void matrix_read_grey_binary(rgb_values ***matrix, int rows, int cols, FILE *imageFile)
{
    unsigned char pixel_value;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fread(&pixel_value, sizeof(unsigned char), 1, imageFile);
            (*matrix)[i][j].r = pixel_value;
        }
    }
}

//reading the matrix of pixels from the file rgb binary
void matrix_read_rgb_binary(rgb_values ***matrix, int rows, int cols, FILE *imageFile)
{
    unsigned char pixel_value;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fread(&pixel_value, sizeof(unsigned char), 1, imageFile);
            (*matrix)[i][j].r = pixel_value;
            fread(&pixel_value, sizeof(unsigned char), 1, imageFile);
            (*matrix)[i][j].g = pixel_value;
            fread(&pixel_value, sizeof(unsigned char), 1, imageFile);
            (*matrix)[i][j].b = pixel_value;
        }
    }
}
/////////////////
// MATRIX SAVE //
/////////////////
//storing in the file the matrix of pixels greyscale ascii
void matrix_save_grey(rgb_values ***matrix, int rows, int cols, FILE *file)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fprintf(file, "%d ", (*matrix)[i][j].r);
        }
        fprintf(file, "\n");
    }
}
//storing in the file the matrix of pixels rgb ascii
void matrix_save_rgb(rgb_values ***matrix, int rows, int cols, FILE *file)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fprintf(file, "%d ", (*matrix)[i][j].r);
            fprintf(file, "%d ", (*matrix)[i][j].g);
            fprintf(file, "%d ", (*matrix)[i][j].b);
        }
        fprintf(file, "\n");
    }
}
//storing in the file the matrix of pixels greyscale binary
void matrix_save_grey_bi(rgb_values ***matrix, int rows, int cols, FILE *file)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fwrite(&(*matrix)[i][j].r, sizeof(unsigned char), 1, file);
        }
    }
}
//storing in the file the matrix of pixels rgb binary
void matrix_save_rgb_bi(rgb_values ***matrix, int rows, int cols, FILE *file)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fwrite(&(*matrix)[i][j].r, sizeof(unsigned char), 1, file);
            fwrite(&(*matrix)[i][j].g, sizeof(unsigned char), 1, file);
            fwrite(&(*matrix)[i][j].b, sizeof(unsigned char), 1, file);
        }
    }
}
//LOAD function
imageData *load(const char *fileName, int *isLoaded, imageData *image)
{
    //checking if an image is loaded
    if ((*isLoaded) == 1)
    {
        matrix_dynamic_dealloc(image->valuesMatrix, image->height);
        free(image);
    }
    FILE *imageFile = fopen(fileName, "r");
    //checking if the file exists
    if (imageFile == NULL)
    {
        printf("Failed to load %s\n", fileName);
        (*isLoaded) = 0;
        return NULL;
    }
    printf("Loaded %s\n", fileName);
    image = (imageData *)malloc(sizeof(imageData));
    if (image == NULL)
    {
        printf("Failed to allocate memory for image data\n");
        fclose(imageFile);
        return NULL;
    }
    //loading the file in the image structure
    fscanf(imageFile, "%c", &image->magicWord[0]);
    fscanf(imageFile, "%c", &image->magicWord[1]);
    image->magicWord[2] = '\0';
    fscanf(imageFile, "%u %u", &image->width, &image->height);
    fscanf(imageFile, "%u ", &image->maxValue);
    matrix__dynamic_alloc(&image->valuesMatrix, image->height, image->width);
    //P2 type
    if (strcmp(image->magicWord, "P2") == 0)
    {
        matrix_read_grey(&image->valuesMatrix, image->height, image->width, imageFile);
        fclose(imageFile);
    }
    //P5 type
    if (strcmp(image->magicWord, "P5") == 0)
    {
        matrix_read_grey_binary(&image->valuesMatrix, image->height, image->width, imageFile);
        fclose(imageFile);
    }
    //P3 type
    if (strcmp(image->magicWord, "P3") == 0)
    {
        matrix_read_rgb(&image->valuesMatrix, image->height, image->width, imageFile);
        fclose(imageFile);
    }
    //P6 type
    if (strcmp(image->magicWord, "P6") == 0)
    {
        matrix_read_rgb_binary(&image->valuesMatrix, image->height, image->width, imageFile);
        fclose(imageFile);
    }
    //setting the x and y coords to the full image
    image->x1 = 0;
    image->x2 = image->width;
    image->y1 = 0;
    image->y2 = image->height;
    (*isLoaded) = 1;
    return image;
}
//deallocating the memory for the image structure at exit
void exit_free(imageData *image)
{
    if (image != NULL)
    {
        matrix_dynamic_dealloc(image->valuesMatrix, image->height);
        free(image);
        return;
    }
    else
    {
        printf("No image loaded\n");
        return;
    }
}
