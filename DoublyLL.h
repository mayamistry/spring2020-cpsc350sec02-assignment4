#include "ListNode.h"

template <class T>
class DoublyLL{
  private:
      ListNode<T> *front;
      ListNode<T> *back;
      unsigned int size; //no such thing as negative size
  public:
    DoublyLL();
    ~DoublyLL();

    void insertFront(T* data);
    void insertBack(T* data);
    T* removeFront();
    T* removeBack();
    T* remove(T* val);
    int search(T* val); //will return position of node
    T* removeAtPos(int pos);

    unsigned int getSize();
    bool isEmpty();
    void printList(); // will print list
    T* getFront();
    T* getBack();

 };

//implementation file (.cpp) for my DoublyLinkedList

//default constructor
template <class T>
DoublyLL<T>::DoublyLL(){
   size = 0;
   front = NULL;
   back = NULL;
 }

//destructor
template <class T>
DoublyLL<T>::~DoublyLL(){
   front = NULL;
   back = NULL;
   delete front;
   delete back;
}

//returns size of the DLL
template <class T>
unsigned int DoublyLL<T>::getSize(){
   return size;
 }

//checks if the DLL is empty or not
template <class T>
bool DoublyLL<T>::isEmpty(){
   return (size == 0);
}

//prints all components of the list currently
template <class T>
void DoublyLL<T>::printList(){
  ListNode<T> *curr = front;

  while(curr != NULL){
    cout << curr->data << endl;
    curr = curr->next;
  }
}

//insert node of type T to the front of the DLL
template <class T>
void DoublyLL<T>::insertFront(T* d){
  ListNode<T> *node = new ListNode<T>(d);

  if(isEmpty()){
    back = node; //b/c back and front are the same
  }else{
    //not Empty
    front->prev = node;
    node->next = front;
  }
  front = node;
  size++;
}

//insert node of type T to the back of the DLL
template <class T>
void DoublyLL<T>::insertBack(T* d){
  ListNode<T> *node = new ListNode<T>(d);

  if(isEmpty()){
    front = node;
    back = node;
  }else{
    //not Empty
    back->next = node;
    node->next = NULL;
    node->prev = back;
  }
  back = node;
  size++;
}

//remove node of type T from the front of the DLL
template <class T>
T* DoublyLL<T>::removeFront(){
  ListNode<T> *tempNode = front;
  //error check, make sure list is not empty
  if (tempNode == NULL) {
    //list is empty
    return NULL;
  }

  if (front->next == NULL) {
    //there is only one node in the list
    back = NULL;//both front and back are equal to null bc there is only 1 node
  } else {
    //more than one node in the list
    front->next->prev = NULL;
    front = front->next;
    front->prev = NULL;
    tempNode->next = NULL;
  }
  T* temp = tempNode->data;
  size--;
  delete tempNode;
  return temp;
}

//remove node of type T from the back of the DLL
template <class T>
T* DoublyLL<T>::removeBack(){
  ListNode<T> *tempNode = back;
  //error check, make sure lsit is not empty

  if (back->prev == NULL) {
    //there is only one node in the list
    front = NULL;//both front and back are equal to null bc there is only 1 node
  } else {
    //more than one node in the list
    front->prev->next = NULL;
  }

  back = back->prev;
  tempNode->prev = NULL;
  T* temp = tempNode->data;
  size--;
  delete tempNode;
  return temp;
}

//need to find the value in the list before we can delete
//this function does not take in a position as a parameter
template <class T>
T* DoublyLL<T>::remove(T* val){
  ListNode<T> *curr = front;

  //lets look for this value
  while(curr->data != val){
    curr = curr->next;
    if (curr == NULL) {
      return NULL;
    }
  }

  //if we get here, we found our node/value, now lets proveed to delete
  if (curr == front){
    //if node to be deleted is the front
    front = curr->next;
  } else{
    //the node to be deleted is somewhere in between front and back
    curr->prev->next = curr->next;
  }

  if (curr == back) {
    back = curr->prev;
  } else{
    //the node to be deleted is somewhere in between front and back
    curr->next->prev = curr->prev;
  }

  curr->next = NULL;
  curr->prev = NULL;
  T* temp = curr->data;
  size--;
  delete curr;
  return temp;
}


//serach function for double link list is the same as single link list
template <class T>
int DoublyLL<T>::search(T* val){ //O(N)
  int pos = -1; //pos means position
  ListNode<T> *curr = front;
  //lets loop and attempt to find the value
  while(curr != NULL){
    ++pos;
    if(curr->data == val){
      //we found it
      break;
    }
    else{
      //we didnt find it continue iterating
      curr = curr->next;
    }
  }
    if(curr = NULL){
      //we didnt find it
      pos = -1;
    }
    return pos;
}

template <class T>
T* DoublyLL<T>::removeAtPos(int pos){
  //error checking to make sure pos does not exceed size of ListNode
  int idx = 0;
  ListNode<T> *curr = front;
  ListNode<T> *prev = front;
  while(idx != pos){
    //loop until I find the position
    prev = curr;
    curr = curr->next;
    idx++;
  }

  //now lets continue w the deletion processing
  prev->next = curr->next;
  curr->next = NULL;
  T* temp = curr->data;
  delete curr;
  size--;

  return temp;
}

template <class T>
T* DoublyLL<T>::getFront(){
  if (isEmpty()) {
    return NULL;
  }
  return front->data;
}

template <class T>
T* DoublyLL<T>::getBack(){
  if (isEmpty()) {
    return NULL;
  }
  return back->data;
}
