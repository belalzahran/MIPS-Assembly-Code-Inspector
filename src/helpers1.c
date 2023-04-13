// Define any helper functions here

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int optionL(FILE *file) {

    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
    int label_count = 0;
    bool in_text_section = true;

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        
        if (strstr(buffer,".text") != NULL)
        {
            in_text_section = true;
        } 
        else if (strstr(buffer,".data") != NULL) 
        {
            in_text_section = false;
        }

        if (in_text_section) 
        {
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

int optionE(FILE *file) {

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

int optionC(FILE *file) {

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

void optionT (FILE *file, int *rCount, int *iCount, int *jCount)
{
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


bool string_exists(char *key, char **searchFrom, int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(key, searchFrom[i]) == 0) {
            return true;
        }
    }
    return false;
}

char* combine_strings(const char* str1, const char* str2) {
    size_t length1 = strlen(str1);
    size_t length2 = strlen(str2);

    char* combined = (char*) malloc(length1 + length2 + 2); 

    if (combined != NULL) {
        strcpy(combined, str1);
        strcat(combined, " ");
        strcat(combined, str2);
    }

    return combined;
}

bool checkOptionCombination(char *argv[], int argc)
{

    char *validCommands2[] = {"-e","-c","-l","-t"};
    char *validCommands3[] = {"-r s","-r t","-e -V","-c -V","-l -V"};
    char *newCommand;
    if (argc == 3)
    {
        newCommand = combine_strings(argv[1],argv[2]);

        if ( string_exists(newCommand, validCommands3, 5) )
        {
            free(newCommand);
            return true;
        }

    }
    else if (argc == 2)
    {
        if (string_exists(argv[1], validCommands2, 4))
            return true;
    }

    return false;
}

void process_file(FILE *inFile, char option, char secondArg)
{

    int labelCount = 0;
	int lineCount = 0;
	int commentCount = 0;
	int rCount = 0;
	int iCount = 0;
	int jCount = 0;

    // char buffer[1024];

    // printf("Processing with mode: %d\n", mode);

    // while (fgets(buffer, sizeof(buffer), file) != NULL) {
    //     printf("Processing line: %s", buffer);
    //     // Do the actual processing here
    // }   

    if(option == 'e')
	{
		lineCount = optionE(inFile);
		fprintf(stdout,"Total number of lines: %d\n",lineCount);
	}
	else if (option == 'l')
	{
		labelCount = optionL(inFile);
		fprintf(stdout,"Lables: %d\n",labelCount);
	}
	else if (option == 'c')
	{
		commentCount = optionC(inFile);
		fprintf(stdout,"Comments: %d\n",commentCount);
	}
	else if (option == 't')
	{
		//printf("Running option T\n");
		optionT(inFile,&rCount,&iCount,&jCount);
		fprintf(stdout,"R:%d, I:%d, J:%d\n",rCount,iCount,jCount);
		
	}
}




void process_fileVerbose(FILE *inFile, char option)
{

    int labelCount = 0;
	int lineCount = 0;
	int commentCount = 0;
	int rCount = 0;
	int iCount = 0;
	int jCount = 0;

    // char buffer[1024];

    // printf("Processing with mode: %d\n", mode);

    // while (fgets(buffer, sizeof(buffer), file) != NULL) {
    //     printf("Processing line: %s", buffer);
    //     // Do the actual processing here
    // }   

    if(option == 'e')
	{
		lineCount = optionE(inFile);
		fprintf(stdout,"Total number of lines: %d\n",lineCount);
	}
	else if (option == 'l')
	{
		labelCount = optionL(inFile);
		fprintf(stdout,"Lables: %d\n",labelCount);
	}
	else if (option == 'c')
	{
		commentCount = optionC(inFile);
		fprintf(stdout,"Comments: %d\n",commentCount);
	}
	else if (option == 't')
	{
		//printf("Running option T\n");
		optionT(inFile,&rCount,&iCount,&jCount);
		fprintf(stdout,"R:%d, I:%d, J:%d\n",rCount,iCount,jCount);
		
	}
}