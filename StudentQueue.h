#ifndef STUDENTQUEUE_H
#define STUDENTQUEUE_H

#include "List.h"
#include "DoublyLL.h"

//this is implementing the List interface
template <class T>
class StudentQueue : public List<T> {
  public:
    StudentQueue();
    ~StudentQueue();
    void insert(T* element); //enqueue
    T* remove(); //dequeue
    T* peek(); //returns whatever is currently at the front BUT no action occurs
    ListNode<T> *getFront();

    //helper methods
    bool isEmpty(); //is the queue empty?
    int getSize(); //returns the number of items in a queue

    int m_size; //don't need numElements since DLL is dynmaic in size
    ListNode<T> *front;
    ListNode<T> *rear;
    DoublyLL<T> *m_queue;
};

#endif //STUDENTQUEUE.H

template <class T>
StudentQueue<T>::StudentQueue() {
  m_size = 0;
  m_queue = new DoublyLL<T>();
  front = NULL;
  rear = NULL;
}

template <class T>
StudentQueue<T>::~StudentQueue() {
  delete m_queue;
}

template <class T>
bool StudentQueue<T>::isEmpty() {
  return (m_size == 0);
}

template <class T>
int StudentQueue<T>::getSize() {
  return m_size;
}

//equivalent to enqueue for the queue ADT
template <class T>
void StudentQueue<T>::insert(T* element) {
  ListNode<T> *node = new ListNode<T>(element);
  if (isEmpty()) {
    front = node;
    rear = node;
  } else {
    rear->next = node;
    node->next = NULL;
    node->prev = rear;
  }
  ++m_size;
  m_queue->insertBack(element);
}

//equivalent to dequeue for the queue ADT
template <class T>
T* StudentQueue<T>::remove() {
  ListNode<T> *curr = front;

  if (front->next == NULL) {
    //there is only one node in the list
    rear = NULL;//both front and back are equal to null bc there is only 1 node
  } else {
    //more than one node in the list
    front->next->prev = NULL;
    front = front->next;
    front->prev = NULL;
    curr->next = NULL;
  }
  T* data = m_queue->removeFront();
  --m_size;
  delete curr;
  return data;
}

template <class T>
T* StudentQueue<T>::peek() {
  return m_queue->getFront();
}

template <class T>
ListNode<T>* StudentQueue<T>::getFront() {
  return front;
}
