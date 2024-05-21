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