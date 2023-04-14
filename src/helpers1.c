// Define any helper functions here
#include "helpers1.h"


int optionL(FILE *file, FILE *erFile, bool v) {

    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
    int label_count = 0;
    bool in_text_section = true;
    int lineNum = 1;

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) 
    {
        
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
            for (int i = 0; i < line_length; i++) 
            {
                if (buffer[i] == ':') {
                    label_count++;
                    if (v)
                    {
                        fprintf(stderr,"%d: %s",lineNum,buffer);
                    }
                    break;
                }
            }
        }
        lineNum++;
    }

    fclose(file);
    return label_count;
}

int optionE(FILE *file, FILE *erFile, bool v) {

    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
    int line_count = 0;
    int lineNum = 1;

    while (fgets(buffer, BUFFER_SIZE, file) != NULL)
    {
        bool is_empty = true;

        for (int i = 0; i < strlen(buffer); i++) 
        {
            if (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n') {
                is_empty = false;
                if (v)
                {
                    fprintf(stderr,"%d: %s",lineNum,&buffer[i]);
                }
                break;
            }
        }
        if (!is_empty) 
        {
            line_count++;
        }

        lineNum++;
    }

    return line_count;
}

int optionC(FILE *file, FILE *erFile, bool v) 
{

    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
    int comment_count = 0;
    int lineNum = 1;

   while (fgets(buffer, BUFFER_SIZE, file) != NULL) 
   {
        int line_length = strlen(buffer);
        for (int i = 0; i < line_length; i++) 
        {
            if (buffer[i] == '#')
            {
                comment_count++;
                if (v)
                {
                    fprintf(stderr,"%d: %s",lineNum,&buffer[i]);
                }
                break;
            }
        }
        lineNum++;
    }
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

bool checkJ(char *input) 
{
    if  (strstr(input, "j") != NULL || strstr(input, "jal") != NULL || strstr(input, "jr") != NULL || strstr(input, "b") != NULL)
    {
        return true;
    }
    return false;
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

int count_substring_occurrences(const char *str, const char *substr) 
{
    int count = 0;
    const char *temp = str;

    while ((temp = strstr(temp, substr)) != NULL) {
        count++;
        temp += strlen(substr); // Move the pointer forward by the length of the substring
    }

    return count;
}

void optionR(FILE *file, char secondArg, RegisterEntry *sRegister, RegisterEntry *tRegister)
{
    
    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
    int count;

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) 
    {
        if (secondArg == 's') 
        {
            for (int i = 0; i < 8; i++)
            {
                count = count_substring_occurrences(buffer,(char *) sRegister[i].name);
                //printf("%d\n",count);
                if (count > 0)
                {
                    sRegister[i].count+= count;
                } 

            }

        }
        else if (secondArg == 't')
        {
            for (int i = 0; i < 10; i++)
            {
                count = count_substring_occurrences(buffer,tRegister[i].name);
                //printf("%d\n",count);
                if (count > 0)
                {
                    tRegister[i].count+= count;
                } 

            }
        }
        //printf("\nchecking new line\n");
    }

}

char* generate_asterisk_string(int length) {
    char* asterisk_string = (char*) malloc((length + 1) * sizeof(char));

    if (asterisk_string != NULL) 
    {
        for (int i = 0; i < length; i++) {
            asterisk_string[i] = '*';
        }
        asterisk_string[length] = '\0';
    }

    return asterisk_string;
}

void process_file(FILE *inFile, FILE *erFile, char option, char secondArg)
{

    int labelCount = 0;
	int lineCount = 0;
	int commentCount = 0;
	int rCount = 0;
	int iCount = 0;
	int jCount = 0;

    RegisterEntry sRegister[] = 
    { {"$s0", 0},{"$s1", 0},{"$s2", 0},{"$s3", 0},{"$s4", 0},{"$s5", 0},{"$s6", 0},{"$s7", 0} };

    RegisterEntry tRegister[] = 
    { {"$t0", 0},{"$t1", 0},{"$t2", 0},{"$t3", 0},{"$t4", 0},{"$t5", 0},{"$t6", 0},{"$t7", 0},{"$t8", 0},{"$t9", 0}};



    if(option == 'e')
	{
		lineCount = optionE(inFile, erFile, false);
		fprintf(stdout,"Total number of lines: %d\n",lineCount);
	}
	else if (option == 'l')
	{
		labelCount = optionL(inFile, erFile, false);
		fprintf(stdout,"Total number of labels: %d\n",labelCount);
	}
	else if (option == 'c')
	{
		commentCount = optionC(inFile, erFile, false);
		fprintf(stdout,"Total number of comments: %d\n",commentCount);
	}
	else if (option == 't')
	{
		//printf("Running option T\n");
		optionT(inFile,&rCount,&iCount,&jCount);
		fprintf(stdout,"R:%d, I:%d, J:%d\n",rCount,iCount,jCount);
		
	}
    else if (option == 'r')
	{
		optionR(inFile,secondArg, sRegister, tRegister);

        if(secondArg == 's')
        {
            for (int i = 0; i < 8; i ++)
            {
                fprintf(stdout,"%s: %s\n",sRegister[i].name,generate_asterisk_string(sRegister[i].count));
            }
        }
        else
        {
            for (int i = 0; i < 10; i ++)
            {
                fprintf(stdout,"%s: %s\n",tRegister[i].name,generate_asterisk_string(tRegister[i].count));
            }
        }
    
	
	}
}

void process_fileVerbose(FILE *inFile, FILE *erFile, char option)
{

    int labelCount = 0;
	int lineCount = 0;
	int commentCount = 0;


    if(option == 'e')
	{
		lineCount = optionE(inFile, erFile, true);
        //fprintf(stderr,);
		fprintf(stdout,"Total number of lines: %d\n",lineCount);
	}
	else if (option == 'l')
	{
		labelCount = optionL(inFile, erFile, true);
        //fprintf(stderr,);
		fprintf(stdout,"Total number of labels: %d\n",labelCount);
	}
	else if (option == 'c')
	{
		commentCount = optionC(inFile, erFile, true);
        //fprintf(stderr,);
		fprintf(stdout,"Total number of comments: %d\n",commentCount);
	}

}

bool is_file_empty(FILE *file) {
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file); // Rewind the file pointer back to the beginning

    return file_size == 0;
}