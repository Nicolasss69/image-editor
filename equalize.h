//Copyright Calina Nicolas 2024
#ifndef EQUALIZE_H
#define EQUALIZE_H
#include "usage.h"
#include "equalize.c"
#include <math.h>
void equalize(imageData *image , int *isLoaded);
double clamp(double number, double min, double max);
#endif

