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
  m_processed = new StudentQueue<Student>();
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
            m_processed->insert(s); //put student removed from registrar into the processed queue to use for analysis purposes
            ++m_numStudents;
            //take out the old idle time and add to the statistics
            int idleTime = curr->getIdleTime();
            m_totalIdleTime += idleTime;
            if (idleTime > m_maxIdleWait) {
              m_maxIdleWait = idleTime; //set new maxIdleTime if it's larger than the current one
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
        for (int i = 0; i < num; ++i) {
          //add the node (or nodes) to the queue first before doing anything
          Student *s = new Student(m_fileText[stringIndex]);
          m_queue->insert(s);
          ++stringIndex;
          if (stringIndex == m_numElements) {
            stringIndex = -1;
          }
        }

        //check if any of the windows are open first
        for (int i = 0; i < m_numWindows; ++i) {
          Window *w = m_registrar->getCurrElement(i);
          if (!m_queue->isEmpty()) {
            if (w->isWindowIdle()) {
              w->setCurrTime(0);
              Student *s1 = m_queue->remove(); //remove the student from the queue SEG FAULT HERE!!!!!!
              m_registrar->addStudent(s1, i); //add student to this specific window
              //don't to worry about wait time because it's already stored in the student object
            }
          }
        }
      }
    }
    cout << "MAIN TIME: " << m_mainTime << endl;
    //What's in the queue?
    ListNode<Student> *curr = m_queue->getFront(); //get front of the queue (pointer)
    Student *student = m_queue->peek(); //get front of the queue (Student)
    while (curr != NULL) {
      student = curr->data;
      cout << "Student in queue: " << student->getWindowTime() << endl;
      curr = curr->next;
    }

    //What's in the registrar?
    for (int i = 0; i  < m_numWindows; ++i) {
      Window *w = m_registrar->getCurrElement(i);
      cout << "Window at registrar: " << w->getCurrTime() << endl;
    }

    cout << endl;

    //AFTER DOING EVERYTHING, then check if you should continue the simulation
    if (stringIndex == 0) {
      //if the simulation hasn't even started, then don't do the boolean check
      m_continue = true;
    } else {
      m_continue = continueSimulation();
    }
    ++m_mainTime;
  }
}

//NEED TO FIX THIS
bool Simulate::continueSimulation() {
  bool check = true;
  //check if the queue is empty and check if the registrar is empty
  if ((m_queue->isEmpty()) && (m_registrar->isEmpty())){
    check = false;
  }
  return check;
}

void Simulate::calculateStats(){
//   //SORTING A NEW Queue
// int tempMin = 0;
// int waitTimes = new int[m_numStudents];
//
//
//
// //mean student wait time
// int total = 0;
// int index = 0;
// ListNode<Student> *curr = m_queue->getFront(); //get front of the queue (pointer)
//   Student *student = m_queue->peek(); //get front of the queue (Student)
//     while (curr != NULL) {
//       int currTime = student->getWaitTime();
//       total += currTime;
//       if (currTime > maxStudentWait){
//         maxStudentWait = currTime;
//       }
//       if (currTime > 10){
//         ++numStudentsOver10;
//       }
//       curr = curr->next;
//       student = curr->data;
//     }
// }
// int studentMean = (total)/(m_numStudents);
// cout << "The mean student wait time is: " << studentMean << endl;
//
//
// //median student wait time
//
// //longest student wait time
// cout << longest student wait time << endl;
//
// //number of students waiting over 10 minutes
//   cout << "Number of students waiting over 10 minutes: " << numStudentsOver10 << endl;
//
//
//
//
// //mean window idle time
// int WindowMean = (.. + .. +.. )/numWindows
//
// //longest w 
}

void Simulate::printStats() {

}
