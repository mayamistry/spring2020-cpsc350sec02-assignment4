#include "Student.h"

Student::Student() {
  m_windowTime = 0;
  m_waitTime = 0;
}

Student::Student(int windowTime) {
  m_windowTime = windowTime;
  m_waitTime = 0;
}

Student::~Student() {
  //no pointers so no need to delete????
}

//setter and getter methods
void Student::setWindowTime(int time) {
  m_windowTime = time;
}

void Student::setWaitTime(int time) {
  m_waitTime = time;
}

int Student::getWindowTime() {
  return m_windowTime;
}

int Student::getWaitTime() {
  return m_waitTime;
}

//increment wait time in the queue
void Student::incrementWaitTime() {
  ++m_waitTime;
}
