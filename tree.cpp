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
NodeTr<T>* insertNodeTree(NodeTr<T>* startingNode, T tValue)
{
    if(startingNode == nullptr)
    {
        return createNodeTree(tValue);
    }
    
    if(tValue < startingNode->payload)
    {
        startingNode->ptrLeft = insertNodeTree(startingNode->ptrLeft, tValue);
    }
    else
    {
        startingNode->ptrRight = insertNodeTree(startingNode->ptrRight, tValue);
    }
    
    return startingNode;
}

template <typename T>
void bfsTraversal(NodeTr<T>* startingNode)
{
    if (startingNode == nullptr) return;
    
    Node<NodeTr<T>*>* nodeListFront = createNode(startingNode);
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

template NodeTr<int>* createNodeTree(int);
template NodeTr<int>* insertNodeTree(NodeTr<int>*, int);
template void bfsTraversal(NodeTr<int>*);