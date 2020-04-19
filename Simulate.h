#include "StudentQueue.h"
#include "Registrar.h"

//DOES THIS NEED TO BE A TEMPLATE??????


class Simulate {
  public:
    Simulate();
    Simulate(int numWindows, Registrar *r, int *text, int numElements);
    void simulate();

    //helper methods
    bool continueSimulation();
    void calculateStats();
    void printStats();

  private:
    //variables for simulation
    int m_numWindows;
    StudentQueue<Student> *m_queue;
    StudentQueue<Student> *m_processed;
    int *m_fileText; //array holding the file text
    int m_numElements; //number of elements in the array
    bool m_continue;
    Registrar *m_registrar;

    int m_mainTime; //represents the clock tick that we're at

    //variables for stats
    int m_numStudents; //number that students in the whole simulation
    int m_totalStudentWait; //total minutes that all students wait in line
    float m_meanStudentWait; //average wait time for students in line
    int m_medianStudentWait; //median student wait time
    int m_maxStudentWait; //max student wait time
    int m_numStudentsOver10; //# students that have to wait for more than 10 mins
    int m_totalIdleTime; //total munutes that windows are idle (window[i] == -1)
    float m_meanIdleTime; //average idle time for windows
    int m_maxIdleWait; //max idle time for a window
    int m_numWindowsOver5; //# of windows that are idle for more than 5 mins
};
