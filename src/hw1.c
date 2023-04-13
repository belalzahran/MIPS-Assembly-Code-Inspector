#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers1.h"
#include "hw1.h"

// Usage statement is defined in hw1.h                                                       \

int main(int argc, char* argv[])
{

	char option;
	char *inFile;
	int labelCount = 0;
	int lineCount = 0;
	int commentCount = 0;
	int rCount = 0;
	int iCount = 0;
	int jCount = 0;

	for (int i = 0; i < argc; i++)
	{
		if(i == 1)
		{
			option = argv[i][1];	
		}
		if (i == 2)
		{
			inFile = argv[i];
		}
	}

	if(option == 'e')
	{
		lineCount = optionE(inFile);
		printf("Line Count: %d\n",lineCount);
	}
	else if (option == 'l')
	{
		labelCount = optionL(inFile);
		printf("Lables: %d\n",labelCount);
	}
	else if (option == 'c')
	{
		commentCount = optionC(inFile);
		printf("Comments: %d\n",commentCount);
	}
	else if (option == 't')
	{
		//printf("Running option T\n");
		optionT(inFile,&rCount,&iCount,&jCount);
		printf("R:%d, I:%d, J:%d\n",rCount,iCount,jCount);
		
	}



    return 0;
}
