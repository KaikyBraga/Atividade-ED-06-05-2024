#include <iostream>

#include "list.h"
#include "sortsUtils.h"

void selectionSort(Node** head)
{
    /*Essa função realiza a ordenação de uma lista duplamente encadeada 
    por meio do método Selection Sort*/

    // Inicializando nós para percorrerem a lista
    Node* ptrOuterNode = *head;
    Node* ptrInnerNode = *head;

    // Realizando verificação para todos os nós
    while(ptrOuterNode != nullptr)
    {
        // O nó de troca recebe o nó posterior ao de fora
        ptrInnerNode = ptrOuterNode->ptrNext;

        // O nó de dentro percorre até o último elemento da lista
        while (ptrInnerNode != nullptr)
        {
            // Condição de Troca
            if (ptrOuterNode->iPayload > ptrInnerNode->iPayload)
            {
                swapValue(ptrOuterNode, ptrInnerNode);
            }

            ptrInnerNode = ptrInnerNode->ptrNext;
        }

        ptrOuterNode = ptrOuterNode->ptrNext;
    }
}

void optimizedSelectionSort(Node** head)
{
    /*Essa função realiza a ordenação de uma lista duplamente encadeada 
    por meio do método Selection Sort de maneira otimizada.*/

    int iMinValue = 0;

    // Inicializando nós para percorrerem a lista
    Node* ptrOuterNode = *head;
    Node* ptrInnerNode = *head;
    Node* ptrSwapNode = *head;

    // Realizando verificação para todos os nós
    while(ptrOuterNode != nullptr)
    {
        // O nó de dentro recebe o nó posterior ao de fora
        ptrInnerNode = ptrOuterNode->ptrNext;

        // O nó de troca recebe o nó de fora
        ptrSwapNode = ptrOuterNode;

        // O valor mínimo é inicialiazado com valor do nó de fora
        iMinValue = ptrOuterNode->iPayload;

        // Verificação para todos nós posteriores ao de fora
        while (ptrInnerNode != nullptr)
        {
            // Condição de Troca
            if (iMinValue > ptrInnerNode->iPayload)
            {
                iMinValue = ptrInnerNode->iPayload;
                ptrSwapNode = ptrInnerNode;
            }

            ptrInnerNode = ptrInnerNode->ptrNext;
        }

        // Troca de valores entre os nós
        swapValue(ptrOuterNode, ptrSwapNode); 

        ptrOuterNode = ptrOuterNode->ptrNext;
    }
}

void addRandomElements(Node** head, int iQuantElements, int iMaxValue)
{
    // Essa função adiciona elementos aleatórios em uma Lista duplamente encadeada.
    // É possível passar o Valor máximo da carga Payload.

    for (int i=0; i < iQuantElements; i++)
        insertEnd(head, (rand() % iMaxValue) + 1);
}

