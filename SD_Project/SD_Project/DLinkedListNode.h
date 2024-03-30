#ifndef DLINKEDLISTNODE_H
#define DLINKEDLISTNODE_H
#include "Character.h"

template<typename T>
class DListNode {
private:
    T value;
    DListNode<T>* next;
    DListNode<T>* prev;
    template<typename U>
    friend class DLinkedList;
public:
    T getValue();
};

#endif