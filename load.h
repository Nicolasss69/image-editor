//Copyright Calina Nicolas 2024
#ifndef LOAD_H
#define LOAD_H
#include "load.c"
void matrix__dynamic_alloc(rgb_values ***matrix , int rows , int cols);
void matrix_dynamic_dealloc(rgb_values **matrix , int rows );
void ignoreComments(FILE *file);
void removeNewline(char *str);
void file_names(char ***namesMatrix , char *user_input , int *nr);
void free_fileName(char **namesMatrix);
void matrix_read_grey(rgb_values ***matrix , int rows, int cols , FILE* imageFile);
void matrix_read_rgb(rgb_values ***matrix , int rows, int cols , FILE* imageFile);
void matrix_print(rgb_values ***matrix , int rows, int cols ,FILE *file);
void matrix_read_grey_binary(rgb_values ***matrix , int rows, int cols , FILE* imageFile);
void matrix_read_rgb_binary(rgb_values ***matrix , int rows, int cols , FILE* imageFile);
imageData *load(const char* fileName , int *isLoaded, imageData *old_image);
#endif
