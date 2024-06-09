#ifndef treeH
#define treeH

template <typename T> 
struct NodeTr
{
    T payload;
    NodeTr* ptrLeft;
    NodeTr* ptrRight;
};

template <typename T> NodeTr<T>* createNodeTree(T);
template <typename T> NodeTr<T>* insertNodeTree(NodeTr<T>*, T);
template <typename T> NodeTr<int>* lesserLeaf(NodeTr<T>*);
template <typename T> NodeTr<int>* deleteNodeTree(NodeTr<T>*, T);
template <typename T> void deleteTree(NodeTr<T>*);
template <typename T> void bfsTraversal(NodeTr<T>*);
template <typename T> NodeTr<T>* bfSearch(NodeTr<T>*, T);
template <typename T> NodeTr<T>* searchNode(NodeTr<T>*, T);
template <typename T> NodeTr<T>* dfSearchPreOrder(NodeTr<T>*, T);
template <typename T> NodeTr<T>* dfSearchInOrder(NodeTr<T>*, T);
template <typename T> NodeTr<T>* dfSearchPostOrder(NodeTr<T>*, T);
void treeTime(int, int, const string&); 

#endif