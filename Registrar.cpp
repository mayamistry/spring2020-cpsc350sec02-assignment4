#include "Registrar.h"

Registrar::Registrar() {
  m_numWindows = 10;
  //m_windows = new Window[m_numWindows];
  initializeRegistrar();
}

Registrar::Registrar(int numWindows) {
  m_numWindows = numWindows;
  //m_windows = new Window[m_numWindows];
  initializeRegistrar();
}

void Registrar::initializeRegistrar() {
  m_windows = new Window *[m_numWindows];
  for (int i = 0; i < m_numWindows; ++i) {
    m_windows[i] = new Window();
  }
}

//add student to window (memory allocation in the array)
void Registrar::addStudent(Student *s, int index) {
  Window *curr = m_windows[index];
  curr->addStudent(s);
}

bool Registrar::isEmpty() {
  bool check = true;
  for (int i  = 0; i < m_numWindows; ++i) {
    Window *curr = m_windows[i];
    if (!curr->isWindowIdle()) {
      check = false;
      break;
    }
  }
  return check;
}

Window* Registrar::getCurrElement(int index) {
  return m_windows[index];
}
