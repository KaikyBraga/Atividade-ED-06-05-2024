#include <iostream>
#include <chrono>
#include <fstream>

#include "list.h"
#include "sortsUtils.h"

using namespace std;

using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::nanoseconds;

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

void bubbleSortTime(int iNumLinhas, int iLength, const string& strFILENAME) 
{
    // Inicialização da semente do gerador de números aleatórios com o tempo atual
    srand(time(nullptr));
    
    ofstream outputFile(strFILENAME, ios::out | ios::trunc);
    outputFile << "Tempo Bubble Sort Padrão,Tempo Bubble Sort Otimizado" << endl;

    Node<int>* head1 = nullptr;
    Node<int>* head2 = nullptr;
   
    for (int i = 1; i <= iNumLinhas; i++) 
    {
        addRandomElements(&head1, iLength, i);
        head2 = copyList(&head1);

        auto timeStart1 = high_resolution_clock::now();
        bubbleSort(&head1);
        auto timeStop1 = high_resolution_clock::now();

        auto timeStart2 = high_resolution_clock::now();
        optimizedBubbleSort(&head2, 10000);
        auto timeStop2 = high_resolution_clock::now();

        auto timeDuration1 = duration_cast<nanoseconds>(timeStop1 - timeStart1);
        auto timeDuration2 = duration_cast<nanoseconds>(timeStop2 - timeStart2);

        outputFile << timeDuration1.count() << "," << timeDuration2.count() << endl;

        clearList(&head1);
        clearList(&head2);
    }

    outputFile.close();
}