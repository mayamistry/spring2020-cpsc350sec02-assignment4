#include <iostream>
using namespace std;

//List node for DLL
template <class T>
class ListNode {
  public:
    ListNode();
    ListNode(T* d);
    ~ListNode();
    //need these to be public so I can access them
    T* data; //pass any type through T
    ListNode *next;
    ListNode *prev;
};

template <class T>
ListNode<T>::ListNode() {
  data = NULL;
  next = NULL;
  prev = NULL;
}

template <class T>
ListNode<T>::ListNode(T* d) {
  data = d;
  next = NULL;
  prev = NULL;
}

template <class T>
ListNode<T>::~ListNode() {
  next = NULL;
  delete next;
}
