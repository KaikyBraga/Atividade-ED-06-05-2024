#include <iostream>

#include "list.h"
#include "sortsUtils.h"

using namespace std;

template <typename T> 
void bubbleSort(Node<T>** head)
{
    /*Essa função realiza a ordenação de uma lista duplamente encadeada 
    por meio do método Bubble Sort*/

    Node<T>* ptrOuterNode = *head;
    Node<T>* ptrInnerNode = *head;

    if (ptrOuterNode == nullptr || ptrOuterNode->ptrNext == nullptr) return;
    
    while (ptrOuterNode != nullptr)
    {
        ptrInnerNode = *head;

        while (ptrInnerNode->ptrNext != nullptr)
        {
            if (ptrInnerNode->payload > ptrInnerNode->ptrNext->payload)
                swapValue(ptrInnerNode, ptrInnerNode->ptrNext);

            ptrInnerNode = ptrInnerNode->ptrNext;
        }
        ptrOuterNode = ptrOuterNode->ptrNext;
    }
}

template <typename T> 
void optimizedBubbleSort(Node<T>** head, int iLength)
{
    /*Essa função realiza a ordenação de uma lista duplamente encadeada 
    por meio do método Bubble Sort de maneira otimizada.*/

    Node<T>* ptrCurrent = *head;

    if (ptrCurrent == nullptr || ptrCurrent->ptrNext == nullptr) return;
    
    bool bUnordered = false;

    for (int iOuterLoop = 0; iOuterLoop < iLength - 1; iOuterLoop++)
    {
        bUnordered = false;

        for (int iInnerLoop = 0; iInnerLoop < (iLength - 1) - iOuterLoop; iInnerLoop++)
        {
            if (ptrCurrent->payload > ptrCurrent->ptrNext->payload)
            {
                swapValue(ptrCurrent, ptrCurrent->ptrNext);
                bUnordered = true;
            }
            ptrCurrent = ptrCurrent->ptrNext;
        }

        ptrCurrent = *head;
        if (bUnordered == false) break;    
    }
}

template void bubbleSort(Node<int>**);
template void optimizedBubbleSort(Node<int>**, int);