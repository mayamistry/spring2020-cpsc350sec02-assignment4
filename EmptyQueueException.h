#include "EmptyQueueException.h"

//Default constructor
EmptyQueueException::EmptyQueueException() {
  m_message = "";
}

//Overloaded constructor
EmptyQueueException::EmptyQueueException(string message) {
  m_message = message;
}

//Destructor - no objects need to be deleted
EmptyQueueException::~EmptyQueueException() {
  //nothing happens here
}

//get method to get message if exception occurs
string EmptyQueueException::getMessage() {
  return m_message;
}
