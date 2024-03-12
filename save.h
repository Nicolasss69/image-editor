//Copyright Calina Nicolas 2024
#ifndef SAVE_H
#define SAVE_H
#include "save.c"
void save(const char* newPhotoName ,const char* type , imageData *image );
void save_binary(const char* newPhotoName , imageData *image);
void save_ascii(const char *newPhotoName , imageData *image);
#endif
