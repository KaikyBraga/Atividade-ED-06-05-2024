#include <iostream>
#include <chrono>
#include <fstream>
#include "list.h"
#include "tree.h"

using namespace std;
using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::nanoseconds;

template <typename T>
NodeTr<T>* createNodeTree(T tValue)
{
    NodeTr<T>* tmp = (NodeTr<T>*) malloc(sizeof(NodeTr<T>));
    
    if (tmp == nullptr)
    {
        cerr << "Erro em createNode: malloc" << endl;
        exit(1);
    }
    
    tmp->payload = tValue;
    tmp->ptrLeft = nullptr;
    tmp->ptrRight = nullptr;
    
    return tmp;
}

template <typename T>
NodeTr<T>* insertNodeTree(NodeTr<T>* ptrStartingNode, T tValue)
{
    if(ptrStartingNode == nullptr)
    {
        return createNodeTree(tValue);
    }
    
    if(tValue < ptrStartingNode->payload)
    {
        ptrStartingNode->ptrLeft = insertNodeTree(ptrStartingNode->ptrLeft, tValue);
    }
    else
    {
        ptrStartingNode->ptrRight = insertNodeTree(ptrStartingNode->ptrRight, tValue);
    }
    
    return ptrStartingNode;
}

template <typename T>
NodeTr<T>* lesserLeaf(NodeTr<T>* startingNode)
{
    NodeTr<T>* ptrCurrent = startingNode;
 
    while (ptrCurrent && ptrCurrent->ptrLeft != nullptr) ptrCurrent = ptrCurrent->ptrLeft;
    
    return ptrCurrent;
}

template <typename T>
NodeTr<T>* deleteNodeTree(NodeTr<T>* startingNode, T tData)
{
    if (startingNode == nullptr) return nullptr;
    
    if (tData < startingNode->payload) startingNode->ptrLeft = deleteNodeTree(startingNode->ptrLeft, tData);
    else if (tData > startingNode->payload) startingNode->ptrRight = deleteNodeTree(startingNode->ptrRight, tData);
    else
    {
        NodeTr<T>* ptrTemp = nullptr;
        
        if (startingNode->ptrLeft == nullptr)
        {
            ptrTemp = startingNode->ptrRight;
            free(startingNode);
            return ptrTemp;
        }
        else if (startingNode->ptrRight == nullptr)
        {
            ptrTemp = startingNode->ptrLeft;
            free(startingNode);
            return ptrTemp;            
        }
        
        ptrTemp = lesserLeaf(startingNode->ptrRight);
        
        startingNode->payload = ptrTemp->payload;
        
        startingNode->ptrRight = deleteNodeTree(startingNode->ptrRight, ptrTemp->payload);
    }
    
    return startingNode;
}

template <typename T>
void deleteTree(NodeTr<T>* startingNode) 
{
    while (startingNode != nullptr) 
    {
        startingNode = deleteNodeTree(startingNode, startingNode->payload);
    }
}


template <typename T>
void bfsTraversal(NodeTr<T>* ptrStartingNode)
{
    if (ptrStartingNode == nullptr) return;
    
    Node<NodeTr<T>*>* nodeListFront = createNode(ptrStartingNode);
    Node<NodeTr<T>*>* nodeListRear = nodeListFront;

    while (nodeListFront != nullptr)
    {
        NodeTr<T>* currentNode = nodeListFront->payload;
        cout << currentNode->payload << " ";
        
        if (currentNode->ptrLeft != nullptr)
        {
            nodeListRear->ptrNext = createNode(currentNode->ptrLeft);
            nodeListRear = nodeListRear->ptrNext;
        }
        
        if (currentNode->ptrRight != nullptr)
        {
            nodeListRear->ptrNext = createNode(currentNode->ptrRight);
            nodeListRear = nodeListRear->ptrNext;
        }
        
        Node<NodeTr<T>*>* temp = nodeListFront;
        nodeListFront = nodeListFront->ptrNext;
        delete temp;
    }
}

template <typename T>
NodeTr<T>* bfSearch(NodeTr<T>* ptrStartingNode, T tData)
{
    if (ptrStartingNode == nullptr) return nullptr;
    
    Node<NodeTr<T>*>* nodeListFront = createNode(ptrStartingNode);
    Node<NodeTr<T>*>* nodeListRear = nodeListFront;

    while (nodeListFront != nullptr)
    {
        NodeTr<T>* currentNode = nodeListFront->payload;

        if (currentNode->payload == tData) return currentNode;
        
        if (currentNode->ptrLeft != nullptr)
        {
            nodeListRear->ptrNext = createNode(currentNode->ptrLeft);
            nodeListRear = nodeListRear->ptrNext;
        }
        
        if (currentNode->ptrRight != nullptr)
        {
            nodeListRear->ptrNext = createNode(currentNode->ptrRight);
            nodeListRear = nodeListRear->ptrNext;
        }
        
        Node<NodeTr<T>*>* temp = nodeListFront;
        nodeListFront = nodeListFront->ptrNext;
        delete temp;
    }

    cout << "Valor não encontrado" << endl;

    return nullptr;
}

template <typename T>
NodeTr<T>* searchNode(NodeTr<T>* ptrStartingNode, T tData)
{
    if(ptrStartingNode == nullptr) return nullptr;

    else if(tData == ptrStartingNode->payload) return ptrStartingNode;

    else if(tData < ptrStartingNode->payload) return searchNode(ptrStartingNode->ptrLeft, tData);

    else return searchNode(ptrStartingNode->ptrRight, tData);
}

template <typename T>
NodeTr<T>* dfSearchPreOrder(NodeTr<T>* ptrStartingNode, T tData)
{
    if (ptrStartingNode == nullptr) return nullptr;

    if(tData == ptrStartingNode->payload) return ptrStartingNode;

    NodeTr<T>* ptrLeftSearch = dfSearchPreOrder(ptrStartingNode->ptrLeft, tData);
    if (ptrLeftSearch != nullptr) return ptrLeftSearch;

    NodeTr<T>* ptrRightSearch = dfSearchPreOrder(ptrStartingNode->ptrRight, tData);
    if (ptrRightSearch != nullptr) return ptrRightSearch;

    return nullptr;
}

template <typename T>
NodeTr<T>* dfSearchInOrder(NodeTr<T>* ptrStartingNode, T tData)
{
    if (ptrStartingNode == nullptr) return nullptr;

    NodeTr<T>* ptrLeftSearch = dfSearchInOrder(ptrStartingNode->ptrLeft, tData);
    if (ptrLeftSearch != nullptr) return ptrLeftSearch;

    if(tData == ptrStartingNode->payload) return ptrStartingNode;

    NodeTr<T>* ptrRightSearch = dfSearchInOrder(ptrStartingNode->ptrRight, tData);
    if (ptrRightSearch != nullptr) return ptrRightSearch;

    return nullptr;
}

template <typename T>
NodeTr<T>* dfSearchPostOrder(NodeTr<T>* ptrStartingNode, T tData)
{
    if (ptrStartingNode == nullptr) return nullptr;

    NodeTr<T>* ptrLeftSearch = dfSearchPostOrder(ptrStartingNode->ptrLeft, tData);
    if (ptrLeftSearch != nullptr) return ptrLeftSearch;

    NodeTr<T>* ptrRightSearch = dfSearchPostOrder(ptrStartingNode->ptrRight, tData);
    if (ptrRightSearch != nullptr) return ptrRightSearch;

    if(tData == ptrStartingNode->payload) return ptrStartingNode;

    return nullptr;
}

void treeTime(int iNumLinhas, int iLength, const string& strFILENAME)
{
    // Inicialização da semente do gerador de números aleatórios com o tempo atual
    srand(time(nullptr));

    ofstream outputFile(strFILENAME, ios::out | ios::trunc);
    outputFile << "Criação de Árvores,Criação de Listas,bfSearch,dfSearchPreOrder,dfSearchInOrder,dfSearchPostOrder" << endl;

    Node<int>* head = nullptr;
    
    int arri[iLength] = {0};

    for (int i = 1; i <= iNumLinhas; i++) 
    {
        NodeTr<int>* root = nullptr;

        // Valores a serem inseridos na lista/árvore
        for (int j = 0; j < iLength; j ++)
        {
            arri[j] = (rand() % iLength) + 1;
        }

        // Criação de árvores com valores payLoads aleatórios
        auto timeStart1 = high_resolution_clock::now();
        for (int iFolha = 0; iFolha < iLength; iFolha++) 
        {
            root = insertNodeTree(root, arri[iFolha]);
        }
        auto timeStop1 = high_resolution_clock::now();
        auto timeDuration1 = duration_cast<nanoseconds>(timeStop1 - timeStart1);
        
        // Criação de Listas
        auto timeStart2 = high_resolution_clock::now();
        for (int iNode = 0; iNode < iLength; iNode++)
        {
            insertEnd(&head, arri[iNode]);
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
        outputFile << timeDuration1.count() << "," << timeDuration2.count() << "," << timeDuration3.count() << "," << timeDuration4.count() << "," << timeDuration5.count() << "," << timeDuration6.count() << endl;

        deleteTree(root);
        clearList(&head);
    }

    outputFile.close();
}


template NodeTr<int>* createNodeTree(int);
template NodeTr<int>* insertNodeTree(NodeTr<int>*, int);
template NodeTr<int>* lesserLeaf(NodeTr<int>*);
template NodeTr<int>* deleteNodeTree(NodeTr<int>*, int);
template void deleteTree(NodeTr<int>*);
template void bfsTraversal(NodeTr<int>*);
template NodeTr<int>* bfSearch(NodeTr<int>*, int);
template NodeTr<int>* searchNode(NodeTr<int>*, int);
template NodeTr<int>* dfSearchPreOrder(NodeTr<int>*, int);
template NodeTr<int>* dfSearchInOrder(NodeTr<int>*, int);
template NodeTr<int>* dfSearchPostOrder(NodeTr<int>*, int);