#include <iostream>
#include <chrono>
#include <fstream>

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

typedef struct Node
{
    int iPayload;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

Node* createNode(int);
void insertFront(Node**, int);
void insertEnd(Node**, int);
void deleteNode(Node**, Node*);
void displayList(Node*);
void swapValue(Node*, Node*);
void addRandomElements(Node**, int, int);
Node* copyList(Node**);
void bubbleSort(Node**);
void optimizedBubbleSort(Node**, int);
void clearList(Node**);

int main() 
{
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
    
    return 0;
}

Node* createNode(int iPayload)
{
    // Essa função cria um novo nó

    // Alocando memória para um nó
    Node* temp = (Node*) malloc(sizeof(Node));
    
    // Carga do nó
    temp->iPayload = iPayload;
    
    // Inicializando nó apontando para nulo (Sem nós na frente e na traseira)
    temp->ptrNext = nullptr;
    temp->ptrPrev = nullptr;
    
    return temp;
}

void displayList(Node* node)
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
    Node* temp = node;
     
    cout << "Payload: ";
    
    // Print de todos os elementos da lista
    while(temp != nullptr)
    {
        cout << temp->iPayload<< " ";
        temp = temp->ptrNext;
    }
    
    cout << endl;
}

void insertFront(Node** head, int iPayload)
{
    // Essa função insere um nó no início de uma lista duplamente encadeada

    Node* newNode = createNode(iPayload);
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

void insertEnd(Node** head, int iPayload)
{
    // Essa função inserre um novo nó no final da lista

    Node* newNode = createNode(iPayload);   
    //newNode->ptrNext = nullptr;

    // Caso a lista seja nula, inserimos um novo nó no final passado
    if (*head == nullptr)
    {
        //newNode->ptrPrev = nullptr;
        (*head) = newNode;
        return;
    }

    // Caso a lista não seja nula
    Node* temp = (*head);

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

void deleteNode(Node** head, Node* ptrDelete)
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

void swapValue(Node* node1, Node* node2)
{
    // Essa função troca os valores dos nós passados.

    int iTemp = node1->iPayload;
    node1->iPayload = node2->iPayload;
    node2->iPayload = iTemp;
}

void addRandomElements(Node** head, int iQuantElements, int iMaxValue)
{
    // Essa função adiciona elementos aleatórios em uma Lista duplamente encadeada.
    // É possível passar o Valor máximo da carga Payload.

    for (int i=0; i < iQuantElements; i++)
        insertEnd(head, (rand() % iMaxValue) + 1);
}

Node* copyList(Node** head)
{
    // Essa função copia uma lista duplamente encadeada

    Node* ptrCurrent = *head;
    Node* newHead = createNode(ptrCurrent->iPayload);

    while (ptrCurrent != nullptr)
    {
        insertEnd(&newHead, ptrCurrent->iPayload);
        ptrCurrent = ptrCurrent->ptrNext;
    }
    
    return newHead;
}

void bubbleSort(Node** head)
{
    /*Essa função realiza a ordenação de uma lista duplamente encadeada 
    por meio do método Bubble Sort*/

    Node* ptrOuterNode = *head;
    Node* ptrInnerNode = *head;

    if (ptrOuterNode == nullptr || ptrOuterNode->ptrNext == nullptr) return;
    
    while (ptrOuterNode != nullptr)
    {
        ptrInnerNode = *head;

        while (ptrInnerNode->ptrNext != nullptr)
        {
            if (ptrInnerNode->iPayload > ptrInnerNode->ptrNext->iPayload)
                swapValue(ptrInnerNode, ptrInnerNode->ptrNext);

            ptrInnerNode = ptrInnerNode->ptrNext;
        }
        ptrOuterNode = ptrOuterNode->ptrNext;
    }
}

void optimizedBubbleSort(Node** head, int iLength)
{
    /*Essa função realiza a ordenação de uma lista duplamente encadeada 
    por meio do método Selection Sort de maneira otimizada.*/

    Node* ptrCurrent = *head;

    if (ptrCurrent == nullptr || ptrCurrent->ptrNext == nullptr) return;
    
    bool bUnordered = false;
    int i = 0;
    for (int iOuterLoop = 0; iOuterLoop < iLength - 1; iOuterLoop++)
    {
        bUnordered = false;

        for (int iInnerLoop = 0; iInnerLoop < (iLength - 1) - iOuterLoop; iInnerLoop++)
        {
            if (ptrCurrent->iPayload > ptrCurrent->ptrNext->iPayload)
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

void clearList(Node** head)
{
    // Essa função esvazia uma lista duplamente encadeada

    Node* ptrCurrent = *head;

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