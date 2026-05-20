cmake_minimum_required(VERSION 3.20)
project(esercitazione5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

# Creo il target per l'eseguibile principale del mio progetto software
set(SRC_test_sorts timecounter.cpp measure_sorts.cpp)
add_executable(measure_sorts ${SRC_test_sorts})

set(SRC_test_sorts timecounter.cpp new_measure_sorts.cpp)
add_executable(new_measure_sorts ${SRC_test_sorts})

## Creo i target per gli eseguibili che effettueranno i test unitari
add_executable(test_bubble_sort test_bubble_sort.cpp)
add_test(NAME bubble_sort COMMAND test_bubble_sort)

add_executable(test_insertion_sort test_insertion_sort.cpp)
add_test(NAME insertion_sort COMMAND test_insertion_sort)

add_executable(test_selection_sort test_selection_sort.cpp)
add_test(NAME selection_sort COMMAND test_selection_sort)

add_executable(test_mergesort test_mergesort.cpp)
add_test(NAME mergesort COMMAND test_mergesort)

add_executable(test_quicksort test_quicksort.cpp)
add_test(NAME quicksort COMMAND test_quicksort)

enable_testing()