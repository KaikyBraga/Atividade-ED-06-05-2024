#include <iostream>
#include "list.h"

using namespace std;

template <typename T>
Node<T>* createNode(T payload)
{
    // Essa função cria um novo nó

    // Alocando memória para um nó
    Node<T>* temp = (Node<T>*) malloc(sizeof(Node<T>));
    
    // Carga do nó
    temp->payload = payload;
    
    // Inicializando nó apontando para nulo (Sem nós na frente e na traseira)
    temp->ptrNext = nullptr;
    temp->ptrPrev = nullptr;
    
    return temp;
}

template <typename T> 
void displayList(Node<T>* node)
{
    // Essa função printa a lista duplamente encadeada

    // Caso não existam nós na lista
    if (node == nullptr)
    {
        cout << "Lista vazia: Não é possível realizar displayList" << endl;
        return; 
    }
    
    // Caso o nó passado estiver no meio o no final da lista
    if  (node->ptrPrev != nullptr)
    {
        cout << "Meio ou Fim da Lista: Não é possível realizar displayList" << endl;
        return;
    }
    
    // Caso o nó passado seja o primeiro elemento da lista
    Node<T>* temp = node;
     
    cout << "Payload: ";
    
    // Print de todos os elementos da lista
    while(temp != nullptr)
    {
        cout << temp->payload<< " ";
        temp = temp->ptrNext;
    }
    
    cout << endl;
}

template <typename T>
void insertFront(Node<T>** head, T payload)
{
    // Essa função insere um nó no início de uma lista duplamente encadeada

    Node<T>* newNode = createNode(payload);
    // newNode->ptrPrev = nullptr; (Cuidado Dobrado, não é necessário nesse caso)
    
    // Caso exista pelo menos um nó na lista
    if (*head != nullptr)
    {
        (*head)->ptrPrev = newNode;
        newNode->ptrNext = (*head);
        (*head) = newNode;
        
        return;
    }
    
    // Caso não existam nós na lista
    (*head) = newNode;
}

template <typename T> 
void insertEnd(Node<T>** head, int payload)
{
    // Essa função inserre um novo nó no final da lista

    Node<T>* newNode = createNode(payload);   
    //newNode->ptrNext = nullptr;

    // Caso a lista seja nula, inserimos um novo nó no final passado
    if (*head == nullptr)
    {
        //newNode->ptrPrev = nullptr;
        (*head) = newNode;
        return;
    }

    // Caso a lista não seja nula
    Node<T>* temp = (*head);

    // Percorremos a lista até seu fim (ptrNext do último nó é nulo)
    while(temp->ptrNext != nullptr)
    {
        temp = temp->ptrNext;
    }

    // Temos agora o último nó da lista

    // newNode aponta para o fim da Lista
    newNode->ptrPrev = temp;

    // Antigo elemento aponta para o novo nó
    temp->ptrNext = newNode; 
}

template <typename T>
void deleteNode(Node<T>** head, Node<T>* ptrDelete)
{
    // Essa função deleta um nó específico da lista

    // Caso a lista seja nulo ou o nó seja nulo
    if (*head == nullptr || ptrDelete == nullptr)   
    {
        cout << "Não foi possível remover." << endl;
        return;
    }
    
    // Caso o ptrDelete seja o primeiro elemento da lista
    if (*head == ptrDelete) 
        (*head) = ptrDelete->ptrNext;
    
    // Se o ptrDelete não é o último nó
    if (ptrDelete->ptrNext != nullptr) 
        ptrDelete->ptrNext->ptrPrev = ptrDelete->ptrPrev; 
    
    // Se o ptrDelete não é o primeiro nó
    if (ptrDelete->ptrPrev != nullptr)
        ptrDelete->ptrPrev->ptrNext = ptrDelete->ptrNext;
    
    free(ptrDelete);
}

template <typename T>
void swapValue(Node<T>* node1, Node<T>* node2)
{
    // Essa função troca os valores dos nós passados.

    T temp = node1->payload;
    node1->payload = node2->payload;
    node2->payload = temp;
}

void addRandomElements(Node<int>** head, int iQuantElements, int iMaxValue)
{
    // Essa função adiciona elementos aleatórios em uma Lista duplamente encadeada.
    // É possível passar o Valor máximo da carga Payload.

    for (int i=0; i < iQuantElements; i++)
        insertEnd(head, (rand() % iMaxValue) + 1);
}

template <typename T>
Node<T>* copyList(Node<T>** head)
{
    // Essa função copia uma lista duplamente encadeada

    Node<T>* ptrCurrent = *head;
    Node<T>* newHead = createNode(ptrCurrent->payload);

    while (ptrCurrent != nullptr)
    {
        insertEnd(&newHead, ptrCurrent->payload);
        ptrCurrent = ptrCurrent->ptrNext;
    }
    
    return newHead;
}

template <typename T>
void clearList(Node<T>** head)
{
    // Essa função esvazia uma lista duplamente encadeada

    Node<T>* ptrCurrent = *head;

    // Confere se já está vazia
    if (ptrCurrent == nullptr) return;

    // Percorre a lista até o último elemento
    while (ptrCurrent->ptrNext != nullptr) ptrCurrent = ptrCurrent->ptrNext;
    
    // Faz o caminho contrário e deleta o último nó a cada iteração
    while (ptrCurrent != *head)
    {
        ptrCurrent = ptrCurrent->ptrPrev;

        deleteNode(head, ptrCurrent->ptrNext);
    }
    // Por fim, deleta o primeiro nó
    deleteNode(head, ptrCurrent);
}

template <typename T>
T maxList(Node<T>* head)
{
    /*
    Essa função calcula o valor máximo de uma lista.
    */

    int iMaxValue = head->payload;
    Node<T>* current = head;

    while (current != nullptr)
    {
        if (current->payload > iMaxValue)
        {
            iMaxValue = current->payload;
        }

        current = current->ptrNext;
    }

    return iMaxValue;
};