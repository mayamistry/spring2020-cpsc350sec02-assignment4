#include "Window.h"

class Registrar {
  public:
    Registrar();
    Registrar(int numWindows); //create the registrar and the window array component
    ~Registrar();

    //should we add a student to one of the windows here?
    //add student to window
    void initializeRegistrar();
    void addStudent(Student *s, int index);
    bool isEmpty();
    Window* getCurrElement(int index);

  private:
    Window **m_windows; //array of windows //DOES THIS NEED TO BE A POINTER OF POINTERS?????
    int m_numWindows;
};
