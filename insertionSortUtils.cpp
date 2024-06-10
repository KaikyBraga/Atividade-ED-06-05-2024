#include <iostream>

#include "list.h"
#include "sortsUtils.h"

using namespace std;

template <typename T> 
void insertSort(Node<T>** head)
{
    /*
    Esta função implementa o método de ordenação de uma lista duplamente encadeada
    por meio do método de Insertion Sort.
    */

    // Caso a lista não tenha elementos ou tiver apenas um nó
    if (head == nullptr || (*head)->ptrNext == nullptr)
        return; 

    Node<T>* ptrOuterNode = (*head)->ptrNext; 
    Node<T>* ptrInnerNode = nullptr;
    T insertValue;

    // Loop Externo (Começa sempre no segundo nó)
    while (ptrOuterNode != nullptr)
    {
        // Valor de troca
        insertValue = ptrOuterNode->payload;

        // Loop Interno (Começa sempre do nó anterior do Loop Externo)
        ptrInnerNode = ptrOuterNode->ptrPrev;
        while (ptrInnerNode != nullptr && insertValue < ptrInnerNode->payload)
        {
            // Caso o valor do nó seja maior que o do valor de troca,
            // então o valor do sucessor desse nó é alterado para o valor desse nó
            ptrInnerNode->ptrNext->payload = ptrInnerNode->payload;

            // Pegando o nó anterior no Loop Interno
            ptrInnerNode = ptrInnerNode->ptrPrev;
        }

        // Caso o Loop Interno percorra todos os nós anteriores ao Loop Externo
        if (ptrInnerNode == nullptr) 
        {
            (*head)->payload = insertValue;
        } 

        else 
        {
            ptrInnerNode->ptrNext->payload = insertValue;
        }

        // Preparando o Loop Externo para a próxima iteração
        ptrOuterNode = ptrOuterNode->ptrNext;
    }
}

template void insertSort(Node<int>**);