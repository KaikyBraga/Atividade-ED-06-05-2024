#ifndef listH
#define listH

template <typename T> 
struct Node
{
    T payload;
    Node* ptrNext;
    Node* ptrPrev;
};

template <typename T> Node<T>* createNode(T);
template <typename T> void insertFront(Node<T>**, T);
template <typename T> void insertEnd(Node<T>**, T);
template <typename T> void deleteNode(Node<T>**, Node<T>*);
template <typename T> void displayList(Node<T>*);
template <typename T> void swapValue(Node<T>*, Node<T>*);
void addRandomElements(Node<int>**, int, int);
template <typename T> Node<T>* copyList(Node<T>**);
template <typename T> void clearList(Node<T>**);
template <typename T> T maxList(Node<T>*);
template <typename T> Node<T>* searchNodebyValue(Node<T>**, T);

#endif