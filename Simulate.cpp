#include "Simulate.h"

Simulate::Simulate() {
  m_numWindows = 0;
  m_queue = NULL;
  m_fileText = "";
  m_windowArray = NULL;
  m_studentArray = NULL;
  m_continue = true;
  m_mainTime = 0;
}

Simulate::Simulate(int numWindows, StudentQueue *q, string text, int *w, int *s) {
  m_numWindows = numWindows;
  m_queue = q;
  m_fileText = text;
  m_windowArray = w;
  m_studentArray = s;
  m_continue = true;
  m_mainTime = 0;
}


void Simulate::simulate() {
  int stringIndex = 0; //keep track of index for string
  while (m_continue) {
    //if m_mainTime == 0, then initialize both of the arrays to 0 and -1
    if (m_mainTime == 0) {
      //initialize both of the arrays to -1 for windows and 0 for students
      for (int i = 0; i < m_numWindows; ++i) {
        m_windowArray[i] = -1;
        m_studentArray[i] = 0;
      }
    }

    //MAKE FUNCTIONS FOR ALL THE DIFFERENT CHECKS??
    //check a huge number of conditions and things to do here
    //1. First check if there are students at the windows and iterate their times
    //also check if you can add students to the window
    for (int i = 0; i < m_numWindows; ++i) {
      if (m_numWindows != -1) {
        //need to check for two things: does w[i] == s[i]?? if not then iterate otherwise reset values
        if (m_numWindows[i] == m_studentArray[i]) {
          //need to remove them from the window now and reset everything
          if (!m_queue->isEmpty()) {
            //is there someone at the queue? then add them straight to the window
            m_numWindows[i] = 0;
            //dequeue the front element from the line
            int data = 0;//node's data (time needed at window)
            m_studentArray[i] = data;
          } else {
            //if no one is in the queue, then reset both arrays to 0 and -1
            m_windowArray[i] = -1;
            m_studentArray[i] = 0;
          }
        } else {
          m_numWindows[i] = m_numWindows[i] + 1; //how can I make this more efficient?
        }
      }
    }
    //2. if students are in the queue, then iterate their wait times as well
    //iterate through the current queue and iterate whatever wait times they have
    //???? not sure how to do this yet
    if (!m_queue->isEmpty()) {
      //figure out the wait time thing here
    }
    //otherwise do nothing since the queue is empty

    //3. take first element from string
    //does if the time represents that clock tick on the file name
    if (m_mainTime == m_fileText[stringIndex]) {
      //if it does, then add the new students to the simulation
      //iterate stringIndex here but figure out where...
      ++stringIndex;
      int num = fileText[stringIndex]; //number of students being added at this clock tick
      ++stringIndex;
      for (int i = 0; i < num; ++i) {
        //add the node (or nodes) to the queue first before doing anything
        ListNode *curr = new ListNode(fileText[stringIndex]);
        //INSERT NODE INTO THE QUEUE HERE
        //INITIALIZE THEIR WAIT TIMES HERE!!!!
        if (stringIndex == m_fileText.size() - 1) {
          stringIndex = -1; //don't read in anymore info from text file since we've read everything
        } else {
          ++stringIndex; //otherwise if there's more info in the file then iterate
        }
      }
      //check if any of the windows are open first
      for (int i = 0; i < m_numWindows; ++i) {
        if (m_numWindows[i] == -1) {
          m_numWindows[i] = 0;
          //dequeue the front element from the line
          //GET RID OF WAIT TIME THING but probably need to add to stats (don't if it equals 0)
          int data = //node's data (time needed at window)
          m_studentArray[i] = data;
        }
      }
    }

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

bool Simulate::continueSimulation() {
  bool check = false;
  //check if the queue is not empty and the arrays do not equal 0 or -1
  if (!m_queue->isEmpty()) {
    check = true;
  }
  for (int i = 0; i < numWindows; ++i) {
    if (m_windowArray[i] != -1) {
      check = true;
      break;
    }
  }
  return check;
}

int* Simulate::allocateMoreMemory(int* curr, int currentSize) {
  int newSize = currentSize * 2;
  int* newArray = new int[newSize];
  for (int i = 0; i < currentSize; ++i) {
    newArray[i] = curr[i];
  }

  return newArray;
}
