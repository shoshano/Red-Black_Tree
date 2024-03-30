#include "RB_Tree.h"
#include "Node.h"
#include <iostream>

template<class T>
RB_Tree<T>::RB_Tree() {
	root = nullptr;
	for (int i = 0; i < 256; i++) {
		occurence_times[i] = 0;
	}
}

template<class T>
RB_Tree<T>::~RB_Tree() {}

template<class T>
Node<T>* RB_Tree<T>::getRoot() {
	return root;
}

//template<class T>
//void RB_Tree<T>::print(Node<T>* node) {
//	// prosta wersja algorytmu inorder tree traversal
//	if (node != nullptr) {						// jesli node nie jest nullptr
//		print(node->getLeft());					// wywolaj print() dla jego lewego poddrzewa
//		std::cout << node->getValue() << " ";   // po tym, jak wypisze lewe poddrzewo wypisz node
//		print(node->getRight());				// wywolaw print() dla prawego poddrzewa
//	}
//}

template<class T>
void RB_Tree<T>::printInner(Node<T>* node) {
	// print dla testowania dzialania drzewa
	if (node != nullptr) {					
		printInner(node->getLeft());					
		std::cout << "(" << node->getValue() << ", " << node->getColor() << ") ";   
		printInner(node->getRight());				
	}
}

template<class T>
void RB_Tree<T>::print(Node<T>* node) {
	printInner(node);
	std::cout << std::endl;
}

template<class T>
void RB_Tree<T>::insert(const T& value){
	occurence_times[int(value.getChar())] += value.getOccurences();
	Node<T>* node = new Node<T>();			//tworzy nowy node
	node->setValue(value);					// nadaje mu wartosc 
	Node<T>* y = nullptr;						// node pomocniczy
	Node<T>* x = root;						// wskaznik na root
	while (!(x == nullptr)) {						// dopuki x jest jest lisciem
		y = x;
		if (node->getValue() < x->getValue()) {	// jesli wartoœc dodawanego noda jest mniejsza to ptrzesun w lewo
			x = x->getLeft();
		}
		else {									 // jesli wartoœc dodawanego noda jest wieksza to ptrzesun w prawo
			x = x->getRight();
		}
	}
	node->setParent(y);					// ustaw y jako rodzica
	if (y == nullptr) {								// jesli y == 0 to nowy node jest korzeniem
		root = node;
	}
	else if (node->getValue() < y->getValue()) {	// jesli wartoœc dodawanego noda jest mniejsza od rodzica to jest lewym synam	
		y->setLeft(node);
	}
	else {											// jesli wartoœc dodawanego noda jest wieksza od rodzica to jest prawym synam
		y->setRight(node);
	}
	node->setColor(1);				// ustaw kolor dodanego noda na czerwony

	fixAfterInsert(node);
}

template<class T>
void RB_Tree<T>::insert(char char_value, int nOccur) {
	occurence_times[char_value] += nOccur;
	Node<T>* node = new Node<T>();			//tworzy nowy node
	node->setValue(Character(char_value, occurence_times[char_value]));					// nadaje mu wartosc 
	Node<T>* y = nullptr;						// node pomocniczy
	Node<T>* x = root;						// wskaznik na root
	while (!(x == nullptr)) {						// dopuki x jest jest lisciem
		y = x;
		if (node->getValue() < x->getValue()) {	// jesli wartoœc dodawanego noda jest mniejsza to ptrzesun w lewo
			x = x->getLeft();
		}
		else {									 // jesli wartoœc dodawanego noda jest wieksza to ptrzesun w prawo
			x = x->getRight();
		}
	}
	node->setParent(y);					// ustaw y jako rodzica
	if (y == nullptr) {								// jesli y == 0 to nowy node jest korzeniem
		root = node;
	}
	else if (node->getValue() < y->getValue()) {	// jesli wartoœc dodawanego noda jest mniejsza od rodzica to jest lewym synam	
		y->setLeft(node);
	}
	else {											// jesli wartoœc dodawanego noda jest wieksza od rodzica to jest prawym synam
		y->setRight(node);
	}
	node->setColor(1);				// ustaw kolor dodanego noda na czerwony

	fixAfterInsert(node);
}


template<class T>
void RB_Tree<T>::transplant(Node<T>* first, Node<T>* second) {
	// Funkcja wstawia node second zamiast noda first
	if (first->getParent() == nullptr) {                 // jesli zamieniany node jest rootem
		this->root = second;							 // ustaw second jako nowy root
	}		
	else if (first == first->getParent()->getLeft()) {	 // jesli zamieniany node jest lewym synem swojego rodzica
		first->getParent()->setLeft(second);             
	}
	else {												 // jesli zamieniany node jest prawym synem swojego rodzica		
		first->getParent()->setRight(second);
	}
	if (second != nullptr) {
		second->setParent(first->getParent());
	}
}

template<class T>
void RB_Tree<T>::remove(Node<T>* node) {
	Node<T>* y = node;								// node ktory zastapi 'node' po usunieciu
	Node<T>* x = new Node<T>();                     // node pomocniczy; zawiera syna noda 'y' (z definicji moze byc max. 1 syn)
	bool y_orig_color = y->getColor();				// kolor noda 'y' przed operacja 'remove'; jesli 0 - musimy zrobic fix; jesli 1 - nie musimy robic fixa;
	if (node->getLeft() == nullptr) {				// jesli 'node' nie ma lewego syna
		if (node->getRight() != nullptr) {			// jesli prawy syn nie jest nullptr
			x = node->getRight();					
		}							
		x->setParent(node->getParent());            // ustaw rodzica 'node' jako rodzica x
		transplant(node, node->getRight());		    // zamien noda 'node' jego prawym synem
	}
	else if (node->getRight() == nullptr) {			// jesli 'node' nie ma prawego syna
		if (node->getLeft() != nullptr) {			// jesli lewy syn nie jest nullptr
			x = node->getLeft();
		}											// ustaw 'node' jako rodzica x
		x->setParent(node->getParent());
		transplant(node, node->getLeft());			// zamien noda 'node' jego lewym synem
	}
	else {
		y = minimum(node->getRight());				// znajdz nastepce noda 'node' w prawym poddrzewie
		y_orig_color = y->getColor();				// zapisz kolor noda 'y'
		if (y->getRight() != nullptr) {				// jesli prawy syn nie jest nullptr
			x = y->getRight();
		}
		x->setParent(y);							// ustaw 'y' jako rodzica x
		if (y != node->getRight()) {				// jesli 'y' jest prawym synem 'node'
			transplant(y, y->getRight());			// zamien noda 'y' jego prawym synem
			y->setRight(node->getRight());			// ustaw prawego syna 'node' jako prawego syna 'y'
			y->getRight()->setParent(y);			// ustaw 'y' jako rodzica prawego syna 'y'
		}
		transplant(node, y);						// zamien noda 'node' na 'y'
		y->setLeft(node->getLeft());				// ustaw lewego syna 'node' jako lewego syna 'y'
		y->getLeft()->setParent(y);					// ustaw 'y' jako rodzica lewego syna 'y'
		y->setColor(node->getColor());				// zmien kolor 'y' na kolor 'node'
	}
	if (y_orig_color == 0) {						// jesli oryginalny kolor 'y' byl 0 (czarny) 
		fixAfterRemove(x);							
	}
}

template<class T>
void RB_Tree<T>::fixAfterRemove(Node<T>* node) {
	Node<T>* sibling = nullptr;										// pomocniczy node. zawiera 'brata' noda 'node'
	while ( (node != this->root) && ((node == nullptr) || (node->getColor() == 0))) {		// dopóki 'node' nie jest rootem i nie jest czarnego koloru
//===================JESLI JEST LEWYM SYNEM========================
		if ((node == node->getParent()->getLeft()) || (node->getParent()->getLeft() == nullptr)){				
			sibling = node->getParent()->getRight();				// ustaw brata jako prawego syna rodzica 'node'
			if (sibling->getColor() == 1)							// jesli kolor brata jest czerwony
			{
				sibling->setColor(0);								// zmien kolor brata na czarny
				node->getParent()->setColor(1);						// zmien kolor rodzica 'node' na czerwony
				leftRotation(node->getParent());					// zrob lewy obrot dookola rodzica 'node'
				sibling = node->getParent()->getRight();			
			}
			if (((sibling->getRight() == nullptr) || (sibling->getRight()->getColor() == 0)) && // jesli lewy syn brata jest czarny (AND)
				((sibling->getLeft() == nullptr) || (sibling->getLeft()->getColor() == 0)))			// prawy syn brata jest czarny
			{
				sibling->setColor(1);								// zmien kolor brata na czerwony
				node = node->getParent();							// przesun wskaznik 'node' na 1 poziom wyzej
			}
			else {
				if (sibling->getRight() == nullptr || sibling->getRight()->getColor() == 0) {			// jesli prawy syn brata jest czarny
					sibling->getLeft()->setColor(0);				// zmien kolor lewego syna brata na czarny
					sibling->setColor(1);							// zmien kolor brata na czerwony
					rightRotation(sibling);							// zrob prawy obrot dookola brata
					sibling = node->getParent()->getRight();		
				}
				sibling->setColor(node->getParent()->getColor());	// zmien kolor brata na kolor rodzica 'node'
				node->getParent()->setColor(0);						// zmien kolor rodzica 'node' na czarny
				sibling->getRight()->setColor(0);					// zmien kolor prawego syna 'sibling' na czarny
				leftRotation(node->getParent());					// zrob lewy obrot dookola rodzica 'node'
				node = this->root;									// ustaw 'node' jako root drzewa
			}
		} 
//===================JESLI JEST PRAWYM SYNEM========================
// ROZWIAZANIE SYMETRYCZNE JAK DLA LEWEGO SYNA. ZAMIENIAMY 'left' na 'right' i 'right' na 'left'
		else {
			sibling = node->getParent()->getLeft();
			if (sibling->getColor() == 1) {
				sibling->setColor(0);
				node->getParent()->setColor(1);
				rightRotation(node->getParent());
				sibling = node->getParent()->getLeft();
			}
			if (((sibling->getRight() == nullptr) || (sibling->getRight()->getColor() == 0)) &&
				((sibling->getLeft() == nullptr) || (sibling->getLeft()->getColor() == 0))) {
				sibling->setColor(1);
				node = node->getParent();
			}
			else {
				if (sibling->getLeft()->getColor() == 0) {
					sibling->getRight()->setColor(0);
					sibling->setColor(1);
					leftRotation(sibling);
					sibling = node->getParent()->getLeft();
				}
				sibling->setColor(node->getParent()->getColor());
				node->getParent()->setColor(0);
				sibling->getLeft()->setColor(0);
				rightRotation(node->getParent());
				node = this->root;
			}
		}
	}
	node->setColor(0);


}

template<class T>
void RB_Tree<T>::leftRotation(Node<T>* x) {
	Node<T>* y = x->getRight();						// inicjuje nowy wezel
	x->setRight(y->getLeft());					// ustawia lewe poddrzewo y jako prawe poddrzewo x
	if (y->getLeft() != nullptr) {					// jesli istnieje lewe poddrzewo y to jego rodzicem staje sie x
		y->getLeft()->setParent(x);
	}
	y->setParent(x->getParent());					// ustawiamy rodzica x jako rodzica y
	if (x->getParent() == nullptr) {				// jesli x byl rootem to teraz y jest rootem
		root = y;
	}
	else if (x->getParent()->getLeft() == x) {		// jesli byl x lewym potomkiem to y jest lewym potomkiem
		x->getParent()->setLeft(y);
	}
	else{											// jesli byl x prawym potomkiem to y jest prawym potomnkiem
		x->getParent()->setRight(y);
	}
	y->setLeft(x);								// lewym potomkiem y staje sie x
	x->setParent(y);							// rodzicem x staje sie y
}

template<class T>
void RB_Tree<T>::rightRotation(Node<T>* x) {
	Node<T>* y = x->getLeft();						// inicjuje nowy wezel
	x->setLeft(y->getRight());					// ustawia prawe poddrzewo y jako lewe poddrzewo x
	if (y->getRight() != nullptr) {					// jesli istnieje prawe poddrzewo y to jego rodzicem staje sie x
		y->getRight()->setParent(x);
	}
	y->setParent(x->getParent());					// ustawiamy rodzica x jako rodzica y
	if (x->getParent() == nullptr) {				// jesli x byl rootem to teraz y jest rootem
		root = y;
	}
	else if (x->getParent()->getLeft() == x) {		// jesli byl x lewym potomkiem to y jest lewym potomkiem
		x->getParent()->setLeft(y);
	}
	else {											// jesli byl x prawym potomkiem to y jest prawym potomnkiem
		x->getParent()->setRight(y);
	}
	y->setRight(x);							// prawym potomkiem y staje sie x
	x->setParent(y);							// rodzicem x staje sie y

}

template<class T>
void RB_Tree<T>::fixAfterInsert(Node<T>* node) {

	while ((root != node) && (node->getParent()->getColor() == 1)) {			//pêtla jesli rodzic jest czerwony to wykonaj
		Node<T>* y = nullptr;		//node pomoczniczy
//==============JESLI JEST LEWYM SYNEM=======================
		if (node->getParent() == node->getParent()->getParent()->getLeft()) {		// jesli node jest lewym synem 
			y = node->getParent()->getParent()->getRight();							// ustawiamy y jako stryja
			if (y != nullptr && y->getColor() == 1) {												// stryj jest czerwony
				node->getParent()->setColor(0);								// ustawia ojca na czarno
				y->setColor(0);												// ustawia stryja na czarano
				node->getParent()->getParent()->setColor(1);					// ustawia dziadka na czerwono
				node = node->getParent()->getParent();								// zmienia wskaznik aktualne wezla odniesienia na dziadka
			}
			else {
				if (node == node->getParent()->getRight()) {						// jesli node jest prawym synem  
					node = node->getParent();							// przypisz aktualny node rodzicowi
					leftRotation(node);								// wykonaj lewa rotacje
				}
				node->getParent()->setColor(0);								// rodzic ma kolor czarny
				node->getParent()->getParent()->setColor(1);						// dziadek ma czerwony
				rightRotation(node->getParent()->getParent());						// rotuje w prawo
			}
		}
//==============JESLI JEST PRAWYM SYNEM=======================
		else if (node->getParent() == node->getParent()->getParent()->getRight()) {	// jesli node jest prawym synem 
			y = node->getParent()->getParent()->getLeft();							// ustawiamy y jako stryja
			if (y != nullptr && y->getColor() == 1) {												// streyj jest czerwony
				node->getParent()->setColor(0);								// ustawia ojca na czarno
				y->setColor(0);												// ustawia stryja na czarano
				node->getParent()->getParent()->setColor(1);					// ustawia dzidka na czerwono
				node = node->getParent()->getParent();								// zmienia wskaznik aktualne wezla odniesienia na dziadka
			}
			else {
				if (node == node->getParent()->getLeft()) {					// jesli node jest lewym synem  
					node = node->getParent();						// przypisz aktualny node rodzicowi
					rightRotation(node);							// wykonaj prawa rotacje
				}
				node->getParent()->setColor(0);							// rodzic ma kolor czarny
				node->getParent()->getParent()->setColor(1);					// dziadek ma czerwony
				leftRotation(node->getParent()->getParent());					// rotuje w lewo
			}
		}
	}                                                                                                                                                                                                      
	root->setColor(0);	//root musi byc czarny
}


template<class T>
Node<T>* RB_Tree<T>::search(T& key)  {
	key.setOccurences(occurence_times[key.getChar()]);
	std::cout << key << std::endl;
	Node<T>* y = root;
	while (y != nullptr) {
		if (y->getValue() == key) {
			return y;
		}
		else if (y->getValue() > key) {
			y = y->getLeft();
		}
		else {
			y = y->getRight();
		}
	}
	return nullptr;
}

template<class T>
Node<T>* RB_Tree<T>::search(char value) {
	int nOcc = occurence_times[value];
	Node<T>* y = root;
	while (y != nullptr) {
		if (y->getValue() == value) {
			return y;
		}
		else if (y->getValue() > nOcc) {
			y = y->getLeft();
		}
		else {
			y = y->getRight();
		}
	}
	return nullptr;
}

template<class T>
Node<T>* RB_Tree<T>::minimum(Node<T>* node) {
	Node<T>* y = node;
	while (y->getLeft() != nullptr) {
		y = y->getLeft();
	}
	return y;
}

template<class T>
Node<T>* RB_Tree<T>::maximum(Node<T>* node) {
	Node<T>* y = node;
	while (y->getRight() != nullptr) {
		y = y->getRight();
	}
	return y;
}

template class RB_Tree<Character>;