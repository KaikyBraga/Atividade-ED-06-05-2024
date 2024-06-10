#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>

#include "list.h"
#include "tree.h"
#include "sortsUtils.h"
#include "times.h"

using namespace std;

using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::nanoseconds;

void bubbleSortTime(int iNumLinhas, int iLength, const string& strFILENAME) 
{
    // Inicialização da semente do gerador de números aleatórios com o tempo atual
    srand(time(nullptr));
    
    ofstream outputFile(strFILENAME, ios::out | ios::trunc);
    outputFile << "Bubble Sort Padrão,Bubble Sort Otimizado" << endl;

    Node<int>* head1 = nullptr;
    Node<int>* head2 = nullptr;
   
    for (int i = 1; i <= iNumLinhas; i++) 
    {
        addRandomElements(&head1, iLength, i);
        head2 = copyList(&head1);

        auto timeStart1 = high_resolution_clock::now();
        bubbleSort(&head1);
        auto timeStop1 = high_resolution_clock::now();

        auto timeStart2 = high_resolution_clock::now();
        optimizedBubbleSort(&head2, 10000);
        auto timeStop2 = high_resolution_clock::now();

        auto timeDuration1 = duration_cast<nanoseconds>(timeStop1 - timeStart1);
        auto timeDuration2 = duration_cast<nanoseconds>(timeStop2 - timeStart2);

        outputFile << timeDuration1.count() << "," << timeDuration2.count() << endl;

        clearList(&head1);
        clearList(&head2);
    }

    outputFile.close();
}


void selectionSortTime(int iNumLinhas, int iLength, const string& strFILENAME) 
{
    // Inicialização da semente do gerador de números aleatórios com o tempo atual
    srand(time(nullptr));
    
    ofstream outputFile(strFILENAME, ios::out | ios::trunc);
    outputFile << "Selection Sort Padrão,Selection Sort Otimizado" << endl;

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

 
void insertSortTime(int iNumLinhas, int iLength, const string& strFILENAME) 
{
    // Inicialização da semente do gerador de números aleatórios com o tempo atual
    srand(time(nullptr));

    ofstream outputFile(strFILENAME, ios::out | ios::trunc);
    outputFile << "Insertion Sort" << endl;

    Node<int>* head = nullptr;

    for (int i = 1; i <= iNumLinhas; i++) 
    {
        addRandomElements(&head, iLength, i);

        auto timeStart = high_resolution_clock::now();
        insertSort(&head);
        auto timeStop = high_resolution_clock::now();

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);

        outputFile << timeDuration.count() << endl;
        clearList(&head);
    }

    outputFile.close();
}


void radixSortTime(int iNumLinhas, int iLength, const string& strFILENAME) 
{
    // Inicialização da semente do gerador de números aleatórios com o tempo atual
    srand(time(nullptr));

    ofstream outputFile(strFILENAME, ios::out | ios::trunc);
    outputFile << "Radix Sort" << endl;

    Node<int>* head = nullptr;

    for (int i = 1; i <= iNumLinhas; i++) 
    {
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


void treeTime(int iNumLinhas, int iLength, const string& strFILENAME)
{
    // Inicialização da semente do gerador de números aleatórios com o tempo atual
    srand(time(nullptr));

    ofstream outputFile(strFILENAME, ios::out | ios::trunc);
    outputFile << "Criação de Árvores,Criação de Listas,bfSearch,dfSearchPreOrder,dfSearchInOrder,dfSearchPostOrder" << endl;

    for (int i = 1; i <= iNumLinhas; i++) 
    {
        // Criação de Listas
        auto timeStart1 = high_resolution_clock::now();

        Node<int>* head = nullptr;
        addRandomElements(&head, iLength, i);

        auto timeStop1 = high_resolution_clock::now();
        auto timeDuration1 = duration_cast<nanoseconds>(timeStop1 - timeStart1);
        
        Node<int>* currentNode = head;

        // Criação de árvores com valores payLoads da lista criada anteriormente
        auto timeStart2 = high_resolution_clock::now();
        NodeTr<int>* root = nullptr;

        while (currentNode != nullptr) 
        {
            root = insertNodeTree(root, currentNode->payload);
            currentNode = currentNode->ptrNext;
        }
        auto timeStop2 = high_resolution_clock::now();
        auto timeDuration2 = duration_cast<nanoseconds>(timeStop2 - timeStart2);

        // Valor a ser buscado
        int iSortValue = (rand() % iLength) + 1;

        // Tempo de Busca bfSearch
        auto timeStart3 = high_resolution_clock::now();

        NodeTr<int>* NodeFound1 = bfSearch(root, iSortValue);
        
        auto timeStop3 = high_resolution_clock::now();
        auto timeDuration3 = duration_cast<nanoseconds>(timeStop3 - timeStart3);

        // Tempo de Busca dfSearchPreOrder
        auto timeStart4 = high_resolution_clock::now();

        NodeTr<int>* NodeFound2 = dfSearchPreOrder(root, iSortValue);

        auto timeStop4 = high_resolution_clock::now();
        auto timeDuration4 = duration_cast<nanoseconds>(timeStop4 - timeStart4);

        // Tempo de Busca dfSearchInOrder
        auto timeStart5 = high_resolution_clock::now();

        NodeTr<int>* NodeFound3 = dfSearchInOrder(root, iSortValue);

        auto timeStop5 = high_resolution_clock::now();
        auto timeDuration5 = duration_cast<nanoseconds>(timeStop5 - timeStart5);

        // Tempo de Busca dfSearchPostOrder
        auto timeStart6 = high_resolution_clock::now();

        NodeTr<int>* NodeFound4 = dfSearchPostOrder(root, iSortValue);

        auto timeStop6 = high_resolution_clock::now();
        auto timeDuration6 = duration_cast<nanoseconds>(timeStop6 - timeStart6);

        // Tempos para a iteração
        outputFile << timeDuration2.count() << "," << timeDuration1.count() << "," << timeDuration3.count() << "," << timeDuration4.count() << "," << timeDuration5.count() << "," << timeDuration6.count() << endl;

        deleteTree(root);
        clearList(&head);
    }

    outputFile.close();
}


void concatenaCSV(const vector<string>& arquivos, const string& arquivoSaida) {
    // Essa função concatena CSVs um do lado do outro.

    ofstream saida(arquivoSaida);

    if (!saida.is_open()) 
    {
        cerr << "Erro ao abrir o arquivo de saída." << endl;
        return;
    }

    vector<ifstream> entradas;
    for (const string& nome_arquivo : arquivos) 
    {
        ifstream entrada(nome_arquivo);
        if (!entrada.is_open()) 
        {
            cerr << "Erro ao abrir o arquivo: " << nome_arquivo << endl;
            return;
        }
        entradas.push_back(move(entrada));
    }

    string linha;
    bool primeiraLinha = true;

    while (1) 
    {
        string linhaConcatenada;

        // Leitura de uma linha de cada arquivo
        for (size_t i = 0; i < entradas.size(); ++i) 
        {
            if (!getline(entradas[i], linha)) 
            {
                // Se não houver mais linhas em algum arquivo, encerra o loop
                saida.close();
                for (auto& entrada : entradas) 
                    entrada.close();

                return;
            }
            if (i != 0) 
                linhaConcatenada += ",";
        
            linhaConcatenada += linha;
        }

        // Escrevendo a linha concatenada no arquivo de saída
        if (!primeiraLinha)
            saida << endl;
        
        else
            primeiraLinha = false;

        saida << linhaConcatenada;
    }
}
