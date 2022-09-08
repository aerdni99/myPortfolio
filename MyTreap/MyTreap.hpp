/*

COPYRIGHT (C) Angelo Indre (4680213) All rights reserved
Data Structures Treap Project
Author. Angelo Indre
        adi19@zips.uakron.edu

MyTreap.cpp

include file for MyTreap

*/

/*

    Using this structure for the TREEEEAP Project:

        Create a MyTreap object with the default constructor
        Insert/Remove/Search the structure with the respective public function

*/

#ifndef MYTREAP_HPP_INCLUDED
#define MYTREAP_HPP_INCLUDED

class TreapNode {
  private:

    int key;                // Stored value obeys BST rules
    TreapNode* left;        // Child ptrs
    TreapNode* right;
    int priority;           // Enforces min heap property. Randomly generated

    friend class MyTreap;

    TreapNode();            // Default node initialized to null with max priority
    TreapNode(int);         // Assigns key, generates random priority, children are nullptrs
};

class MyTreap {

  private:

    TreapNode* root;
    void insert(int, TreapNode* &);                 // Recursive calls to insert, remove, and search maintain treap structure
    void remove(int, TreapNode* &);
    bool search(int, TreapNode* &);
    void rotateLeft(TreapNode* &);                  // Private rotate functions are called by the above three functions
    void rotateRight(TreapNode* &);                 // Used for maintaining priority and BST properties
    void outputPreOrder(TreapNode*);                // Outputs tree from root
    void deleteSubTree(TreapNode* &);

  public:

    MyTreap();                                      // Default ctor initializes root to nullptr, calls srand()
    ~MyTreap();                                     // Dtor deletes every node in the tree;
    void insert(int);                               // Public MyTreap functions access private overloaded versions to
    void remove(int);                               // protect the root data
    bool search(int);
    void outputPreOrder();                          // Outputs treap in preorder. Used for my testing (calls private overload)
    int getRootKey();                               // Get method to see the root's key. also for my testing



};

#endif // MYTREAP_HPP_INCLUDED
