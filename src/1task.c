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

struct massive
	{
	TYPE* data;
	int memlen;
	int datalen;
	};

void change_memsz (struct massive* inp, int newmemlen)
	{
	if (newmemlen > MAX_DATASZ)
		{
		fprintf (stderr, "Unable to allocate memory for %i elements, max count is %i.\n",
					newmemlen, MAX_DATASZ);
		
		return;
		}
	
	if (inp -> memlen == 0)
		{
		inp -> data = (TYPE*) malloc (sizeof (TYPE) * newmemlen);
		inp -> memlen = newmemlen;
		}
	
	else
		{
		inp -> data = (TYPE*) realloc (inp -> data, newmemlen);
		inp -> memlen = newmemlen;
		}
	}

void init_massive (struct massive* inp)
	{
	inp -> data    = 0;
	inp -> memlen  = 0;
	inp -> datalen = 0;
	
	change_memsz (inp, DEF_LEN);
	
	massives_count ++;
	}

void delete_massive (struct massive* inp)
	{
	free (inp -> data);
	inp -> datalen = 0;
	inp -> memlen  = 0;
	
	massives_count --;
	}

void add_element_to_end (struct massive* inp, TYPE new_element)
	{
	while (inp -> datalen + 1 >= inp -> memlen) change_memsz (inp, inp -> memlen + MEM_STEP);
	
	inp -> data [inp -> datalen ++] = new_element;
	}

void remove_element_from_end (struct massive* inp)
	{
	inp -> datalen --;
	}

void change_element (struct massive* inp, int ind, TYPE new_element)
	{
	if (ind >= inp -> memlen)
		printf ("Trying to rewrite unallocated memory - element %i. Max number %i. I'll drop that.'\n",
			ind, inp -> datalen);
	
	else inp -> data [ind] = new_element;
	}
	
int main ()
	{
	return 0;
	}
