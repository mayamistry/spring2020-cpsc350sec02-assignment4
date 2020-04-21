#include <iostream>
using namespace std;

//Student object that holds window time and wait time in queue
class Student {
  public:
    Student();
    Student(int windowTime);
    ~Student();

    //setter and getter methods
    void setWindowTime(int time);
    void setWaitTime(int time);
    int getWindowTime();
    int getWaitTime();

    //increment wait time in the queue
    void incrementWaitTime();

  private:
    int m_windowTime; //time needed at window
    int m_waitTime; //wait time in the queue
};
