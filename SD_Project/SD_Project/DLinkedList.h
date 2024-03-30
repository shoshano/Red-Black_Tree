#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H
#include "DLinkedListNode.h"
#include "Character.h"

template<typename T>
class DLinkedList {
private:
    DListNode<T>* head;
    DListNode<T>* tail;
public:
    DLinkedList();
    ~DLinkedList();
    bool isEmpty() const;
    const T& front() const;
    const T& back() const;
    void addFront(const T& value);
    void addBack(const T& value);
    void addFront(char char_value, int nOccur);
    void addBack(char char_value, int nOccur);
    void print() const;
    void removeFront();
    void removeBack();
    //IMPLEMENT SEARCH FUNCTION
    DListNode<T>* search(const char& value) const;
protected:
    void add(DListNode<T>* v, const T& value);
    void remove(DListNode<T>* v);
};

#endif