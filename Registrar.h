#include "Window.h"

//Registrar to hold the students in windows
class Registrar {
  public:
    Registrar();
    Registrar(int numWindows); //create the registrar and the window array component
    ~Registrar();

    //add student to window
    void initializeRegistrar();
    void addStudent(Student *s, int index);
    bool isEmpty();
    Window* getCurrElement(int index);

  private:
    Window **m_windows; //array of windows
    int m_numWindows;
};
