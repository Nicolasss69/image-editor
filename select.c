//Copyright Calina Nicolas 2024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usage.h"

//function to veryfy if the coordinates are in the range of the image for x
int verify_range_x(int coord, int width)
{
    if (coord < 0 || coord > width)
    {
        return 1;
    }
    return 0;
}
//function to veryfy if the coordinates are in the range of the image for y
int verify_range_y(int coord, int height)
{
    if (coord < 0 || coord > height)
    {
        return 1;
    }
    return 0;
}

//orders the coordinates ascending
void order_coordinates(int *a, int *b)
{
    int aux;
    if ((*a) > (*b))
    {
        aux = (*a);
        (*a) = (*b);
        (*b) = aux;
    }
}
//function to select
void select_image(imageData *image, char *x1, char *y1, char *x2, char *y2)
{
    //checks if the image is loaded
    if (image == NULL)
    {
        printf("No image loaded\n");
        return;
    }
    //checks if the coordinates are valid numbers
    char *end;
    int ix1 = strtol(x1, &end, 10);
    if (*end != '\0' || end == x1)
    {
        printf("Invalid command\n");
        return;
    }
    int ix2 = strtol(x2, &end, 10);
    if (*end != '\0' || end == x2)
    {
        printf("Invalid command\n");
        return;
    }
    int iy1 = strtol(y1, &end, 10);
    if (*end != '\0' || end == y1)
    {
        printf("Invalid command\n");
        return;
    }
    int iy2 = strtol(y2, &end, 10);
    if (*end != '\0' || end == y2)
    {
        printf("Invalid command\n");
        return;
    }
    //converts from char to int
    ix1 = atoi(x1);
    ix2 = atoi(x2);
    iy1 = atoi(y1);
    iy2 = atoi(y2);
    order_coordinates(&ix1, &ix2);
    order_coordinates(&iy1, &iy2);
    //checks if the coordinates are in the range of the image
    if (ix2 - ix1 <= 0 || iy2 - iy1 <= 0)
    {
        printf("Invalid set of coordinates\n");
        return;
    }
    if (verify_range_x(ix1, image->width) == 1)
    {
        printf("Invalid set of coordinates\n");
        return;
    }
    else if (verify_range_x(ix2, image->width) == 1)
    {
        printf("Invalid set of coordinates\n");
        return;
    }
    else if (verify_range_y(iy1, image->height) == 1)
    {
        printf("Invalid set of coordinates\n");
        return;
    }
    else if (verify_range_y(iy2, image->height) == 1)
    {
        printf("Invalid set of coordinates\n");
        return;
    }
    //updates the coordinates in the selection
    image->x1 = ix1;
    image->x2 = ix2;
    image->y1 = iy1;
    image->y2 = iy2;
    //rechecks if the coordinates are in the range of the image
    if (image->x2 - image->x1 <= 0 || image->y2 - image->y1 <= 0)
    {
        printf("Invalid set of coordinates\n");
        return;
    }
    //prints the coordinates
    printf("Selected %d %d %d %d\n", image->x1,
           image->y1, image->x2, image->y2);
}

void select_all(imageData *image)
{
    //checks if the image is loaded
    if (image == NULL)
    {
        printf("No image loaded\n");
        return;
    }
    //resets the coordinates to the full image
    image->x1 = 0;
    image->x2 = image->width;
    image->y1 = 0;
    image->y2 = image->height;
    printf("Selected ALL\n");
}
