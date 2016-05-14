#include "stdio.h"
#include "malloc.h"
#include "assert.h"

#define check(COND) { if (COND) { } else { fprintf (stderr, "Condition '%s' is false!\n", #COND); assert (0); } }

typedef int TYPE;

//TODO: 2-level inheritance
//TODO: vector usage (WTF?)
//TODO: reloaded virtual functions

const int DEF_LEN    = 10;
const int MEM_STEP   = 50;
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

int pointer_valid (void* inp)
	{
	if (inp != 0) return 1;
	else return 0;
	}

class data_structure
	{
	public:
	
	TYPE* data;
	int memlen;
	int datalen;
	
	 data_structure () { }
	~data_structure () { }
	
	int get_datalen ()
		{
		return datalen;
		}

	int get_memlen ()
		{
		return memlen;
		}
		
	virtual int add_element (TYPE new_element) { }
	
	int change_memsz (int newmemlen)
		{
		try
  			{
    			if (newmemlen > MAX_DATASZ) throw UNABLE_TO_ALLOCATE_MEMORY;
  			}
  		
  		catch (int errnum)
  			{
    			fprintf (stderr, ERRORS [errnum], newmemlen, MAX_DATASZ);
			
			return 1;
			}
		
		if (memlen == 0)
			{
			check (!pointer_valid (data))
			
			data = (TYPE*) malloc (sizeof (TYPE) * newmemlen);
			memlen = newmemlen;
			}
	
		else
			{
			check (pointer_valid (data))
			
			printf ("reallocating with new mem len %i\n", newmemlen);
			data = (TYPE*) realloc (data, newmemlen * sizeof (TYPE));
			memlen = newmemlen;
			}
	
		return 1;
		}
	};

class array: public data_structure
	{
	private:
	
	public:
	
	 array (): data_structure () {}
	~array () {}

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
	
	int add_element (TYPE new_element)
		{
		return add_element_to_end (new_element);
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
		try
  			{
    			if (ind >= memlen) throw WRITE_TO_UNALLOCATED_MEMORY;
  			}
  		
  		catch (int errnum)
  			{
    			fprintf (stderr, ERRORS [errnum], ind, datalen);
			
			return 0;
			}
		
		data [ind] = new_element;
		return 1;
		}

	int zero_array ()
		{
		int i = 0;
		for (; i < datalen; i ++) data [i] = 0;
		datalen = 0;
	
		return 1;
		}

	int bubble_sort ()
		{
		for (int i = datalen; i > 0; i --)
			{
			for (int j = 0; j < i - 1; j ++)
				{
				if (data [j] < data [j + 1])
					{
					TYPE temp    = data [j];
					data [j]     = data [j + 1];
					data [j + 1] = temp;
					}
				}
			}
	
		int success = 1;
	
		for (int i = 0; i < datalen - 1; i ++)
			if (data [i] < data [i + 1]) success = 0;
		
		return success;
		}

	int print_element (int ind)
		{
		try
  			{
    			if (ind >= datalen) throw GARBAGE_READ;
  			}
  		
  		catch (int errnum)
  			{
    			fprintf (stderr, ERRORS [errnum], ind, datalen);
			
			return 0;
			}
		
		printf ("%i", data [ind]);
	
		return 1;
		}

	int print_array ()
		{
		for (int i = 0; i < datalen; i ++)
			{
			print_element (i);
			printf (" ");
			}
	
		printf ("\n");
	
		return 1;
		}

	int verbose_full_print ()
		{
		printf ("---------------------------------------------------------------\n");
		printf ("Printing data about obj at %x: \nAllocated memory %i bytes (for %i elements), used %i b, %i el.\n",
			this, (memlen) * sizeof (TYPE), memlen, (datalen) * sizeof (TYPE), datalen);
		printf ("Printing data in the array:\n");
		print_array ();
	
		return 1;
		}
	};

class sorted_array: public array
	{
	public:
	
	 sorted_array (): array () { }
	~sorted_array () { }
	
	int add_element (TYPE new_element)
		{
		add_element_to_end (new_element)
		bubble_sort        ();
		}
	
	int search (TYPE val)
		{
		int ind = -1;
		
		for (int i = 0; i < datalen; i ++)
			if (data [i] == val)
				ind = i;
		}
	};
