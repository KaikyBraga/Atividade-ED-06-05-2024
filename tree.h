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
template <typename T> void bfsTraversal(NodeTr<T>*);
// template <typename T> int treeHeight(NodeTr<T>*);

#endif