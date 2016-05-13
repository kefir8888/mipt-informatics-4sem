#include "stdio.h"
#include "malloc.h"
#include "assert.h"

#define check(COND) { if (COND) { } else { fprintf (stderr, "Condition '%s' is false!\n", #COND); assert (0); } }

typedef int TYPE;

//TODO: 2-level inheritance
//TODO: vector usage (WTF?)
//TODO: reloaded virtual functions

const int DEF_LEN    = 10;
const int MEM_STEP   = 10;
const int MAX_DATASZ = 301; //azaza

int arrays_count = 0;
const char* OK_EXITING     = "You've deleted all the arrays.\n";
const char* NOT_OK_EXITING = "You've not deleted all the arrays.\n'";

enum {UNABLE_TO_ALLOCATE_MEMORY,
      ELEMENT_NOT_ADDED,
      WRITE_TO_UNALLOCATED_MEMORY,
      GARBAGE_READ};

const char* ERRORS [] = {"Unable to allocate memory for %i elements, max count is %i.\n",
			 "Element not added.\n",
			 "Trying to write to unallocated memory - element %i. Max number is %i. I'll drop that.\n",
			 "Trying to read garbage from not filled memory at index %i. Max ind %i.\n"};

void print_exit_message ()
	{
	if (arrays_count == 0) printf ("%s", OK_EXITING);
	else printf ("%s", NOT_OK_EXITING);
	}

int pointer_valid (struct array* inp)
	{
	if (inp != 0) return 1;
	else return 0;
	}

class array
	{
	private:
	
	TYPE* data;
	int memlen;
	int datalen;
	
	public:
	
	 array () {}
	~array () {}

	int change_memsz (int newmemlen)
		{
		if (newmemlen > MAX_DATASZ)
			{
			fprintf (stderr, ERRORS [UNABLE_TO_ALLOCATE_MEMORY], newmemlen, MAX_DATASZ);
		
			return 0;
			}
	
		if (memlen == 0)
			{
			data = (TYPE*) malloc (sizeof (TYPE) * newmemlen);
			memlen = newmemlen;
			}
	
		else
			{
			printf ("reallocating with new mem len %i\n", newmemlen);
			data = (TYPE*) realloc (data, newmemlen * sizeof (TYPE));
			memlen = newmemlen;
			}
	
		return 1;
		}

	int init_array ()
		{
		data    = 0;
		memlen  = 0;
		datalen = 0;
		
		int suc = change_memsz (DEF_LEN);
		
		arrays_count ++;
		
		return suc;
		}

	int delete_array ()
		{
		free (data);
		datalen = 0;
		memlen  = 0;
	
		arrays_count --;
	
		return 1;
		}

	int add_element_to_end (TYPE new_element)
		{
		int success = 1;
	
		if (datalen + 1 >= memlen)
			{
			success = change_memsz (memlen + MEM_STEP);
			}
	
		if (success == 1) data [datalen ++] = new_element;
		else fprintf (stderr, ERRORS [ELEMENT_NOT_ADDED]);
	
		return success;
		}

	int remove_element_from_end ()
		{
		datalen --;
	
		return 1;
		}

	int change_element (int ind, TYPE new_element)
		{
		if (ind >= memlen)
			{
			printf (ERRORS [WRITE_TO_UNALLOCATED_MEMORY], ind, datalen);
			return 0;
			}
		
		else 	{
			data [ind] = new_element;
			return 1;
			}
		}

int zero_array (struct array* inp)
	{
	check (pointer_valid (inp))
	
	int i = 0;
	for (; i < inp -> datalen; i ++) inp -> data [i] = 0;
	inp -> datalen = 0;
	
	return 1;
	}

int bubble_sort (struct array* inp)
	{
	check (pointer_valid (inp))
	
	for (int i = inp -> datalen; i > 0; i --)
		{
		for (int j = 0; j < i - 1; j ++)
			{
			if (inp -> data [j] < inp -> data [j + 1])
				{
				TYPE temp = inp -> data [j];
				inp -> data [j] = inp -> data [j + 1];
				inp -> data [j + 1] = temp;
				}
			}
		}
	
	int success = 1;
	
	for (int i = 0; i < inp -> datalen - 1; i ++)
		if (inp -> data [i] < inp -> data [i + 1]) success = 0;
		
	return success;
	}

int get_datalen (struct array* inp)
	{
	check (pointer_valid (inp))
	
	return inp -> datalen;
	}

int get_memlen (struct array* inp)
	{
	check (pointer_valid (inp))
	
	return inp -> memlen;
	}

int print_element (struct array* inp, int ind)
	{
	check (pointer_valid (inp))
	
	if (ind >= inp -> datalen)
		{
		printf (ERRORS [GARBAGE_READ], ind, inp -> datalen);
		
		return 0;
		}
	
	printf ("%i", inp -> data [ind]);
	
	return 1;
	}

int print_array (struct array* inp)
	{
	check (pointer_valid (inp))
	
	int i = 0;
	
	for (; i < inp -> datalen; i ++)
		{
		print_element (inp, i);
		printf (" ");
		}
	
	printf ("\n");
	
	return 1;
	}

int verbose_full_print (struct array* inp)
	{
	check (pointer_valid (inp))
	
	printf ("---------------------------------------------------------------\n");
	printf ("Printing data about obj at %x: \nAllocated memory %i bytes (for %i elements), used %i b, %i el.\n",
		/*(unsigned int)*/ inp, (inp -> memlen) * sizeof (TYPE), inp -> memlen, (inp -> datalen) * sizeof (TYPE), inp -> datalen);
	printf ("Printing data in the array:\n");
	print_array (inp);
	
	return 1;
	}
};
