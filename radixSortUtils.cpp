#include <iostream>
#include <chrono>
#include <fstream>

#include "list.h"
#include "sortsUtils.h"

using namespace std;

using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::nanoseconds;

void radixSort(Node** head, int iLength)
{
    /*Essa função realiza a ordenação de uma lista duplamente encadeada 
    por meio do método Radix Sort.*/

    Node* ptrCurrent = *head;
    int iMaxValue = maxList(*head);

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

void radixSortTime(int iNumLinhas, const string& filename) 
{
    // Inicialização da semente do gerador de números aleatórios com o tempo atual
    srand(time(nullptr));

    ofstream outputFile(filename, ios::out | ios::trunc);
    outputFile << "Tempo (nanossegundos)" << endl;

    Node* head = nullptr;

    for (int i = 1; i <= iNumLinhas; i++) {
        addRandomElements(&head, 10000, i);

        auto timeStart = high_resolution_clock::now();
        radixSort(&head, 10000);
        auto timeStop = high_resolution_clock::now();

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);

        outputFile << timeDuration.count() << endl;
        clearList(&head);
    }

    outputFile.close();
}