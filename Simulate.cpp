#include "Simulate.h"

Simulate::Simulate() {
  m_numWindows = 0;
  m_queue = NULL;
  m_processed = NULL;
  m_fileText = NULL;
  m_numElements = 0;
  m_continue = true;
  m_mainTime = 0;
  m_registrar = NULL; //array has the correct amount of memory blocks but all NULL


  m_numStudents = 0; //number that students in the whole simulation
  m_totalStudentWait = 0; //total minutes that all students wait in line
  m_meanStudentWait = 0; //average wait time for students in line
  m_medianStudentWait = 0; //median student wait time
  m_maxStudentWait = 0; //max student wait time
  m_numStudentsOver10 = 0; //# students that have to wait for more than 10 mins
  m_totalIdleTime = 0; //total munutes that windows are idle (window[i] == -1)
  m_meanIdleTime = 0; //average idle time for windows
  m_maxIdleWait = 0; //max idle time for a window
  m_numWindowsOver5 = 0; //# of windows that are idle for more than 5 mins
}

Simulate::Simulate(int numWindows, Registrar *r, int *text, int numElements) {
  m_numWindows = numWindows;
  m_queue = new StudentQueue<Student>();
  m_processed = new DoublyLL<Student>();
  m_fileText = text;
  m_numElements = numElements;
  m_continue = true;
  m_mainTime = 0;
  m_registrar = r; //array has the correct amount of memory blocks but all NULL

  m_numStudents = 0; //number that students in the whole simulation
  m_totalStudentWait = 0; //total minutes that all students wait in line
  m_meanStudentWait = 0; //average wait time for students in line
  m_medianStudentWait = 0; //median student wait time
  m_maxStudentWait = 0; //max student wait time
  m_numStudentsOver10 = 0; //# students that have to wait for more than 10 mins
  m_totalIdleTime = 0; //total munutes that windows are idle (window[i] == -1)
  m_meanIdleTime = 0; //average idle time for windows
  m_maxIdleWait = 0; //max idle time for a window
  m_numWindowsOver5 = 0; //# of windows that are idle for more than 5 mins
}

Simulate::~Simulate() {
  delete m_queue;
  delete m_processed;
  delete m_fileText;
  delete m_registrar;
}

void Simulate::simulate() {
  int stringIndex = 0; //keep track of index for string

  while (m_continue) {
    //CHECK #1: Are there any students at the windows? If so, iterate their times and also check if you can add another student to the window
    if (!m_registrar->isEmpty()) {
      for (int i = 0; i < m_numWindows; ++i) {
        Window *curr = m_registrar->getCurrElement(i);
        Student *s = curr->getStudent();
        //check if there is a student at this specific window
        if (!curr->isWindowIdle()) {
          //check if we need to remove the student if their times are equal
          if (curr->getCurrTime() == s->getWindowTime()) {
            //need to remove them from the window, but first check if student is in the queue
            m_processed->insertBack(s); //put student removed from registrar into the processed DLL to use for analysis purposes
            //take out the old idle time and add to the statistics
            int idleTime = curr->getIdleTime();
            m_totalIdleTime += idleTime;
            if (idleTime > m_maxIdleWait) {
              m_maxIdleWait = idleTime; //set new maxIdleTime if it's larger than the current one
            }
            if (idleTime > 5) {
              ++m_numWindowsOver5;
            }
            curr->setIdleTime(0);
            if (!m_queue->isEmpty()) {
              curr->setCurrTime(0); //reset the time for the window
              Student *s1 = m_queue->remove(); //remove the student from the queue
              m_registrar->addStudent(s1, i); //add student to this specific window
            } else {
              //there's no student in the queue, so make the window null
              curr->setCurrTime(-1);
              s = NULL;
              curr->setStudent(s);
            }
          } else {
            //the times are not equal for the window time and student time, so just increment the window time;
            curr->incrementCurrTime();
          }
        } else {
          //increment the idles times for the windows since student is NULL
          curr->incrementIdleTime();
        }
      }
    } else if (m_mainTime != 0) {
      for (int i = 0; i < m_numWindows; ++i) {
        Window *w = m_registrar->getCurrElement(i);
        if (w->isWindowIdle()) {
          w->incrementIdleTime();
        }
      }
    }


    //CHECK #2: Are there are any students in the queue? If so, iterate all of their wait times for that specific student
    if (!m_queue->isEmpty()) {
      ListNode<Student> *curr = m_queue->getFront(); //get front of the queue (pointer)
      Student *student = m_queue->peek(); //get front of the queue (Student)
      while (curr != NULL) {
        student = curr->data;
        student->incrementWaitTime();
        curr = curr->next;
      }
    }

    //CHECK #3: See if you can add any new students to the simulation based off of the string index of the text file
    if (stringIndex != -1) {
      if (m_mainTime == m_fileText[stringIndex]) {
        //if it does, then add the new students to the simulation
        ++stringIndex;
        int num = m_fileText[stringIndex]; //number of students being added at this clock tick
        ++stringIndex;
        m_numStudents += num;
        for (int i = 0; i < num; ++i) {
          //add the node (or nodes) to the queue first before doing anything
          Student *s = new Student(m_fileText[stringIndex]);
          m_queue->insert(s);
          if (stringIndex == m_numElements - 1) {
            stringIndex = -1;
            break;
          }
          ++stringIndex;
        }


        //check if any of the windows are open first
        for (int i = 0; i < m_numWindows; ++i) {
          Window *w = m_registrar->getCurrElement(i);
          if (!m_queue->isEmpty()) {
            if (w->isWindowIdle()) {
              w->setCurrTime(0);
              Student *s1 = m_queue->remove();
              m_registrar->addStudent(s1, i); //add student to this specific window
              //don't to worry about wait time because it's already stored in the student object
            }
          }
        }
      }
    }

    //AFTER DOING EVERYTHING, then check if you should continue the simulation
    if (stringIndex == 0) {
      //if the simulation hasn't even started, then don't do the boolean check
      m_continue = true;
    } else {
      m_continue = continueSimulation();
      if (m_continue == false) {
        //take all wait times and idle times from windows and place into stats variables
        for (int i  = 0; i < m_numWindows; ++i) {
          Window *w = m_registrar->getCurrElement(i);
          if (w->isWindowIdle()) {
            int idleTime = w->getIdleTime();
            m_totalIdleTime += idleTime;
            if (idleTime > m_maxIdleWait) {
              m_maxIdleWait = idleTime; //set new maxIdleTime if it's larger than the current one
            }
            if (idleTime > 5) {
              ++m_numWindowsOver5;
            }
          }
        }
      }
    }
    ++m_mainTime;
  }
}

//checks if we can exit simulation or not
bool Simulate::continueSimulation() {
  bool check = true;
  //check if the queue is empty and check if the registrar is empty
  if ((m_queue->isEmpty()) && (m_registrar->isEmpty())){
    check = false;
  }
  return check;
}

//calculates stats after simulation is over
void Simulate::calculateStats(){
  //SORTING A NEW Queue


  //sort the wait times for the students and put ordered times into an array
  int* waitTimes = new int[m_numStudents];
  int index = 0;
  while (!m_processed->isEmpty()) {
    ListNode<Student> *curr = m_processed->front;
    Student *minStudent = curr->data;
    int tempMin = minStudent->getWaitTime();
    while (curr != NULL) {
      Student *compare = curr->data;
      if (compare->getWaitTime() <= tempMin) {
        tempMin = compare->getWaitTime();
        minStudent = compare;
      }
      if (curr->next == NULL) {
        break;
      }
      curr = curr->next;
    }
    waitTimes[index++] = tempMin;
    m_totalStudentWait += tempMin;
    if (tempMin > 10){
      ++m_numStudentsOver10;
    }
    m_processed->remove(minStudent);
  }

  //calculate the mean and get the max wait time at the end of the array
  m_meanStudentWait = (float)(m_totalStudentWait / m_numStudents);
  m_maxStudentWait = waitTimes[m_numStudents - 1];

  //calculate median of student wait
  int mid = 0;
  //if even
  if (m_numStudents % 2 == 0) {
    mid = m_numStudents / 2;
    m_medianStudentWait = (waitTimes[mid] + waitTimes[mid + 1]) / 2;
  } else {
    //if odd
    mid = (m_numStudents / 2) + 1;
    m_medianStudentWait = waitTimes[mid];
  }

  //calculate mean for window idle waitTimes
  m_meanIdleTime = (float)m_totalIdleTime / m_numWindows;
}

//print all the stats using the member variables
void Simulate::printStats() {
  cout << "STATS FROM REGISTRAR SIMULATION: " << endl;
  cout << "Mean student wait time: " << m_meanStudentWait << endl;
  cout << "Median student wait time: " << m_medianStudentWait << endl;
  cout << "Longest student wait time: " << m_maxStudentWait << endl;
  cout << "# of students waiting for more than 10 mins: " << m_numStudentsOver10 << endl;
  cout << "Mean window idle time: " << m_meanIdleTime << endl;
  cout << "Longest window idle time: " << m_maxIdleWait << endl;
  cout << "# of windows idle for more than 5 mins: " << m_numWindowsOver5 << endl;
}
