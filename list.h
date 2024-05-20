#ifndef listH
#define listH

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
void clearList(Node**);

#endif