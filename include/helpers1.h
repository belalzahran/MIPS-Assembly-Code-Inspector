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

void process_file(FILE *file, char option, char secondArg);
void process_fileVerbose(FILE *inFile, char option);

bool checkOptionCombination(char *argv[], int argc);
bool string_exists(char *key, char **searchFrom, int count);
char* combine_strings(const char* str1, const char* str2);

void optionR (FILE *file, char secondArg, void *sRegister[8][2], void *tRegister[10][2]);
char* generate_asterisk_string(int length);
int count_substring_occurrences(const char *str, const char *substr);


#endif
