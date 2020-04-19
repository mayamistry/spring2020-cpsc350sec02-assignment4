#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

//this is the list interface which StudentQueue will use to implement
template <class T>
class List {
  //get everything from textbook
  public:
    virtual void insert(T* element) = 0; //enqueue
    virtual T* remove() = 0; //dequeue
    virtual T* peek() = 0; //returns whatever is currently at the front BUT no action occurs

    //helper methods
    virtual bool isEmpty() = 0; //is the queue empty?
    virtual int getSize() = 0; //returns the number of items in a queue
};

#endif //LIST_H
