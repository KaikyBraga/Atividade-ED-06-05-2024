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
void selectionSort(Node<T>** head)
{
    /*Essa função realiza a ordenação de uma lista duplamente encadeada 
    por meio do método Selection Sort*/

    // Inicializando nós para percorrerem a lista
    Node<T>* ptrOuterNode = *head;
    Node<T>* ptrInnerNode = *head;

    // Realizando verificação para todos os nós
    while(ptrOuterNode != nullptr)
    {
        // O nó de troca recebe o nó posterior ao de fora
        ptrInnerNode = ptrOuterNode->ptrNext;

        // O nó de dentro percorre até o último elemento da lista
        while (ptrInnerNode != nullptr)
        {
            // Condição de Troca
            if (ptrOuterNode->payload > ptrInnerNode->payload)
            {
                swapValue(ptrOuterNode, ptrInnerNode);
            }

            ptrInnerNode = ptrInnerNode->ptrNext;
        }

        ptrOuterNode = ptrOuterNode->ptrNext;
    }
}

template <typename T> 
void optimizedSelectionSort(Node<T>** head)
{
    /*Essa função realiza a ordenação de uma lista duplamente encadeada 
    por meio do método Selection Sort de maneira otimizada.*/

    T minValue = 0;

    // Inicializando nós para percorrerem a lista
    Node<T>* ptrOuterNode = *head;
    Node<T>* ptrInnerNode = *head;
    Node<T>* ptrSwapNode = *head;

    // Realizando verificação para todos os nós
    while(ptrOuterNode != nullptr)
    {
        // O nó de dentro recebe o nó posterior ao de fora
        ptrInnerNode = ptrOuterNode->ptrNext;

        // O nó de troca recebe o nó de fora
        ptrSwapNode = ptrOuterNode;

        // O valor mínimo é inicialiazado com valor do nó de fora
        minValue = ptrOuterNode->payload;

        // Verificação para todos nós posteriores ao de fora
        while (ptrInnerNode != nullptr)
        {
            // Condição de Troca
            if (minValue > ptrInnerNode->payload)
            {
                minValue = ptrInnerNode->payload;
                ptrSwapNode = ptrInnerNode;
            }

            ptrInnerNode = ptrInnerNode->ptrNext;
        }

        // Troca de valores entre os nós
        swapValue(ptrOuterNode, ptrSwapNode); 

        ptrOuterNode = ptrOuterNode->ptrNext;
    }
}

void selectionSortTime(int iNumLinhas, int iLength, const string& strFILENAME) 
{
    // Inicialização da semente do gerador de números aleatórios com o tempo atual
    srand(time(nullptr));
    
    ofstream outputFile(strFILENAME, ios::out | ios::trunc);
    outputFile << "Tempo Selection Sort Padrão,Tempo Selection Sort Otimizado" << endl;

    Node<int>* head1 = nullptr;
    Node<int>* head2 = nullptr;

    for (int i = 1; i <= iNumLinhas; i++) 
    {
        addRandomElements(&head1, iLength, i);
        head2 = copyList(&head1);

        auto timeStart1 = high_resolution_clock::now();
        selectionSort(&head1);
        auto timeStop1 = high_resolution_clock::now();

        auto timeStart2 = high_resolution_clock::now();
        optimizedSelectionSort(&head2);
        auto timeStop2 = high_resolution_clock::now();

        auto timeDuration1 = duration_cast<nanoseconds>(timeStop1 - timeStart1);
        auto timeDuration2 = duration_cast<nanoseconds>(timeStop2 - timeStart2);

        outputFile << timeDuration1.count() << "," << timeDuration2.count() << endl;

        clearList(&head1);
        clearList(&head2);
    }

    outputFile.close();
}

