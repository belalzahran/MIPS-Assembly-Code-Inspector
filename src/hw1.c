#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include "helpers1.h"
#include "hw1.h"

// Usage statement is defined in hw1.h                                                       \

int main(int argc, char* argv[])
{
	
	bool verbose = false;
	char option;
	char secondArg;

	//printf("%s",argv[2]);

	// if (argv[2][1] == 'V')
	// 	 verbose = 1;

	if (argc > 3) 
	{
		fprintf(stderr, "Too many options specified\n");
		fprintf(stderr, "%s\n",USAGE_MSG);
	}
	else if (argc == 3)
	{
		
		if (checkOptionCombination(argv, argc))
		{
			// valid arguments and combinations
			option = argv[1][1];
			secondArg = argv[2][0] == '-'? 'V' : argv[2][0];

			if (secondArg == 'V')
			{
				printf("Calling verbose function\n");
				//process_fileVerbose(stdin, option);
			}
			else if (secondArg == 's' || secondArg == 't')
			{
				// call regular process file and pass through r flag
				//printf("Calling regular function w second Arg R\n");
				process_file(stdin, option, secondArg);
			}
			else 
			{
				fprintf(stderr,"we dont know what happened sorry\n");
			}

		}
		else
		{
			fprintf(stderr,"Invalid combinations of options\n");
			fprintf(stderr, "%s\n",USAGE_MSG);
		}
	}
	else if(argc == 2)
	{
		if (checkOptionCombination(argv, argc))
		{
			option = argv[1][1];

			process_file(stdin, option,' ');
		}
		else 
		{
			fprintf(stderr,"Invalid\n");
			fprintf(stderr, "%s\n",USAGE_MSG);
		}
	}
	else if(argc == 1)
	{
		fprintf(stderr,"No options specified\n");
		fprintf(stderr, "%s\n",USAGE_MSG);
	}

    return 0;
}