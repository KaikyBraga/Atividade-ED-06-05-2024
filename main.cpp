#include <iostream>
#include "list.h"
#include "sortsUtils.h"

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