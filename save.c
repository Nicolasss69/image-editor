//Copyright Calina Nicolas 2024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usage.h"

//function for putting the pixels in the matrix binary
void save_binary(const char *newPhotoName, imageData *image)
{
	FILE *nameFile = fopen(newPhotoName, "wb");
	if (nameFile == NULL)
	{
		printf("No image loaded\n");
		return;
	}
	//makes the conversion from ascii to binary
	if (strcmp(image->magicWord, "P2") == 0)
	{
		strcpy(image->magicWord, "P5");
	}
	if (strcmp(image->magicWord, "P3") == 0)
	{
		strcpy(image->magicWord, "P6");
	}
	fprintf(nameFile, "%s", image->magicWord);
	fprintf(nameFile, "\n");
	fprintf(nameFile, "%u ", image->width);
	fprintf(nameFile, "%u", image->height);
	fprintf(nameFile, "\n");
	fprintf(nameFile, "%u", image->maxValue);
	fprintf(nameFile, "\n");
	//makes the difference between rgb and grey
	if (strcmp(image->magicWord, "P5") == 0)
	{
		matrix_save_grey_bi(&image->valuesMatrix, image->height, image->width, nameFile);
	}
	else if (strcmp(image->magicWord, "P6") == 0)
	{
		matrix_save_rgb_bi(&image->valuesMatrix, image->height, image->width, nameFile);
	}
	printf("Saved %s\n", newPhotoName);
	fclose(nameFile);
}
//function for putting the pixels in the matrix ascii
void save_ascii(const char *newPhotoName, imageData *image)
{
	FILE *nameFile = fopen(newPhotoName, "wt");
	if (nameFile == NULL)
	{
		printf("No image loaded\n");
		return;
	}
	//makes the conversion from binary to ascii
	if (strcmp(image->magicWord, "P6") == 0)
	{
		strcpy(image->magicWord, "P3");
	}
	if (strcmp(image->magicWord, "P5") == 0)
	{
		strcpy(image->magicWord, "P2");
	}
	fprintf(nameFile, "%s", image->magicWord);
	fprintf(nameFile, "\n");
	fprintf(nameFile, "%u ", image->width);
	fprintf(nameFile, "%u", image->height);
	fprintf(nameFile, "\n");
	fprintf(nameFile, "%u", image->maxValue);
	fprintf(nameFile, "\n");
	//makes difference between rgb and grey
	if (strcmp(image->magicWord, "P2") == 0)
	{
		matrix_save_grey(&image->valuesMatrix, image->height, image->width, nameFile);
	}
	else if (strcmp(image->magicWord, "P3") == 0)
	{
		matrix_save_rgb(&image->valuesMatrix, image->height, image->width, nameFile);
	}
	printf("Saved %s\n", newPhotoName);
	fclose(nameFile);
}
//function that distinguishes between ascii and binary and is called in main
void save(const char *newPhotoName, const char *type, imageData *image)
{
	if (image == NULL)
	{
		printf("No image loaded\n");
		return;
	}
	if (strcmp(type, "ascii") == 0)
	{
		save_ascii(newPhotoName, image);
	}
	else
	{
		save_binary(newPhotoName, image);
	}
}
