//Copyright Calina Nicolas 2024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usage.h"
#include "load.h"
#include "save.h"
#include "select.h"
#include "crop.c"
#include "histogram.h"
#include "equalize.h"
#include "apply.h"
#include "rotate.h"

int main(void)
{   
    //image is a pointer to a structure which contains the image data
    imageData *image = NULL;
    //user_input is used for reading the user input
    char *user_input;
    //isLoaded is used to check if an image is loaded
    int isLoaded = 0;
    //inputsMatrix is used to store the user input
    char **inputsMatrix;
    //nr is used to store the number of words in the user input
    int nr;
    user_input = malloc(100 * sizeof(char));
    while (1)
    {
        //reads and checks the user input
        if (fgets(user_input, 100, stdin) == NULL)
        {
            fprintf(stderr, "Error reading user input\n");
            free(user_input);
            return 1;
        }
        //LOAD
        file_names(&inputsMatrix, user_input, &nr);
        if (strcmp(inputsMatrix[0], "LOAD") == 0)
        {
            image = load(inputsMatrix[1], &isLoaded, image);
            free_fileName(inputsMatrix);
        }
        //SAVE
        else if (strcmp(inputsMatrix[0], "SAVE") == 0)
        {
            save(inputsMatrix[1], inputsMatrix[2], image);
            free_fileName(inputsMatrix);
        }
        //SELECT ALL
        else if (strcmp(inputsMatrix[0], "SELECT") == 0 && strcmp(inputsMatrix[1], "ALL") == 0)
        {
            select_all(image);
            free_fileName(inputsMatrix);
        }
        //HISTOGRAM
        else if (strcmp(inputsMatrix[0], "HISTOGRAM") == 0)
        {
            histogram(&isLoaded, image, inputsMatrix, nr);
            free_fileName(inputsMatrix);
        }
        //EQUALIZE
        else if (strcmp(user_input, "EQUALIZE") == 0)
        {
            equalize(image, &isLoaded);
            free_fileName(inputsMatrix);
        }
        //ROTATE
        else if (strcmp(user_input, "ROTATE") == 0)
        {
            rotate(image, inputsMatrix[1] ,&isLoaded);
            free_fileName(inputsMatrix);
        }
        //CROP
        else if (strcmp(inputsMatrix[0], "CROP") == 0)
        {
            crop(image, &isLoaded);
            free_fileName(inputsMatrix);
        }
        //APPLY
        else if (strcmp(inputsMatrix[0], "APPLY") == 0)
        {
            apply(image, inputsMatrix, &isLoaded, nr);
            free_fileName(inputsMatrix);
        }
        //SELECT
        else if (strcmp(inputsMatrix[0], "SELECT") == 0)
        {
            select_image(image, inputsMatrix[1], inputsMatrix[2],
                         inputsMatrix[3], inputsMatrix[4]);
            free_fileName(inputsMatrix);
        }
        //EXIT
        else if (strcmp(inputsMatrix[0], "EXIT") == 0)
        {
            exit_free(image);
            free_fileName(inputsMatrix);
            break;
        }
        else
        {
            //if the user input is not valid
            printf("Invalid command\n");
            free_fileName(inputsMatrix);
        }
    }
    //free the user input
    free(user_input);
}