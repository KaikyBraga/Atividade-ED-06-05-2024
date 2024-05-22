#ifndef sortUtilsH
#define sortUtilsH

using std::string;

template <typename T> void bubbleSort(Node<T>**);
template <typename T> void optimizedBubbleSort(Node<T>**, int);
void bubbleSortTime(int, int, const string&);

template <typename T> void selectionSort(Node<T>**);
template <typename T> void optimizedSelectionSort(Node<T>**);
void selectionSortTime(int, int, const string&); 

template <typename T> void insertSort(Node<T>**);
void insertSortTime(int, int, const string&); 

template <typename T> void radixSort(Node<T>**, int);
void radixSortTime(int, int, const string&); 
void tutorialRadixSort();

#endif