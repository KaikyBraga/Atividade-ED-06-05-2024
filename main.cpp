#include <iostream>
#include "list.h"
#include "sortsUtils.h"
#include "tree.h"

#include <fstream>
#include <vector>
#include <string>
using namespace std;
void concatenaCSV(const vector<string>& arquivos, const string& arquivoSaida) 
{
    // Essa função concatena CSVs um do lado do outro.

    ofstream saida(arquivoSaida);

    if (!saida.is_open()) 
    {
        cerr << "Erro ao abrir o arquivo de saída." << endl;
        return;
    }

    vector<ifstream> entradas;
    for (const string& nomeArquivo : arquivos) 
    {
        ifstream entrada(nomeArquivo);
        if (!entrada.is_open()) 
        {
            cerr << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
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

int main() 
{
    // BUBBLE SORT
    bubbleSortTime(100, 10000, "output/bubbleSort_time.csv");

    // SELECTION SORT
    selectionSortTime(100, 10000, "output/selectionSort_time.csv");

    // INSECTION SORT
    insertSortTime(100, 10000, "output/insertSort_time.csv");
    
    // RADIX SORT
    radixSortTime(100, 10000, "output/radixSort_time.csv");
    
    // TUTORIAL DE COMO FUNCIONA O RADIX SORT
    tutorialRadixSort(); 

    // ÁRVORE
    treeTime(100, 10000, "output/tree_time.csv");

    // Arquivo de todos os tempos das funções
    concatenaCSV({"output/bubbleSort_time.csv", "output/selectionSort_time.csv", "output/insertSort_time.csv", "output/radixSort_time.csv","output/tree_time.csv"}, "output/all_times.csv");

    return 0;
}