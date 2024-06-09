#include <iostream>
#include "list.h"
#include "tree.h"

using namespace std;

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

template NodeTr<int>* createNodeTree(int);
template NodeTr<int>* insertNodeTree(NodeTr<int>*, int);
template void bfsTraversal(NodeTr<int>*);
template NodeTr<int>* bfSearch(NodeTr<int>*, int);
template NodeTr<int>* searchNode(NodeTr<int>*, int);
template NodeTr<int>* dfSearchPreOrder(NodeTr<int>*, int);
template NodeTr<int>* dfSearchInOrder(NodeTr<int>*, int);
template NodeTr<int>* dfSearchPostOrder(NodeTr<int>*, int);