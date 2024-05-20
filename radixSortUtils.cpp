#include <iostream>

#include "list.h"
#include "sortsUtils.h"

int MaxList(Node* head)
{
    /*
    Essa função calcula o valor máximo de uma lista.
    */

    int iMaxValue = head->iPayload;
    Node* current = head;

    while (current != nullptr)
    {
        if (current->iPayload > iMaxValue)
        {
            iMaxValue = current->iPayload;
        }

        current = current->ptrNext;
    }

    return iMaxValue;
}

void radixSort(Node** head, int iLength)
{
    /*Essa função realiza a ordenação de uma lista duplamente encadeada 
    por meio do método Radix Sort.*/

    Node* ptrCurrent = *head;
    int iMaxValue = MaxList(*head);

    if (ptrCurrent == nullptr || ptrCurrent->ptrNext == nullptr) return;
    
    for (int iExp = 1; iMaxValue / iExp > 0; iExp *= 10)
    {
        bool bUnordered = false;
        int i = 0;
        for (int iOuterLoop = 0; iOuterLoop < iLength - 1; iOuterLoop++)
        {
            bUnordered = false;

            for (int iInnerLoop = 0; iInnerLoop < (iLength - 1) - iOuterLoop; iInnerLoop++)
            {
                if (((ptrCurrent->iPayload / iExp) % 10) > ((ptrCurrent->ptrNext->iPayload / iExp) % 10))
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
}