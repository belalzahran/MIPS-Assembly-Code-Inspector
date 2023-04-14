#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include "helpers1.h"
#include "hw1.h"

// Usage statement is defined in hw1.h                                                 

int main(int argc, char* argv[])
{
	bool verbose = false;
	char option;
	char secondArg;
	if (argc > 3) 
	{
		fprintf(stderr, "Too many options specified\n");
		fprintf(stderr, "%s\n",USAGE_MSG);
	}
	else if (argc == 3)
	{	
		if (checkOptionCombination(argv, argc))
		{
			option = argv[1][1];
			secondArg = argv[2][0] == '-'? 'V' : argv[2][0];

			if (secondArg == 'V')
			{
				process_fileVerbose(stdin, stderr, option);
			}
			else if (secondArg == 's' || secondArg == 't')
			{
				process_file(stdin, stderr, option, secondArg);
			}
		}
		else
		{
			fprintf(stderr,"Invalid combinations of options\n");
			fprintf(stderr, "%s\n",USAGE_MSG);
		}
	}
	else if (argc == 2)
	{
		if (checkOptionCombination(argv, argc))
		{
			option = argv[1][1];
			process_file(stdin, stderr, option,' ');
		}
		else 
		{
			fprintf(stderr, "%s",USAGE_MSG);
		}
	}
	else if (argc == 1)
	{
		fprintf(stderr,"No options specified\n");
		fprintf(stderr, "%s\n",USAGE_MSG);
	}

    return 0;
}