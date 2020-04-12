#include "StudentQueue.h"

class Simulate {
  public:
    Simulate();
    Simulate(int numWindows, StudentQueue *q, string text, int *w, int *s);
    void simulate();

    //helper methods
    bool continueSimulation();
    void printStats();

    int* allocateMoreMemory(int *curr);

  private:
    //variables for simulation
    int m_numWindows;
    StudentQueue *m_queue;
    string m_fileText;
    int *m_windowArray;
    int *m_studentArray;
    bool m_continue;

    int m_mainTime; //represents the clock tick that we're at

    //variables for stats
    //should we create arrays?? try and see if this works
    int *waitTimes; //student wait times in the queue
    int *idleTimes; //idle wait times for the windows
    int *arraySize;

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
