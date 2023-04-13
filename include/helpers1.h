#ifndef HELPERS_1_H
#define HELPERS_1_H

#include <stdbool.h>


int optionL(char *filename);
int optionE(char *filename);
int optionC(char *filename);
void optionT(char *filename, int *rCount, int *iCount, int *jCount);
int dollarSignCount(char *currString, int stringLength);
bool dollarAndComma (char *currString, int stringLength);
bool checkJ(char *input);






#endif
