#include <iostream>
#include "RB_Tree.h"
#include "DLinkedList.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void read_text(RB_Tree<Character>& tree, char letters[], int counters[]) {
    for (int i = 0; i < 14; i++) {
        tree.insert(letters[i], counters[i]);
    }
}

void read_from_file(const std::string& filename, std::string& origin) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            origin += line;
        }

        file.close();
    }
    else {
        std::cout << "Failed to open the file." << std::endl;
    }
    file.close();
}

std::string filter_text(std::string text) {
    std::string result = "";
    for (char c : text) {
        if (std::isalpha(c)) {
            result += std::tolower(c);
        }
    }
    return result;
}

void count_chars(const std::string& text, char characters[], int occurrences[], int& count) {
  
    int counter[26] = { 0 }; 

    for (char c : text) {
        if (std::isalpha(c)) {
            int index = c - 'a';
            counter[index]++;
        }
    }

    count = 0;
    for (int i = 0; i < 26; i++) {
        if (counter[i] > 0) {
            characters[count] = static_cast<char>(i + 'a');
            occurrences[count] = counter[i];
            count++;
        }
    }
}


int main() {
    RB_Tree<Character> tree;
    DLinkedList<Character> list;

    const int MAX_SIZE = 26;
    char characters[MAX_SIZE];
    int char_counters[MAX_SIZE];
    int count;

    std::string text = "";

    read_from_file("exampleText.txt", text);
    text = filter_text(text);
    count_chars(text, characters, char_counters, count);

    for (int i = 0; i < count; i++) {
        tree.insert(characters[i], char_counters[i]);
    }

    for (int i = 0; i < count; i++) {
        list.addBack(characters[i], char_counters[i]);
    }

    char char_to_search = 'b';

    cout << "TREE " << char_to_search << " character: " << tree.search(char_to_search)->getValue() << endl;
    cout << "LIST " << char_to_search << " character: " << list.search(char_to_search)->getValue() << endl;


    return 0;
}
