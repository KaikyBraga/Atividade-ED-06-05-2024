#include <iostream>
#include <chrono>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::rand;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

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
void selectionSort(Node*);
void optimizedSelectionSort(Node*);
void addRandomElements(Node**, int, int);

int main()
{
    cout << "================================================================" << endl;
    Node* head1 = nullptr;
    cout << "Teste 1: Lista com 10 elementos:" << "\n" << endl;
    cout << "Lista antes do Selection Sort" << endl;
    insertFront(&head1, 10);
    insertFront(&head1, 2);
    insertFront(&head1, 5);
    insertFront(&head1, 6);
    insertFront(&head1, 9);
    insertFront(&head1, 1);
    insertFront(&head1, 53);
    insertFront(&head1, 2);
    insertFront(&head1, 13);
    insertFront(&head1, 24);
    displayList(head1);

    cout << endl;
    cout << "Lista depois do Selection Sort" << endl;
    selectionSort(head1);
    displayList(head1);

    cout << "================================================================" << endl;
    Node* head2 = nullptr;
    cout << "Teste 2: Lista com 10 elementos:" << "\n" << endl;
    cout << "Lista antes do Selection Sort Otimizado" << endl;
    insertFront(&head2, 10);
    insertFront(&head2, 2);
    insertFront(&head2, 5);
    insertFront(&head2, 6);
    insertFront(&head2, 9);
    insertFront(&head2, 1);
    insertFront(&head2, 53);
    insertFront(&head2, 2);
    insertFront(&head2, 13);
    insertFront(&head2, 24);
    displayList(head2);

    cout << endl;
    cout << "Lista depois do Selection Sort Otimizado" << endl;
    optimizedSelectionSort(head2);
    displayList(head2);

    cout << "================================================================" << endl;
    Node* head3 = nullptr;
    Node* head4 = nullptr;
    cout << "Teste 3: Lista com 10000 elementos com carga Payload de 0 ate 100:" << "\n" << endl;
    addRandomElements(&head3, 10000, 100);
    //displayList(head3); // Não é dado o display pela quantidade de elementos existentes
    auto timeStart = high_resolution_clock::now();
    selectionSort(head3);
    auto timeStop = high_resolution_clock::now();

    auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << "Tempo de execucao com o Selection Sort: " << timeDuration.count() << " nanosegundos." << endl;

    cout << "================================================================" << endl;
    cout << "Teste 4: Lista com 10000 elementos com carga Payload de 0 ate 100:" << "\n" << endl;
    addRandomElements(&head4, 10000, 100);
    //displayList(head4);  // Não é dado o display pela quantidade de elementos existentes
    timeStart = high_resolution_clock::now();
    optimizedSelectionSort(head4);
    timeStop = high_resolution_clock::now();

    timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << "Tempo de execucao com o Selection Sort otimizado: " << timeDuration.count() << " nanosegundos." << endl;
    cout << "================================================================" << endl;


    return 0;
}

Node* createNode(int iPayload)
{
    // Essa função cria um novo nó

    // Alocando memória para um nó
    Node* temp = (Node*) malloc(sizeof(Node));
    
    // Carga do nó
    temp -> iPayload = iPayload;
    
    // Inicializando nó apontando para nulo (Sem nós na frente e na traseira)
    temp -> ptrNext = nullptr;
    temp -> ptrPrev = nullptr;
    
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
    if  (node -> ptrPrev != nullptr)
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
        cout << temp -> iPayload<< " ";
        temp = temp -> ptrNext;
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

void selectionSort(Node* head)
{
    /*Essa função realiza a ordenação de uma lista duplamente encadeada 
    por meio do método Selection Sort*/

    // Inicializando nós para percorrerem a lista
    Node* OuterNode = head;
    Node* InnerNode = head;

    // Realizando verificação para todos os nós
    while(OuterNode != nullptr)
    {
        // O nó de troca recebe o nó posterior ao de fora
        InnerNode = OuterNode->ptrNext;

        // O nó de dentro percorre até o último elemento da lista
        while (InnerNode != nullptr)
        {
            // Condição de Troca
            if (OuterNode->iPayload > InnerNode->iPayload)
            {
                swapValue(OuterNode, InnerNode);
            }

            InnerNode = InnerNode->ptrNext;
        }

        OuterNode = OuterNode->ptrNext;
    }
}


void optimizedSelectionSort(Node* head)
{
    /*Essa função realiza a ordenação de uma lista duplamente encadeada 
    por meio do método Selection Sort de maneira otimizada.*/

    int minValue = 0;

    // Inicializando nós para percorrerem a lista
    Node* OuterNode = head;
    Node* InnerNode = head;
    Node* SwapNode = head;

    // Realizando verificação para todos os nós
    while(OuterNode != nullptr)
    {
        // O nó de dentro recebe o nó posterior ao de fora
        InnerNode = OuterNode->ptrNext;

        // O nó de troca recebe o nó de fora
        SwapNode = OuterNode;

        // O valor mínimo é inicialiazado com valor do nó de fora
        minValue = OuterNode->iPayload;

        // Verificação para todos nós posteriores ao de fora
        while (InnerNode != nullptr)
        {
            // Condição de Troca
            if (minValue > InnerNode->iPayload)
            {
                minValue = InnerNode->iPayload;
                SwapNode = InnerNode;
            }

            InnerNode = InnerNode->ptrNext;
        }

        // Troca de valores entre os nós
        swapValue(OuterNode, SwapNode); 

        OuterNode = OuterNode->ptrNext;
    }
}

void addRandomElements(Node** head, int iQuantElements, int iMaxValue)
{
    // Essa função adiciona elementos aleatórios em uma Lista duplamente encadeada.
    // É possível passar o Valor máximo da carga Payload.

    for (int i=0; i < iQuantElements; i++)
        insertEnd(head, (rand() % iMaxValue) + 1);
}