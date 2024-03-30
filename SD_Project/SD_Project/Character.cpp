#include "Character.h"

Character::Character(){}

Character::Character(const char& value, const int& n_occurences) {
	this->value = value;
	this->n_occurences = n_occurences;
}

char Character::getChar() const {
	return this->value;
}

int Character::getOccurences() const {
	return this->n_occurences;
}

void Character::addOccurences() {
	this->n_occurences++;
}

void Character::setOccurences(int nOcc) {
	this->n_occurences = nOcc;
}

bool Character::operator<(const Character& other) const {
	return n_occurences < other.n_occurences;
}

bool Character::operator>(const Character& other) const {
	return n_occurences > other.n_occurences;
}

bool Character::operator>(int other) const {
	return this->n_occurences > other;
}

bool Character::operator<=(const Character& other) {
	return n_occurences <= other.n_occurences;
}

bool Character::operator>=(const Character& other) {
	return n_occurences >= other.n_occurences;
}

//bool Character::operator==(const Character& other) {
//	return n_occurences == other.n_occurences;
//}
//
//bool Character::operator!=(const Character& other) {
//	return n_occurences != other.n_occurences;
//}

bool Character::operator==(const Character& other) {
	return value == other.value;
}

bool Character::operator!=(const Character& other) {
	return value != other.value;
}

std::ostream& operator<<(std::ostream& os, const Character& character) {
	os << "(" << character.value << " : " << character.n_occurences << ")";
	return os;
}