#include "Window.h"

Window::Window() {
  m_student = NULL;
  m_currTime = -1;
  m_idleTime = 0;
}

Window::~Window() {
  delete m_student;
}

//setter and getter methods

void Window::setStudent(Student *s) {
  m_student = s;
}

Student* Window::getStudent() {
  return m_student;
}

void Window::setCurrTime(int time) {
  m_currTime = time;
}

void Window::setIdleTime(int time) {
  m_idleTime = time;
}

int Window::getCurrTime() {
  return m_currTime;
}

int Window::getIdleTime() {
  return m_idleTime;
}

//increment curr and idle times
void Window::incrementCurrTime() {
  ++m_currTime;
}

void Window::incrementIdleTime() {
  ++m_idleTime;
}

void Window::addStudent(Student *s) {
  m_student = s;
  m_currTime = 0;
}

//check if window is idle
bool Window::isWindowIdle() {
  return (m_student == NULL);
}
