#include <iostream>
#include <chrono>
#include <fstream>

#include "list.h"
#include "sortsUtils.h"

using namespace std;

using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::nanoseconds;

int main() 
{
    // BUBBLE SORT
    bubbleSortTime(100, "output/bubbleSort_time.csv");

    // SELECTION SORT
    selectionSortTime(100, "output/selectionSort_time.csv");

    // INSECTION SORT
    insertSortTime(100, "output/insertSort_time.csv");
    
    // RADIX SORT
    radixSortTime(100, "output/radixSort_time.csv");

    return 0;
}