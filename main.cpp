#include <iostream>
#include <vector>
#include <string>

#include "list.h"
#include "sortsUtils.h"
#include "tree.h"
#include "times.h"

using namespace std;

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
    
    // TUTORIAL DE COMO FUNCIONA O RADIX SORT
    tutorialRadixSort();

    // ÁRVORE
    treeTime(100, 10000, "output/tree_time.csv");

    // Arquivo de todos os tempos das funções
    vector<string> arquivos = {"output/bubbleSort_time.csv","output/selectionSort_time.csv",
                                "output/insertSort_time.csv","output/radixSort_time.csv","output/tree_time.csv"};

    string saida = "output/all_times.csv";

    concatenaCSV(arquivos, saida);

    return 0;
}