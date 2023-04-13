#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "helpers1.h"
#include "hw1.h"

// Usage statement is defined in hw1.h                                                       \

int main(int argc, char* argv[])
{
	char option = argv[1][1];
	
   process_file(stdin,option);

    return 0;
}