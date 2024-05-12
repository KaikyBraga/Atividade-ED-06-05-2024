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
void addRandomElements(Node**, int, int);
void insertSort(Node**);
void clearList(Node**);

int main() {
    int iNumLinhas = 100;

    Node* testHead = nullptr;

    addRandomElements(&testHead, 1, 100);  

    // displayList(testHead); 

    clearList(&testHead);

    displayList(testHead);

    // Inicialização da semente do gerador de números aleatórios com o tempo atual
    srand(time(nullptr)); 
    ofstream outputFile("insertSort_time.csv", ios::out | ios::trunc);
    
    outputFile << "Quantidade de Elementos,Tempo (nanossegundos)" << endl;

    Node* head = nullptr;

    for (int i = 1; i <= iNumLinhas ; i ++) 
    {
        addRandomElements(&head, 1000, i);

        auto timeStart = high_resolution_clock::now();
        insertSort(&head);
        auto timeStop = high_resolution_clock::now();

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);

        outputFile << 1000 * i << "," << timeDuration.count() << endl;
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

void addRandomElements(Node** head, int iQuantElements, int iMaxValue)
{
    // Essa função adiciona elementos aleatórios em uma Lista duplamente encadeada.
    // É possível passar o Valor máximo da carga Payload.

    for (int i=0; i < iQuantElements; i++)
        insertEnd(head, (rand() % iMaxValue) + 1);
}

void insertSort(Node** head)
{
    /*
    Esta função implementa o método de ordenação de uma lista duplamente encadeada
    por meio do método de Insertion Sort.
    */

    // Caso a lista não tenha elementos ou tiver apenas um nó
    if (head == nullptr || (*head)->ptrNext == nullptr)
        return; 

    Node* ptrOuterNode = (*head)->ptrNext; 
    Node* ptrInnerNode = nullptr;
    int iInsertValue = 0;

    // Loop Externo (Começa sempre no segundo nó)
    while (ptrOuterNode != nullptr)
    {
        // Valor de troca
        iInsertValue = ptrOuterNode->iPayload;

        // Loop Interno (Começa sempre do nó anterior do Loop Externo)
        ptrInnerNode = ptrOuterNode->ptrPrev;
        while (ptrInnerNode != nullptr && iInsertValue < ptrInnerNode->iPayload)
        {
            // Caso o valor do nó seja maior que o do valor de troca,
            // então o valor do sucessor desse nó é alterado para o valor desse nó
            ptrInnerNode->ptrNext->iPayload = ptrInnerNode->iPayload;

            // Pegando o nó anterior no Loop Interno
            ptrInnerNode = ptrInnerNode->ptrPrev;
        }

        // Caso o Loop Interno percorra todos os nós anteriores ao Loop Externo
        if (ptrInnerNode == nullptr) 
        {
            (*head)->iPayload = iInsertValue;
        } 

        else 
        {
            ptrInnerNode->ptrNext->iPayload = iInsertValue;
        }

        // Preparando o Loop Externo para a próxima iteração
        ptrOuterNode = ptrOuterNode->ptrNext;
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