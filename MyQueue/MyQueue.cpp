/*

COPYRIGHT (C) Angelo Indre (4680213) All rights reserved
Data Structures List Project
Author. Angelo Indre
        adi19@zips.uakron.edu
Purpose. Research performance of a selected data structure

*/

#include <iostream>

#include "MyQueue.h"

//Methods

    //Constructor and Destructor
MyQueue::MyQueue()
{
    head = nullptr;
    tail = nullptr;
}
MyQueue::~MyQueue()
{
    while (!empty())
        dequeue();
    head = nullptr;
    tail = nullptr;
}

    //Enqueue and Deque
void MyQueue::enqueue(const int& item)
{
    QNode* newNode;                 // Create and initialize a new node
    newNode = new QNode;
    newNode->data = item;
    newNode->next = nullptr;
    if (head == nullptr)            //case 1: head does not exist
    {
        head = newNode;             //new node is head and tail
        tail = head;
        return;
    } else                          //case 2: head exists
    {
        tail->next = newNode;       //wire new node after tail, assign tail to new node
        tail = newNode;
        return;
    }

}
int MyQueue::dequeue()
{
    int deleted;
    if (head == nullptr)
    {
        std::cout << "\nReturned 0 because queue is empty.\n";
        return 0;
    }
    else
    {
        QNode* nodePtr = head;      //temp node so we can rewire head without a memory leak
        head = head->next;          //rewire head
        deleted = nodePtr->data;    //save the val
        delete nodePtr;             //delete the node
        return deleted;             //return the value
    }
}

    //Other basic methods for the queue
bool MyQueue::empty()
{
    if (!head)
        return true;
    return false;
}
size_t MyQueue::size()
{
    int count = 0;
    if (head == nullptr)
        return 0;
    QNode* nodePtr;
    nodePtr = head;
    while (nodePtr != nullptr)
    {
        count++;
        nodePtr = nodePtr->next;
    }
    return count;
}
int MyQueue::front()
{
    return head->data;
}
int MyQueue::back()
{
    return tail->data;
}
void MyQueue::clear()
{
    while (!empty())
        dequeue();
}

    //Used for testing my container
void MyQueue::displayQ()
{
    QNode* nodePtr;
    nodePtr = head;
    while (nodePtr != nullptr)
    {
        std::cout << nodePtr->data << ", ";
        nodePtr = nodePtr->next;
    }
    std::cout << std::endl << std::endl;
}
