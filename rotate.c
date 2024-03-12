//Copyright Calina Nicolas 2024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "usage.h"

//rotates selection grey images to 90 degrees right
void rotate_90_right(imageData *image){
    //calculates the new height and width
    int newHeight = image->x2 - image->x1;
    int newWidth = image->y2 - image->y1;
    //alocates memory for the new matrix
    rgb_values **newMatrix;
    matrix__dynamic_alloc((&newMatrix), newHeight, newWidth);
    //goes through the old matrix and puts the values in the new matrix
    for (int i = 0; i < newHeight; i++){
        for (int j = 0; j < newWidth; j++){
            newMatrix[j][newHeight - 1 - i].r = image->valuesMatrix[i + image->y1][j + image->x1].r;
        }
    }
    //assigns the new matrix to the old one values and therefore rotates the image
    for (int i = 0; i < newWidth; i++){
        for (int j = 0; j < newHeight; j++){
            image->valuesMatrix[i + image->y1][j + image->x1].r = newMatrix[i][j].r;
        }
    }
    //deallocates the memory for the new matrix
    matrix_dynamic_dealloc(newMatrix, newHeight);
}
//rotates selection rgb images to 90 degrees right
void rotate_90_right_rgb(imageData *image){
    //calculates the new height and width
    int newHeight = image->x2 - image->x1;
    int newWidth = image->y2 - image->y1;
    //alocates memory for the new matrix
    rgb_values **newMatrix;
    matrix__dynamic_alloc((&newMatrix), newHeight, newWidth);
    //goes through the old matrix and puts the values in the new matrix
    for (int i = 0; i < newHeight; i++){
        for (int j = 0; j < newWidth; j++){
            newMatrix[j][newHeight - 1 - i].r = image->valuesMatrix[i + image->y1][j + image->x1].r;
            newMatrix[j][newHeight - 1 - i].g = image->valuesMatrix[i + image->y1][j + image->x1].g;
            newMatrix[j][newHeight - 1 - i].b = image->valuesMatrix[i + image->y1][j + image->x1].b;
        }
    }
    //assigns the new matrix to the old one values and therefore rotates the image
    for (int i = 0; i < newWidth; i++){
        for (int j = 0; j < newHeight; j++){
            image->valuesMatrix[i + image->y1][j + image->x1].r = newMatrix[i][j].r;
            image->valuesMatrix[i + image->y1][j + image->x1].g = newMatrix[i][j].g;
            image->valuesMatrix[i + image->y1][j + image->x1].b = newMatrix[i][j].b;
        }
    }
    //deallocates the memory for the new matrix
    matrix_dynamic_dealloc(newMatrix, newHeight);
}
//rotates whole grey images to 90 degrees right
void rotate_90_matrix_right(imageData *image){
    //calculates the new height and width
    int newHeight = image->height;
    int newWidth = image->width;
    //alocates memory for the new matrix
    rgb_values **newMatrix;
    matrix__dynamic_alloc((&newMatrix), newWidth , newHeight);
    //goes through the old matrix and puts the values in the new matrix
    for (int i = 0; i < newHeight; i++){
        for (int j = 0; j < newWidth; j++){
            newMatrix[j][newHeight - 1 - i].r = image->valuesMatrix[i][j].r;
        }
    }
    //deallocs memory for the old matrix
    matrix_dynamic_dealloc(image->valuesMatrix, newHeight);
    //assigns the new matrix to the old one and swaps the width and height
    image->valuesMatrix = newMatrix;
    image->height = newWidth;
    image->width = newHeight;
    //swaps the x and y coordinates
    int aux;
    aux = image->x2;
    image->x2 = image->y2;
    image->y2 = aux;
}
//rotates whole rgb images to 90 degrees right
void rotate_90_matrix_right_rgb(imageData *image){
    //calculates the new height and width
    int newHeight = image->height;
    int newWidth = image->width;
    //alocates memory for the new matrix
    rgb_values **newMatrix;
    matrix__dynamic_alloc((&newMatrix), newWidth , newHeight);
    //goes through the old matrix and puts the values in the new matrix
    for (int i = 0; i < newHeight; i++){
        for (int j = 0; j < newWidth; j++){
            newMatrix[j][newHeight - 1 - i].r = image->valuesMatrix[i][j].r;
            newMatrix[j][newHeight - 1 - i].g = image->valuesMatrix[i][j].g;
            newMatrix[j][newHeight - 1 - i].b = image->valuesMatrix[i][j].b;
        }
    }
    //deallocs memory for the old matrix
    matrix_dynamic_dealloc(image->valuesMatrix, newHeight);
    //assigns the new matrix to the old one and swaps the width and height
    image->valuesMatrix = newMatrix;
    image->height = newWidth;
    image->width = newHeight;
    //swaps the x and y coordinates
    int aux;
    aux = image->x2;
    image->x2 = image->y2;
    image->y2 = aux;
}
//rotate function
void rotate(imageData *image , char *angle_input , int *isLoaded){
    //checks if an image is loaded
    if((*isLoaded) == 0){
        printf("No image loaded\n");
        return;
    }
    //checks if the image is valid
    if (image == NULL){
        printf("No image loaded\n");
        return;
    }
    //converts the input to int
    int angle = atoi(angle_input);
    //variable to check if the angle is negative
    int neg = 0;
    //changes the negative angles to positive ones (-angle = 360 - angle)
    if(angle == -270){
        angle = 90;
        neg = 1;
    }
    if(angle == -180){
        angle = 180;
        neg = 1;
    }
    if(angle == -90){
        angle = 270;
        neg = 1;
    }
    if(angle == -360){
        angle = 360;
        neg = 1;
    }
    //checks if the angle is a between -360 and 360
    if(angle != 90 && angle != 180 && angle != 270 && angle != 360 && angle != 0){
        printf("Unsupported rotation angle\n");
        return;
    }
    //checks if the selection is a full matrix
    int fullMatrixSelected = 0 ;
    if(image->x2 - image->x1 == image->width && image->y2 - image->y1 == image->height){
        fullMatrixSelected = 1;
    }
    //rotates the whole greyscale images
    if(fullMatrixSelected == 1 && (strcmp(image->magicWord , "P2") == 0 || strcmp(image->magicWord , "P5") == 0)){
        if(angle == 90){
            //if angle is 90 or -270 rotates the image 90 degrees right
            rotate_90_matrix_right(image);
            if(!neg){
            printf("Rotated 90\n");
            } else {
            printf("Rotated -270\n");
            }
            return;
        }
        if(angle == 180){
            //if angle is 180 or -180 rotates the image 180 degrees right by rotating it 90 degrees right twice
            rotate_90_matrix_right(image);
            rotate_90_matrix_right(image);
            if(!neg){
            printf("Rotated 180\n");
            } else {
            printf("Rotated -180\n");
            }
            return;
        }
        if(angle == 270){
            //if angle is 270 or -90 rotates the image 270 degrees right by rotating it 90 degrees right three times
            rotate_90_matrix_right(image);
            rotate_90_matrix_right(image);
            rotate_90_matrix_right(image);
            if(!neg){
            printf("Rotated 270\n");
            } else {
            printf("Rotated -90\n");
            }
            return;
        }
        if(angle == 360){
            //if the angle is 360 or -360 it does not rotate it at all
            if(!neg){
            printf("Rotated 360\n");
            } else {
            printf("Rotated -360\n");
            }
            return;
        }
        if(angle == 0){
            //if the angle is 0 it does nothing
            if(!neg){
            printf("Rotated 0\n");
            }
            return;
        }
    }
    //rotates the whole rgb images
    if(fullMatrixSelected == 1 && (strcmp(image->magicWord , "P3") == 0 || strcmp(image->magicWord , "P6") == 0)){
        if(angle == 90){
            //if angle is 90 or -270 rotates the image 90 degrees right
            rotate_90_matrix_right_rgb(image);
            if(!neg){
            printf("Rotated 90\n");
            } else {
            printf("Rotated -270\n");
            }
            return;
        }
        if(angle == 180){
            //if angle is 180 or -180 rotates the image 180 degrees right by rotating it 90 degrees right twice
            rotate_90_matrix_right_rgb(image);
            rotate_90_matrix_right_rgb(image);
            if(!neg){
            printf("Rotated 180\n");
            } else {
            printf("Rotated -180\n");
            }
            return;
        }
        if(angle == 270){
            //if angle is 270 or -90 rotates the image 270 degrees right by rotating it 90 degrees right three times
            rotate_90_matrix_right_rgb(image);
            rotate_90_matrix_right_rgb(image);
            rotate_90_matrix_right_rgb(image);
            if(!neg){
            printf("Rotated 270\n");
            } else {
            printf("Rotated -90\n");
            }
            return;
        }
        if(angle == 360){
            //if the angle is 360 or -360 it does not rotate it at all
            if(!neg){
            printf("Rotated 360\n");
            } else {
            printf("Rotated -360\n");
            }
            return;
        }
        if(angle == 0){
            //if the angle is 0 it does nothing
            if(!neg){
            printf("Rotated 0\n");
            }
            return;
        }
    }
    //checks if the selection defines a square matrix
    if(image->x2 - image->x1 != image->y2 - image->y1){
        printf("The selection must be square\n");
        return;
    }
    //rotates the selection greyscale images
    if( angle == 90 && (strcmp(image->magicWord , "P2") == 0 || strcmp(image->magicWord , "P5") == 0)){
        rotate_90_right(image);
        //if the angle is 90 or -270 it rotates the selection 90 degrees right
        if(angle == 90 && neg == 0){
            printf("Rotated 90\n");
        }
        else{
            printf("Rotated -270\n");
        }
        return;
    }
    //rotates the selection rgb images
    if( angle == 90 && (strcmp(image->magicWord , "P3") == 0 || strcmp(image->magicWord , "P6") == 0)){
        rotate_90_right_rgb(image);
        //if the angle is 90 or -270 it rotates the selection 90 degrees right
        if(angle == 90 && neg == 0){
            printf("Rotated 90\n");
        }
        else{
            printf("Rotated -270\n");
        }
        return;
    }
    //rotates the selection greyscale images
    if( angle == 180 && (strcmp(image->magicWord , "P2") == 0 || strcmp(image->magicWord , "P5") == 0)){
        rotate_90_right(image);
        rotate_90_right(image);
        //if the angle is 180 or -180 it rotates the selection 180 degrees right by rotating it 90 degrees right twice
        if(angle == 180 && neg == 0){
            printf("Rotated 180\n");
        }
        else{
            printf("Rotated -180\n");
        }
        return;
    }
    //rotates the selection rgb images
    if( angle == 180 && (strcmp(image->magicWord , "P3") == 0 || strcmp(image->magicWord , "P6") == 0)){
        rotate_90_right_rgb(image);
        rotate_90_right_rgb(image);
        //if the angle is 180 or -180 it rotates the selection 180 degrees right by rotating it 90 degrees right twice
        if(angle ==180 && neg == 0){
            printf("Rotated 180\n");
        }
        else{
            printf("Rotated -180\n");
        }
        return;
    }
    //rotates the selection greyscale images
    if( angle == 270 && (strcmp(image->magicWord , "P2") == 0 || strcmp(image->magicWord , "P5") == 0)){
        rotate_90_right(image);
        rotate_90_right(image);
        rotate_90_right(image);
        //if the angle is 270 or -90 it rotates the selection 270 degrees right by rotating it 90 degrees right three times
        if(angle == 270 && neg == 0){
            printf("Rotated 270\n");
        }
        else{
            printf("Rotated -90\n");
        }
        return;
    }
    //rotates the selection rgb images
    if( angle == 270 && (strcmp(image->magicWord , "P3") == 0 || strcmp(image->magicWord , "P6") == 0)){
        rotate_90_right_rgb(image);
        rotate_90_right_rgb(image);
        rotate_90_right_rgb(image);
        //if the angle is 270 or -90 it rotates the selection 270 degrees right by rotating it 90 degrees right three times
        if(angle == 270 && neg == 0){
            printf("Rotated 270\n");
        }
        else{
            printf("Rotated -90\n");
        }
        return;
    }
    //if the angle is 360 or -360 it does not rotate it at all
    if(angle == 360){
            if(!neg){
            printf("Rotated 360\n");
            } else {
            printf("Rotated -360\n");
            }
            return;
        }
        //if the angle is 0 it does nothing
        if(angle == 0){
            if(!neg){
            printf("Rotated 0\n");
            }
            return;
        }

}
