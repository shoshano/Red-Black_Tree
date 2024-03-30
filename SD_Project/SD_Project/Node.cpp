#include "Node.h"

template<class T>
Node<T>::Node() {
	this->value = 0;
	this->color = 0;
	this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;

}

template<class T>
Node<T>::~Node() {}

template<class T>
void Node<T>::setValue(T value) {
	this->value = value;
}

template<class T>
void Node<T>::setColor(bool color) {
	this->color = color;
}


template<class T>
void Node<T>::setParent(Node<T> *parent) {
	this->parent = parent;
}

template<class T>
void Node<T>::setLeft(Node<T>* left) {
	this->left = left;
}

template<class T>
void Node<T>::setRight(Node<T>* right) {
	this->right = right;
}

template<class T>
T Node<T>::getValue() {
	return value;
}

template<class T>
bool Node<T>::getColor() {
	return color;
}

template<class T>
Node<T>* Node<T>::getParent() {
	return parent;
}
template<class T>
Node<T>* Node<T>::getLeft() {
	return left;
}

template<class T>
Node<T>* Node<T>::getRight() {
	return right;
}

//template class Node<int>;
template class Node<Character>;
