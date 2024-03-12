//Copyright Calina Nicolas 2024
#ifndef APPLY_H
#define APPLY_H
#include "usage.h"
#include "apply.c"
void apply_edge(imageData *image);
void apply(imageData *image  ,char **file_names , int *is_loaded , int nr);
#endif
