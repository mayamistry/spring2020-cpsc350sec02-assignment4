#include "FileIO.h"

FileIO::FileIO() {
  m_fileName = "";
}

FileIO::FileIO(string name) {
  m_fileName = name;
}

FileIO::~FileIO() {
  //nothing needs to get deleted here because no pointers are being created
}

void FileIO::setFileName(string name) {
  m_fileName = name;
}

string FileIO::getFileName() {
  return m_fileName;
}

void FileIO::readInFile() {
  cout << "Opening source file provided..." << endl;
  inFS.open(m_fileName);

  if (!inFS.is_open()) {
    cout << "Could not open file. Start program over." << endl;
    return;
  }

  //What do I need to do here?
  //1. Create the StudentQueue pointer instance
  //2. Create the two arrays, one for windows and students and create
  //using the # of numbers from the top of the file (need to create track out
  //which line we are at on the file) lineCount == 1;

  StudentQueue* queue = new StudentQueue();
  int lineCount = 0;
  string currentLine = "";
  string fileText = "";

  //use these two arrays to keep track and windows and students after being removed from the queue
  int *windowArray;
  int *studentArray;

  while (!inFS.eof()) {
    inFS >> currentLine;
    if (!inFS.fail()) {
      ++lineCount;
      if (lineCount == 1) {
        int numWindows = stoi(currentLine);
        windowArray = new int[numWindows];
        studentArray = new int[numWindows];
      } else {
        fileText += currentLine;
      }
    }
  }


  inFS.close();

  //create an instance of simulate here
  //pass through the numWindows, two arrays, the queue, the string and other info??



}
