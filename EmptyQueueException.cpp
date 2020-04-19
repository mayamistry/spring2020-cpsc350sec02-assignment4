#include <iostream>
using namespace std;

//Exception class to see if queueu is empty when trying to dequeue
class EmptyQueueException {
  public:
    EmptyQueueException();
    EmptyQueueException(string message);
    ~EmptyQueueException();

    string getMessage();
  private:
    string m_message;
};
