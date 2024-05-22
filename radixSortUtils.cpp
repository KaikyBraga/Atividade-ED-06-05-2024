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
void radixSort(Node<T>** head)
{
    /* Essa função realiza a ordenação de uma lista duplamente encadeada 
       por meio do método Radix Sort. */

    // Caso a lista não tenha elementos ou tiver apenas um nó
    if (*head == nullptr || (*head)->ptrNext == nullptr)
        return;

    // Valor máximo na lista
    int iMaxValue = maxList(*head);

    // Loop para cada dígito no valor máximo
    for (int iExp = 1; iMaxValue / iExp > 0; iExp *= 10)
    {
        Node<T>* ptrOuterNode = (*head)->ptrNext;
        
        // Loop externo para percorrer todos os nós da lista
        while (ptrOuterNode != nullptr)
        {
            // Valor do nó atual para inserção
            int iInsertValue = ptrOuterNode->payload;
            Node<T>* ptrInnerNode = ptrOuterNode->ptrPrev;
            
            // Loop interno para encontrar a posição correta para inserção
            while (ptrInnerNode != nullptr && (iInsertValue / iExp) % 10 < (ptrInnerNode->payload / iExp) % 10)
            {
                // Caso o valor do dígito seja maior que o do valor do dígito da troca,
                // então o valor do sucessor desse nó é alterado para o valor desse nó
                ptrInnerNode->ptrNext->payload = ptrInnerNode->payload;
                ptrInnerNode = ptrInnerNode->ptrPrev;
            }

            // Caso o Loop Interno percorra todos os nós anteriores ao Loop Externo
            if (ptrInnerNode == nullptr)
            {
                // Se não houver nó anterior, o valor é inserido no head da lista
                (*head)->payload = iInsertValue;
            }

            else
            {
                // Insere o valor após o nó anterior encontrado
                ptrInnerNode->ptrNext->payload = iInsertValue;
            }

            // Preparando o Loop Externo para a próxima iteração
            ptrOuterNode = ptrOuterNode->ptrNext;
        }
    }
}

void tutorialRadixSort()
{
    /*
    Mostra para o usuário um tutorial de como funciona o algoritmo de ordenação
    Radix Sort.
    */

    cout << "O Radix Sort é um algoritmo de ordenação que utiliza uma comparação entre os algarismos de mesma posição da lista." << endl;
    cout << "Por exemplo, ele compara todas as unidades, em seguida todas as dezenas, e assim por diante." << endl;
    cout << endl;

    cout << "EXEMPLO:" << endl;
    cout << "-----------------------------" << endl;
    cout << "INPUT: [43 79 140 26 721 330]" << endl;
    cout << "-----------------------------" << endl;
    cout << "Algarismos das unidades: [3 9 0 6 1 0]" << endl;
    cout << endl;
    cout << "Ordenamos a lista referente à ordenação das unidades:" << endl;
    cout << "LISTA: [140 330 721 43 26 79]" << endl;
    cout << "-----------------------------" << endl;
    cout << "Algarismos das dezenas: [4 3 2 4 2 7]" << endl;
    cout << endl;
    cout << "Ordenamos a lista referente à ordenação das dezenas:" << endl;
    cout << "LISTA: [721 26 330 140 43 79]" << endl;
    cout << "-----------------------------" << endl;
    cout << "Algarismos das centenas: [7 0 3 1 0 0]" << endl;
    cout << endl;
    cout << "Ordenamos a lista referente à ordenação das centenas:" << endl;
    cout << "LISTA: [26 43 79 140 330 721]" << endl;
    cout << "-----------------------------" << endl;
    cout << "Chegamos ao último algarismo (máximo), encerrando o algoritmo!" << endl;
    cout << "OUTPUT: [26 43 79 140 330 721]" << endl;
}

template <typename T> 
void radixSortTime(int iNumLinhas, int iLength, const string& filename) 
{
    // Inicialização da semente do gerador de números aleatórios com o tempo atual
    srand(time(nullptr));

    ofstream outputFile(filename, ios::out | ios::trunc);
    outputFile << "Tempo (nanossegundos)" << endl;

    Node<int>* head = nullptr;

    for (int i = 1; i <= iNumLinhas; i++) {
        addRandomElements(&head, iLength, i);

        auto timeStart = high_resolution_clock::now();
        radixSort(&head);
        auto timeStop = high_resolution_clock::now();

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);

        outputFile << timeDuration.count() << endl;
        clearList(&head);
    }

    outputFile.close();
}