#include <iostream>
#include <chrono>
#include <fstream>
#include "selectionSortUtils.h"
#include "bubbleSortUtils.h"
#include "insertionSortUtils.h"

using namespace std;
using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::nanoseconds;

int main() 
{
    // BUBBLE SORT

        int iNumLinhas = 100;

    // Inicialização da semente do gerador de números aleatórios com o tempo atual
    srand(time(nullptr)); 
    ofstream outputFile("bubbleSort_time.csv", ios::out | ios::trunc);
    
    outputFile << "Quantidade de Elementos,Tempo Bubble Sort Padrão,Tempo Bubble Sort Otimizado" << endl;

    Node* head1 = nullptr;
    Node* head2 = nullptr;

    for (int i = 1; i <= iNumLinhas ; i ++) 
    {
        addRandomElements(&head1, 10000, i);
        head2 = copyList(&head1);

        auto timeStart1 = high_resolution_clock::now();
        bubbleSort(&head1);
        auto timeStop1 = high_resolution_clock::now();

        auto timeStart2 = high_resolution_clock::now();
        optimizedBubbleSort(&head2,10000);
        auto timeStop2 = high_resolution_clock::now();

        auto timeDuration1 = duration_cast<nanoseconds>(timeStop1 - timeStart1);
        auto timeDuration2 = duration_cast<nanoseconds>(timeStop2 - timeStart2);

        outputFile << 10000 << "," << timeDuration1.count() << "," << timeDuration2.count() << endl;
        clearList(&head1);
        clearList(&head2);
    }

    outputFile.close();

    // SELECTION SORT

    int iNumLinhas = 100;

    // Inicialização da semente do gerador de números aleatórios com o tempo atual
    srand(time(nullptr)); 
    ofstream outputFile("selectionSort_time.csv", ios::out | ios::trunc);
    
    outputFile << "Quantidade de Elementos,Tempo Selection Sort Padrão,Tempo Selection Sort Otimizado" << endl;

    Node* head1 = nullptr;
    Node* head2 = nullptr;

    for (int i = 1; i <= iNumLinhas ; i ++) 
    {
        addRandomElements(&head1, 10000, i);
        head2 = copyList(&head1);

        auto timeStart1 = high_resolution_clock::now();
        selectionSort(&head1);
        auto timeStop1 = high_resolution_clock::now();

        auto timeStart2 = high_resolution_clock::now();
        optimizedSelectionSort(&head2);
        auto timeStop2 = high_resolution_clock::now();

        auto timeDuration1 = duration_cast<nanoseconds>(timeStop1 - timeStart1);
        auto timeDuration2 = duration_cast<nanoseconds>(timeStop2 - timeStart2);

        outputFile << 10000 << "," << timeDuration1.count() << "," << timeDuration2.count() << endl;
        clearList(&head1);
        clearList(&head2);
    }

    outputFile.close();

    // INSECTION SORT
    
        int iNumLinhas = 100;

    // Inicialização da semente do gerador de números aleatórios com o tempo atual
    srand(time(nullptr)); 
    ofstream outputFile("insertSort_time.csv", ios::out | ios::trunc);
    
    outputFile << "Quantidade de Elementos,Tempo (nanossegundos)" << endl;

    Node* head = nullptr;

    for (int i = 1; i <= iNumLinhas ; i ++) 
    {
        addRandomElements(&head, 10000, i);

        auto timeStart = high_resolution_clock::now();
        insertSort(&head);
        auto timeStop = high_resolution_clock::now();

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);

        outputFile << 10000 << "," << timeDuration.count() << endl;
        clearList(&head);
    }

    outputFile.close();
    
    return 0;
}