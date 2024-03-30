#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>

class Character {
private:
	char value;
	int n_occurences;
public:
	Character();
	Character(const char& value, const int& n_occurences=1);
	void addOccurences();
	bool operator<(const Character& other) const;
	bool operator>(const Character& other) const;
	bool operator>(int other) const;
	bool operator<=(const Character& other);
	bool operator>=(const Character& other);
	bool operator==(const Character& other);
	bool operator!=(const Character& other);
	char getChar() const;
	int getOccurences() const;
	void setOccurences(int nOcc);

	friend std::ostream& operator<<(std::ostream& os, const Character& character);
};

#endif
