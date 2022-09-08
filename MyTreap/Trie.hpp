/*
    Trie.hpp

    Include file for Trie.cpp
*/

#ifndef TRIE_HPP_INCLUDED
#define TRIE_HPP_INCLUDED

#include <cstdlib>
#include <string>

class Trie{
public:
    // Constructor
    Trie();

    struct node{
        // character that the node holds
        char c;

        // is this node a complete word
        bool isWord;

        // holds all possible children, 1 for each char
        node *children[26];
    };

    // insert a word to the TRIE
    void Insert(const std::string& word);

    // return true if the word is in the TRIE
    bool Search(const std::string& word);

    // return true if word starts with the prefix
    bool StartsWith(const std::string& prefix);

    // return true if a node has children
    bool hasChildren(node *n){
        for(int a = 0; a < 26; a++){
            if(n->children[a] != NULL){
                return true;
            }
        }
        return false;
    }

    // delete a key from the TRIE
    void Delete(const std::string& word){

        // invalid word
        if(word.length() < 0){
            return;
        }
        // get the last node of the word
        node *curr = getNode(word);
        // if word is not in the TRIE
        if(curr == NULL){
            return;
        }

        // set isWord to false
        curr->isWord = false;
    }

private:
    // root
    node *root;

    // create a note w/ char ch
    node *createNode(char ch){
        // create new node
        node *newNode = new node;
        // populate data members
        newNode->c = ch;
        newNode->isWord = false;
        for(int a=0;a<26;a++){
            newNode->children[a] = NULL;
        }
        // return node
        return newNode;
    }

    // returns the last node of a given word, or NULL if not in TRIE
    node *getNode(const std::string& word){
        // create new node starting at root
        node *curr = root;

        // loop through all characters
        for(int a=0; a< word.length(); a++){
            // grab each char
            char c = word.at(a);

            // if there is not a node w/ this character
            if(curr->children[c-'a'] == NULL){
                return NULL;
            }
            // move to next node
            curr = curr->children[c - 'a'];
        }
        return curr;
    }
};

#endif // TRIE_HPP_INCLUDED
