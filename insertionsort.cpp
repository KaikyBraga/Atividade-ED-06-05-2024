#include <iostream>
#include <chrono>
#include <fstream>
#include "insertionsortUtils.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::rand;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::ios;
using std::ofstream;

int main() 
{
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