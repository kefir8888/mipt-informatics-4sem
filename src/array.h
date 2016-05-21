#include "stdio.h"
#include "malloc.h"
#include "assert.h"
#include <iostream>
#include <exception>

using namespace std;

#define check(COND) { if (COND) { } else { fprintf (stderr, "Condition '%s' is false!\n", #COND); assert (0); } }

const int DEF_LEN    = 10;
const int MEM_STEP   = 50;
const int MAX_DATASZ = 301; //azaza

int arrays_count = 0;
const char* OK_EXITING     = "You've deleted all the arrays.\n";
const char* NOT_OK_EXITING = "You've not deleted all the arrays.\n'";

void print_exit_message ()
	{
	if (arrays_count == 0) printf ("%s", OK_EXITING);
	else printf ("%s", NOT_OK_EXITING);
	}

int pointer_valid (void* inp)
	{
	if (inp != 0) return 1;
	else return 0;
	}

template <class TYPE> class data_structure;

template <class TYPE> class array;

template <class TYPE> class sorted_array;

