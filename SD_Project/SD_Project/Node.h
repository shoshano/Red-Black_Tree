#ifndef NODE_H_
#define NODE_H_
#include "Character.h"

template< class T>
class Node {
	T value;						//wartosc w nodzie

	Node* parent;					// node rodzic
	Node* left;						// lewy potomek
	Node* right;					// prawy potomek

	bool color;						// kolor 0 - czarny, 1 - czerwony

public:
	Node();							//konstruktor
	~Node();						//dekonstruktor

	//gettery
	T getValue();					//zwraca wartosc noda
	bool getColor();				//zwraca kolor noda
	Node* getParent();				//zwraca rodzica noda
	Node* getLeft();				//zwraca lewego potomka noda
	Node* getRight();				//zwraca prawego potomka noda

	//settery
	void setValue(T value);			//ustawia wartoœæ
	void setColor(bool color);		//ustawia kolor
	void setParent(Node* parent);	//ustwaiamy rodzica
	void setLeft(Node* left);		//ustawiamy lewego potomka
	void setRight(Node* right);		//ustawiamy prawego potomka
};


#endif 


