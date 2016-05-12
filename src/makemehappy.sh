#!/bin/bash
make -f array_make
valgrind --leak-check=full --leak-resolution=med ./2task
gcov -b ./2task.cpp | tee output.txt
