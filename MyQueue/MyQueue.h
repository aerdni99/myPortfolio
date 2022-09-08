#ifndef MYQUEUE_H_INCLUDED
#define MYQUEUE_H_INCLUDED

class MyQueue;

class QNode
{
    friend class MyQueue;
private:
    int data;
    QNode* next;
};

//Class definition
class MyQueue
{
private:

    QNode* head;
    QNode* tail;
public:
    MyQueue();                              //Default Ctor
    ~MyQueue();                             //Dtor
    void clear();                           //Empty the queue
    void enqueue(const int& item);          //Append item
    int dequeue();                          //Cut off head
    bool empty();                           //Check if empty
    void displayQ();                        //Display queue's contents
    size_t size();                          //Display current size of queue
    int front();                            //Return first value
    int back();                             //Return last value
};

#endif // MYQUEUE_H_INCLUDED
