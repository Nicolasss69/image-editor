//Copyright Calina Nicolas 2024
#ifndef SELECT_H
#define SELECT_H
#include "usage.h"
#include "select.c"
int verify_range_x(int coord , int width);
int verify_range_y(int coord , int height);
void select_image(imageData *image ,char* x1 ,char* y1 ,char* x2 ,char* y2 );
void select_all(imageData *image);
#endif
