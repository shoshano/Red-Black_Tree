#ifndef RB_TREE_H_
#define RB_TREE_H_
#include "Node.h"
#include "Character.h"

template<class T>
class RB_Tree {
	Node<T>* root;								// korzen drzewa
	int occurence_times[256];
protected:
	void transplant(Node<T>* first, Node<T>* second);
	void printInner(Node<T>* node);
public:
	RB_Tree();									// konstruktor
	~RB_Tree();									// dekonstruktor
	Node<T>* getRoot();							// getter roota
	void insert(const T& value);				// dodaje 
	void insert(char char_value, int nOccur=1);				// dodaje 
	void remove(Node<T>* node);					// usuwa
	void leftRotation(Node<T>* x);				// rotuje w lewo
	void rightRotation(Node<T>* x);				// rotuje w prawo
	void fixAfterInsert(Node<T>* node);			// napiawia po dodaniu
	void fixAfterRemove(Node<T>* node);			// naprawia po usuwaniu
	Node<T>* search(T& key);				    // szuka
	Node<T>* search(char value);				// szuka
	Node<T>* minimum(Node<T>* node);			// znajduje minimum
	Node<T>* maximum(Node<T>* node);			// znajduje maximum
	void print(Node<T>* node);
};

#endif // !RB_TREE_H_


