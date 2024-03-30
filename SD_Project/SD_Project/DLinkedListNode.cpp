#include "DLinkedListNode.h"

template<class T>
T DListNode<T>::getValue() {
	return this->value;
}

template class DListNode<Character>;