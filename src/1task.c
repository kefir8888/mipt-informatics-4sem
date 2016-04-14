#include "sdio.h"
#include "malloc.h"

typedef int TYPE;

//TODO enum to errors
//TODO gitlog min 15
//TODO coverage > 95 %
//TODO valgrind
//TODO makefile
//TODO unittests
//TODO move massive to library

//#define TYPE   TYPE_INT
//typedef int TYPE_INT;
//typedef double TYPE_DOUBLE;

//enum types
//	{
//	TYPE_INT,
//	TYPE_DOUBLE
//	};

//const char* types_strings [2] = { "int", "double" };

const int DEF_LEN    = 10;
const int MEM_STEP   = 10;
const int MAX_DATASZ = 100;

int massives_count = 0;
const char* OK_EXITING = "You've deleted all the massives.\n'";
const char* NOT_OK_EXITING = "You've not deleted all the massives.\n'";

void print_exit_message ()
	{
	if (massives_count == 0) printf ("%s", OK_EXITING);
	else printf ("%s", NOT_OK_EXITING);
	}

int main ()
	{
	return 0;
	}
