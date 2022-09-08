/*
    Trie.cpp

    Trie Data Structure
*/
#include "Trie.hpp"

Trie::Trie(){
    // set up the root with a standard default
    root = createNode('\0');
}

void Trie::Insert(const std::string& word){
    // start at the root
    node *curr = root;

    // loop through all characters

    for(int a=0; a< word.length(); a++){
        // grab a character from the word
        char c = word.at(a);

        // if there is not a node w/ this character
        if(curr->children[c - 'a'] == NULL){
            // create a node w/ this character
            curr->children[c - 'a'] = createNode(c);
        }
        // move to next node
        curr = curr->children[c - 'a'];
    }
    // set isWord to true
    curr->isWord = true;
}

// returns true if a word in the TRIE starts with the given prefix
bool Trie::StartsWith(const std::string& prefix){
    return getNode(prefix) != NULL;
}

// returns true if the word exists in the TRIE
bool Trie::Search(const std::string& word){
    node *curr = getNode(word);
    return curr != NULL && curr->isWord;
}
