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
	
	array <int>* array1 = new array <int> ();
	array <int>* array2 = new array <int> ();
	
	try_check (array1->init_array ());
	
	check (array2 -> init_array ())
	
	check (array1 -> verbose_full_print ())
	
	check (array1 -> add_element (5))
	check (array1 -> add_element_to_end (1))
	check (array1 -> add_element_to_end (8))
	check (array1 -> add_element_to_end (41))
	//check (array2 -> change_memsz (1000))
	check (array1 -> add_element_to_end (3))
	check (array1 -> add_element_to_end (3))
	check (array1 -> add_element_to_end (8))
	check (array1 -> add_element_to_end (13))
	check (array1 -> verbose_full_print ())
	check (array1 -> remove_element_from_end ())
	check (array1 -> print_array ())
	
	sorted_array <int>* sarr = new sorted_array <int> ();
	sarr -> init_array ();
	sarr -> add_element (5);
	check (sarr -> search (5) == 1)
	printf ("search result is %i\n", sarr -> search (5));
	sarr -> delete_array ();
	delete sarr;
	
	check (array1 -> bubble_sort ())
	check (array1 -> print_array ())
	
	check (array1 -> change_element (3, 7))
	check (array1 -> print_array    ())
	
	check (array1 -> zero_array  ())
	check (array1 -> print_array ())
	printf ("datalen = %i, memlen = %i\n", array1 -> get_datalen (), array1 -> get_memlen ());
	
	for (int i = 0; i < MAX_DATASZ - 70; i ++)
		array1 -> add_element_to_end (41);
	
	check (array1 -> delete_array ())
	print_exit_message ();
	check (array2 -> delete_array ())
	print_exit_message ();
	delete array1;
	delete array2;
	
	/*
	check (array1 -> init_array ())
	check (array2 -> init_array ())
	
	check (array1 -> verbose_full_print ())
	
	check (array1 -> add_element (5))
	check (array1 -> add_element_to_end (1))
	check (array1 -> add_element_to_end (8))
	check (array1 -> add_element_to_end (41))
	//check (array2 -> change_memsz (1000))
	check (array1 -> add_element_to_end (3))
	check (array1 -> add_element_to_end (3))
	check (array1 -> add_element_to_end (8))
	check (array1 -> add_element_to_end (13))
	check (array1 -> verbose_full_print ())
	check (array1 -> remove_element_from_end ())
	check (array1 -> print_array ())
	
	sorted_array <int>* sarr = new sorted_array <int> ();
	sarr -> init_array ();
	sarr -> add_element (5);
	check (sarr -> search (5) == 1)
	printf ("search result is %i\n", sarr -> search (5));
	sarr -> delete_array ();
	delete sarr;
	
	check (array1 -> bubble_sort ())
	check (array1 -> print_array ())
	
	check (array1 -> change_element (3, 7))
	check (array1 -> print_array    ())
	
	check (array1 -> zero_array  ())
	check (array1 -> print_array ())
	printf ("datalen = %i, memlen = %i\n", array1 -> get_datalen (), array1 -> get_memlen ());
	
	for (int i = 0; i < MAX_DATASZ - 70; i ++)
		array1 -> add_element_to_end (41);
	
	check (array1 -> delete_array ())
	print_exit_message ();
	check (array2 -> delete_array ())
	print_exit_message ();
	delete array1;
	delete array2;
	*/
	return 0;
	}
