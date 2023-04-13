// Define any helper functions here

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int optionL(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
    int label_count = 0;
    bool in_text_section = false;

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        if (strncmp(buffer, ".text", 5) == 0) {
            in_text_section = true;
        } else if (strncmp(buffer, ".data", 5) == 0) {
            in_text_section = false;
        }

        if (in_text_section) {
            int line_length = strlen(buffer);
            for (int i = 0; i < line_length; i++) {
                if (buffer[i] == ':') {
                    label_count++;
                    break;
                }
            }
        }
    }

    fclose(file);
    return label_count;
}

int optionE( char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
    int line_count = 0;

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        bool is_empty = true;

        for (int i = 0; i < strlen(buffer); i++) {
            if (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n') {
                is_empty = false;
                break;
            }
        }
        if (!is_empty) {
            line_count++;
        }
    }

    fclose(file);
    return line_count;
}

int optionC(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    int ch;
    int comment_count = 0;
    bool in_comment = false;

    while ((ch = fgetc(file)) != EOF) {
        // Check for the start of a comment
        if (ch == '#') {
            in_comment = true;
        }

        // Check for the end of a comment or the end of the input
        if (in_comment && (ch == '\n' || ch == EOF)) {
            comment_count++;
            in_comment = false;
        }
    }

    fclose(file);
    return comment_count;
}

int dollarSignCount(char *currString, int stringLength)
{
    int count = 0;
    char ch;
    int runTimes =0;
    for (int i = 0; i < stringLength;i++)
    {
        //printf("%c",currString[i]);
        if (currString[i] == '$')
        {
            count++;
            //printf(" counted...\n");
        }
        runTimes++;
        //scanf("%c", &ch);
    }
    //printf("runTimes: %d and stringLength: %d\n",runTimes,stringLength);
    return count;
}

bool dollarAndComma (char *currString, int stringLength)
{
    bool result = false;

    for (int i = 0; i < stringLength;i++)
    {
        if (currString[i] == '$')
        {
            for (int j = i; j < stringLength;j++)
            {
                if(currString[j] == ',')
                {
                    result = true;
                }
            }

        }
    }

    return result;
}

bool checkJ(char *input) {
    int space_count = 0;

    for (const char *ptr = input; *ptr != '\0'; ++ptr) {
        if (*ptr == '#') {
            break; // Stop checking when encountering a comment
        }
        if (isspace((unsigned char)*ptr)) {
            space_count++;
            if (space_count > 1) {
                return false;
            }
        }
    }

    return space_count == 1;
}

void optionT (char *filename, int *rCount, int *iCount, int *jCount)
{
    FILE *file = fopen(filename,"r");
    if (file == NULL)
    {
        perror("Error opening file\n");
    }
    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
    int dollarCount;
    int currStrLength;

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) 
    {
        dollarCount = 0;
        buffer[strcspn(buffer, "\n")] = '\0';
        currStrLength = strlen(buffer);
        dollarCount = dollarSignCount(buffer,currStrLength);
        //printf("\n\"%-s\"-",buffer);

        //printf("string length is %d\n",currStrLength);
        //print++
        //printf("\"%s\" contains %d $'s\n\n",buffer,dollarCount);

        if (dollarCount == 3)
        {
            //printf("R COUNT ");
            (*rCount)++;
        }
        else if (dollarCount == 2 || dollarAndComma(buffer,currStrLength))
        {
            //printf("I COUNT ");
            (*iCount)++;
        }
        else if (dollarCount == 1 || checkJ(buffer))
        {
            //printf("J COUNT ");
            (*jCount)++;
        }
        else
        {
            //printf("else statement ");
        }
            
   }
    //printf("There are %d lines printed\n",print);
    fclose(file);
}

