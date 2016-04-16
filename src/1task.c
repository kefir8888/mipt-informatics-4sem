#include "stdio.h"
#include "malloc.h"
#include "assert.h"

typedef int TYPE;

#define check(COND) { if (COND) { } else { fprintf (stderr, "Condition '%s' is false!\n", #COND); assert (0); } }

//TODO enum to errors  DONE
//TODO gitlog min 15   DONE
//TODO coverage > 95 % DONE
//gcc -fprofile-arcs -ftest-coverage -std=c99 1task.c -o 1task
//./1task
//gcov -b ./1task.c | tee output.txt
//TODO valgrind        DONE
// valgrind --leak-check=full --leak-resolution=med ./1task
//TODO makefile                (?)
//TODO unittests       DONE
//TODO move massive to library (?)

const int DEF_LEN    = 10;
const int MEM_STEP   = 10;
const int MAX_DATASZ = 300; //azaza

int arrays_count = 0;
const char* OK_EXITING = "You've deleted all the arrays.\n'";
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

struct array
	{
	TYPE* data;
	int memlen;
	int datalen;
	};

int change_memsz (struct array* inp, int newmemlen)
	{
	printf ("started changing memsz\n");
	
	if (newmemlen > MAX_DATASZ)
		{
		fprintf (stderr, ERRORS [UNABLE_TO_ALLOCATE_MEMORY],newmemlen, MAX_DATASZ);
		
		return 0;
		}
	
	if (inp -> memlen == 0)
		{
		inp -> data = (TYPE*) malloc (sizeof (TYPE) * newmemlen);
		inp -> memlen = newmemlen;
		}
	
	else
		{
		printf ("reallocating with new mem len %i\n", newmemlen);
		inp -> data = (TYPE*) realloc (inp -> data, newmemlen * sizeof (TYPE));
		inp -> memlen = newmemlen;
		}
	
	return 1;
	}

int init_array (struct array* inp)
	{
	inp -> data    = 0;
	inp -> memlen  = 0;
	inp -> datalen = 0;
	
	int suc = change_memsz (inp, DEF_LEN);
	
	arrays_count ++;
	
	return suc;
	}

int delete_array (struct array* inp)
	{
	free (inp -> data);
	inp -> datalen = 0;
	inp -> memlen  = 0;
	
	arrays_count --;
	
	return 1;
	}

int add_element_to_end (struct array* inp, TYPE new_element)
	{
	int success = 1;
	
	if (inp -> datalen + 1 >= inp -> memlen)
		{
		success = change_memsz (inp, inp -> memlen + MEM_STEP);
		}
	
	if (success == 1) inp -> data [inp -> datalen ++] = new_element;
	else fprintf (stderr, ERRORS [ELEMENT_NOT_ADDED]);
	
	return success;
	}

int remove_element_from_end (struct array* inp)
	{
	inp -> datalen --;
	
	return 1;
	}

int change_element (struct array* inp, int ind, TYPE new_element)
	{
	if (ind >= inp -> memlen)
		{
		printf (ERRORS [WRITE_TO_UNALLOCATED_MEMORY],	ind, inp -> datalen);
		return 0;
		}
		
	else 	{
		inp -> data [ind] = new_element;
		return 1;
		}
	}

int zero_array (struct array* inp)
	{
	int i = 0;
	for (; i < inp -> datalen; i ++) inp -> data [i] = 0;
	inp -> datalen = 0;
	
	return 1;
	}

int get_datalen (struct array* inp)
	{
	return inp -> datalen;
	}

int get_memlen (struct array* inp)
	{
	return inp -> memlen;
	}

int print_element (struct array* inp, int ind)
	{
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
	printf ("---------------------------------------------------------------\n");
	printf ("Printing data about obj at %x: \nAllocated memory %i bytes (for %i elements), used %i b, %i el.\n",
		/*(unsigned int)*/ inp, (inp -> memlen) * sizeof (TYPE), inp -> memlen, (inp -> datalen) * sizeof (TYPE), inp -> datalen);
	printf ("Printing data in the array:\n");
	print_array (inp);
	
	return 1;
	}

int main ()
	{
	struct array array1;
	struct array array2;
	
	check (init_array (&array1))
	check (init_array (&array2))
	
	check (verbose_full_print (&array1))
	
	check (add_element_to_end (&array1, 0))
	check (add_element_to_end (&array1, 1))
	check (add_element_to_end (&array1, 1))
	check (add_element_to_end (&array1, 2))
	check (add_element_to_end (&array1, 3))
	check (add_element_to_end (&array1, 5))
	check (add_element_to_end (&array1, 8))
	check (add_element_to_end (&array1, 13))
	check (verbose_full_print (&array1))
	check (remove_element_from_end (&array1))
	check (print_array (&array1))
	
	check (change_element (&array1, 3, 7))
	check (print_array (&array1))
	
	check (zero_array   (&array1))
	check (print_array (&array1))
	printf ("datalen = %i, memlen = %i\n", get_datalen (&array1), get_memlen (&array1));
	
	for (int i = 0; i < MAX_DATASZ + 5; i ++)
		/*check (*/add_element_to_end (&array2, 41);//)
	
	check (delete_array (&array1))
	print_exit_message ();
	check (delete_array (&array2))
	print_exit_message ();
	
	return 0;
	}
