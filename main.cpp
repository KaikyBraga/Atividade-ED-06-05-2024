#include <iostream>
#include "list.h"
#include "sortsUtils.h"
#include "tree.h"

int main() 
{
    // NodeTr<int>* root = nullptr;

    // root = insertNodeTree(root, 42);
    // root = insertNodeTree(root, 13);
    // root = insertNodeTree(root, 11);
    // root = insertNodeTree(root, 10);
    // root = insertNodeTree(root, 28);
    // root = insertNodeTree(root, 51);
    // root = insertNodeTree(root, 171);
    
    // NodeTr<int>* node = searchNode(root, 28);
    // std::cout << node->payload << std::endl;

    // node = dfSearchPreOrder(root, 28);
    // std::cout << node->payload << std::endl;
    
    // node = dfSearchInOrder(root, 28);
    // std::cout << node->payload << std::endl;
    
    // node = dfSearchPostOrder(root, 28);
    // std::cout << node->payload << std::endl;

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

    return 0;
}