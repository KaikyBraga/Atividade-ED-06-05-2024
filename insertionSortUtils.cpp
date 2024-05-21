#include <iostream>
#include <chrono>
#include <fstream>

#include "list.h"
#include "sortsUtils.h"

using namespace std;

using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::nanoseconds;

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

void insertSortTime(int iNumLinhas, const string& filename) {
    // Inicialização da semente do gerador de números aleatórios com o tempo atual
    srand(time(nullptr));

    ofstream outputFile(filename, ios::out | ios::trunc);
    outputFile << "Tempo (nanossegundos)" << endl;

    Node* head = nullptr;

    for (int i = 1; i <= iNumLinhas; i++) {
        addRandomElements(&head, 10000, i);

        auto timeStart = high_resolution_clock::now();
        insertSort(&head);
        auto timeStop = high_resolution_clock::now();

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);

        outputFile << timeDuration.count() << endl;
        clearList(&head);
    }

    outputFile.close();
}