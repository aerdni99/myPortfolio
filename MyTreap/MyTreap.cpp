/*

COPYRIGHT (C) Angelo Indre (4680213) All rights reserved
Data Structures Treap Project
Author. Angelo Indre
        adi19@zips.uakron.edu

MyTreap.cpp

implementation file for MyTreap

*/

#include "MyTreap.hpp"
#include <limits>
#include <random>
#include <time.h>
#include <iostream>

TreapNode::TreapNode()
{
    key = NULL;
    left = right = nullptr;
    priority = std::numeric_limits<int>::max();

}
TreapNode::TreapNode(int keyVal)
{
    key = keyVal;
    priority = rand();
    left = right = nullptr;
}

MyTreap::MyTreap()
{
    srand(time(0));     // Seed for priority generatings
    root = nullptr;
}

MyTreap::~MyTreap()
{
    deleteSubTree(root);
}
void MyTreap::deleteSubTree(TreapNode* &parent)
{
    if (parent == nullptr)
        return;
    if (parent->left != nullptr)
        deleteSubTree(parent->left);
    if (parent->right != nullptr)
        deleteSubTree(parent->right);
    delete parent;
    parent = nullptr;
}

void MyTreap::insert(int keyVal)
{
    insert(keyVal, root);
}

void MyTreap::insert(int keyVal, TreapNode* &currentRoot)
{
    if (currentRoot == nullptr)                                         // If at a leaf node, create and insert node
    {
        currentRoot = new TreapNode(keyVal);
        return;
    }
    if (keyVal < currentRoot->key) {
        insert(keyVal, currentRoot->left);                              // BST move down to leaf node
        if (currentRoot->priority > currentRoot->left->priority) {      // If priority is wrong, rotate
            rotateRight(currentRoot);
        }
    }
    else {
        insert(keyVal, currentRoot->right);                             // BST move down to leaf node
        if (currentRoot->priority > currentRoot->right->priority) {     // If priority is wrong, rotate
            rotateLeft(currentRoot);
        }
    }
}

void MyTreap::rotateLeft(TreapNode* &parent)
{
    TreapNode *rightChild = parent->right;          // See below, flip flop right and left
    TreapNode *rightLeft = parent->right->left;
    rightChild->left = parent;
    parent->right = rightLeft;
    parent = rightChild;
}

void MyTreap::rotateRight(TreapNode* &parent)
{
    TreapNode* leftChild = parent->left;            // Pointer to left kid
    TreapNode* leftRight = parent->left->right;     // Pointer to left kid's right kid
    leftChild->right = parent;                      // Make parent its kid's parent
    parent->left = leftRight;                       // Old parent adopts its left child's old kid
    parent = leftChild;                             // Left child is new parent
}

void MyTreap::outputPreOrder()
{
    std::cout << "(key, priority) '/' = nullNode\n";                    // Format for output
    outputPreOrder(root);
}

void MyTreap::outputPreOrder(TreapNode *rooty)
{
    if (rooty == nullptr) {
        std::cout << "/\n";                                             // This node is null
        return;
    }                                                                   // Preorder traversal with cout's
    outputPreOrder(rooty->left);
    std::cout << "(" << rooty->key << ", " << rooty->priority << ")\n";
    outputPreOrder(rooty->right);
}

int MyTreap::getRootKey()
{
    return root->key;
}

void MyTreap::remove(int keyVal)
{
    remove(keyVal, root);
}

void MyTreap::remove(int keyVal, TreapNode* &currentRoot)
{                                       // Normal BST searching
    if (currentRoot == nullptr)         // key not found, return
        return;
    else if (keyVal < currentRoot->key)
    {
        remove(keyVal, currentRoot->left);
    }
    else if (keyVal > currentRoot->key)
    {
        remove(keyVal, currentRoot->right);
    }
    else                                                                        // key found, rotate to the bottom
    {
        if (currentRoot->left == nullptr && currentRoot->right == nullptr)      // Has no kids, delete
        {
            delete currentRoot;
            currentRoot = nullptr;
        }
        else if (currentRoot->left == nullptr)                                  // Has a right kid, move down
        {
            rotateLeft(currentRoot);
            remove(keyVal, currentRoot->left);
        }
        else if (currentRoot->right == nullptr)                                 // Has a left kid, move down
        {
            rotateRight(currentRoot);
            remove(keyVal, currentRoot->right);
        }
        else if (currentRoot->left->priority < currentRoot->right->priority)    // Has 2 kid, left takes priority, move down
        {
            rotateRight(currentRoot);
            remove(keyVal, currentRoot->right);
        }
        else                                                                    // Has 2 kid, right takes priority, move down
        {
            rotateLeft(currentRoot);
            remove(keyVal, currentRoot->left);
        }
    }
}

bool MyTreap::search(int keyVal)
{
    bool isFound = search(keyVal, root);
    return isFound;
}

bool MyTreap::search(int keyVal, TreapNode* &currentRoot)       // Recursive BST search
{
    if (currentRoot == nullptr)                 // base case: if you reach a leaf node and it's not a match, return false
        return false;
    else if (keyVal < currentRoot->key)         // Look left for less than
    {
        search(keyVal, currentRoot->left);
    }
    else if (keyVal > currentRoot->key)         // Right for greater than
    {
        search(keyVal, currentRoot->right);
    }
        return true;                            // Default case, key found, return true
}
