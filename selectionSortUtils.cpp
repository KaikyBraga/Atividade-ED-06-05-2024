#include <iostream>

#include "list.h"
#include "sortsUtils.h"

using namespace std;

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

template void selectionSort(Node<int>**);
template void optimizedSelectionSort(Node<int>**);