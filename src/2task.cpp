#include "array.cpp"

#define try_check( CALL ) \
try \
{ \
CALL;\
} \
catch (exception& ex) \
	{ \
	fprintf (stderr, "%s", ex.what ()); \
	err_count ++; \
	} \
tests_passed ++;

int main ()
	{
	int err_count    = 0;
	int tests_passed = 0;
	
	//alternative_array <alternative_array <int> >* alt_arr = new alternative_array <alternative_array <int> > ();
	
	//for (int i = 0; i < 10; i ++)
	//	{
	//	alt_arr
	//	}
	
	
	alternative_array <alternative_array <int> >* vect = new alternative_array <alternative_array <int> > ();
	
	for (int i = 0; i < 10; i ++)
		{
		vect -> add_element (*(new alternative_array <int>));
		
		for (int j = 0; j < i; j ++)
			(*vect) [i].add_element (i);
		}
	
	/*for (int i = 0; i < 10; i ++)
		{
		for (int j = 0; j < i; j ++)
			{
			printf ("%i", ((*vect) [i]) [j]);
			}
		
		printf ("\n");
		}
	*/
	
	array <int>* array1 = new array <int> ();
	array <int>* array2 = new array <int> ();
	
	try_check (array1->init_array ())
	try_check (array2 -> init_array ())
	try_check (array1 -> verbose_full_print ())
	try_check (array1 -> add_element (5))
	try_check (array1 -> add_element_to_end (1))
	try_check (array1 -> add_element_to_end (8))
	try_check (array1 -> add_element_to_end (41))
	//check (array2 -> change_memsz (1000))
	try_check (array1 -> add_element_to_end (3))
	try_check (array1 -> add_element_to_end (3))
	try_check (array1 -> add_element_to_end (8))
	try_check (array1 -> add_element_to_end (13))
	try_check (array1 -> verbose_full_print ())
	try_check (array1 -> remove_element_from_end ())
	try_check (array1 -> print_array ())
	
	sorted_array <int>* sarr = new sorted_array <int> ();
	sarr -> init_array ();
	sarr -> add_element (5);
	try_check (sarr -> search (5) == 1)
	printf ("search result is %i\n", sarr -> search (5));
	sarr -> delete_array ();
	delete sarr;
	
	try_check (array1 -> bubble_sort ())
	try_check (array1 -> print_array ())
	
	try_check (array1 -> change_element (3, 7))
	try_check (array1 -> print_array    ())
	
	try_check (array1 -> zero_array  ())
	try_check (array1 -> print_array ())
	printf ("datalen = %i, memlen = %i\n", array1 -> get_datalen (), array1 -> get_memlen ());
	
	for (int i = 0; i < MAX_DATASZ - 70; i ++)
		array1 -> add_element_to_end (41);
	
	try_check (array1 -> delete_array ())
	print_exit_message ();
	try_check (array2 -> delete_array ())
	print_exit_message ();
	delete array1;
	delete array2;	
	
	return 0;
	}
