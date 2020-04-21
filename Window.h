#include "Student.h"

//Class to hold the student in the window when in rgeistrar
class Window {
  public:
    Window();
    ~Window();

    //setter and getter methods
    void setStudent(Student *s);
    Student* getStudent();
    void setCurrTime(int time);
    void setIdleTime(int time);
    int getCurrTime();
    int getIdleTime();

    //increment curr and idle times
    void incrementCurrTime();
    void incrementIdleTime();

    //add student to window object
    void addStudent(Student *s);

    //check if window is idle
    bool isWindowIdle();

  private:
    Student *m_student;
    int m_currTime; //compare this time to the student time needed at window
    int m_idleTime; //for how many minutes does the window not have a student?
};
