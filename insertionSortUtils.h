#ifndef insertionSortH
#define insertionSortH

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

#endif