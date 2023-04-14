#ifndef HELPERS_1_H
#define HELPERS_1_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    char *name;
    int count;
} RegisterEntry;


int optionL(FILE *file, FILE *erFile, bool v);
int optionE(FILE *file, FILE *erFile, bool v);
int optionC(FILE *file, FILE *erFile, bool v);

void optionT(FILE *file, int *rCount, int *iCount, int *jCount);

int dollarSignCount(char *currString, int stringLength);
bool dollarAndComma (char *currString, int stringLength);
bool checkJ(char *input);

void process_file(FILE *inFile, FILE *erFile, char option, char secondArg);
void process_fileVerbose(FILE *inFile, FILE *erFile, char option);

bool checkOptionCombination(char *argv[], int argc);
bool string_exists(char *key, char **searchFrom, int count);
char* combine_strings(const char* str1, const char* str2);

void optionR(FILE *file, char secondArg, RegisterEntry *sRegister, RegisterEntry *tRegister);
char* generate_asterisk_string(int length);
int count_substring_occurrences(const char *str, const char *substr);
bool is_file_empty(FILE *file);


#endif
