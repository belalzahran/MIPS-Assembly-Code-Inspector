#ifndef HELPERS_1_H
#define HELPERS_1_H

#include <stdbool.h>


int optionL(FILE *file);
int optionE(FILE *file);
int optionC(FILE *file);
void optionT(FILE *file, int *rCount, int *iCount, int *jCount);
int dollarSignCount(char *currString, int stringLength);
bool dollarAndComma (char *currString, int stringLength);
bool checkJ(char *input);

void process_file(FILE *file, char option);






#endif
