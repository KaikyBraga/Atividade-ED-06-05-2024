#include <iostream>

#include "list.h"
#include "sortsUtils.h"

void insertSort(Node** head)
{
    /*
    Esta função implementa o método de ordenação de uma lista duplamente encadeada
    por meio do método de Insertion Sort.
    */

    // Caso a lista não tenha elementos ou tiver apenas um nó
    if (head == nullptr || (*head)->ptrNext == nullptr)
        return; 

    Node* ptrOuterNode = (*head)->ptrNext; 
    Node* ptrInnerNode = nullptr;
    int iInsertValue = 0;

    // Loop Externo (Começa sempre no segundo nó)
    while (ptrOuterNode != nullptr)
    {
        // Valor de troca
        iInsertValue = ptrOuterNode->iPayload;

        // Loop Interno (Começa sempre do nó anterior do Loop Externo)
        ptrInnerNode = ptrOuterNode->ptrPrev;
        while (ptrInnerNode != nullptr && iInsertValue < ptrInnerNode->iPayload)
        {
            // Caso o valor do nó seja maior que o do valor de troca,
            // então o valor do sucessor desse nó é alterado para o valor desse nó
            ptrInnerNode->ptrNext->iPayload = ptrInnerNode->iPayload;

            // Pegando o nó anterior no Loop Interno
            ptrInnerNode = ptrInnerNode->ptrPrev;
        }

        // Caso o Loop Interno percorra todos os nós anteriores ao Loop Externo
        if (ptrInnerNode == nullptr) 
        {
            (*head)->iPayload = iInsertValue;
        } 

        else 
        {
            ptrInnerNode->ptrNext->iPayload = iInsertValue;
        }

        // Preparando o Loop Externo para a próxima iteração
        ptrOuterNode = ptrOuterNode->ptrNext;
    }
}