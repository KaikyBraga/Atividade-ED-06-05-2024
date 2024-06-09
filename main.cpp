#include <iostream>
#include "list.h"
#include "sortsUtils.h"
#include "tree.h"

int main() 
{
    // BUBBLE SORT
    bubbleSortTime(100, 10000, "output/bubbleSort_time.csv");

    // SELECTION SORT
    selectionSortTime(100, 10000, "output/selectionSort_time.csv");

    // INSECTION SORT
    insertSortTime(100, 10000, "output/insertSort_time.csv");
    
    // RADIX SORT
    radixSortTime(100, 10000, "output/radixSort_time.csv");
    
    tutorialRadixSort();    

    return 0;
}