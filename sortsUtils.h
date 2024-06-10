#ifndef sortUtilsH
#define sortUtilsH

template <typename T> void bubbleSort(Node<T>**);
template <typename T> void optimizedBubbleSort(Node<T>**, int);

template <typename T> void selectionSort(Node<T>**);
template <typename T> void optimizedSelectionSort(Node<T>**);

template <typename T> void insertSort(Node<T>**);

template <typename T> void radixSort(Node<T>**);
void tutorialRadixSort();

#endif