#include "array.cpp"

int main ()
	{
	struct array array1;
	struct array array2;
	
	check (array1.init_array ())
	check (array2.init_array ())
	
	check (array1.verbose_full_print ())
	
	check (array1.add_element_to_end (5))
	check (array1.add_element_to_end (1))
	check (array1.add_element_to_end (8))
	check (array1.add_element_to_end (41))
	check (array1.add_element_to_end (3))
	check (array1.add_element_to_end (3))
	check (array1.add_element_to_end (8))
	check (array1.add_element_to_end (13))
	check (array1.verbose_full_print ())
	check (array1.remove_element_from_end ())
	check (array1.print_array ())
	
	check (array1.bubble_sort ())
	check (array1.print_array ())
	
	check (array1.change_element (3, 7))
	check (array1.print_array    ())
	
	check (array1.zero_array  ())
	check (array1.print_array ())
	printf ("datalen = %i, memlen = %i\n", array1.get_datalen (), array1.get_memlen ());
	
	for (int i = 0; i < MAX_DATASZ + 5; i ++)
		array1.add_element_to_end (41);
	
	check (array1.delete_array ())
	print_exit_message ();
	check (array2.delete_array ())
	print_exit_message ();
	
	return 0;
	}
