//Copyright Calina Nicolas 2024
#ifndef USAGE_H
#define USAGE_H
typedef struct{
    unsigned  char r;
    unsigned  char g;
    unsigned  char b;
}rgb_values;
typedef struct{
    char magicWord[2];
    rgb_values **valuesMatrix;
    unsigned int x1;
    unsigned int x2;
    unsigned int y1;
    unsigned int y2;
    unsigned  int width;
    unsigned  int height;
    unsigned  int maxValue;
}imageData;
#endif
