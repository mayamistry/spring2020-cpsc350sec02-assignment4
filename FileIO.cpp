#include "FileIO.h"

FileIO::FileIO() {
  m_fileName = "";

}

FileIO::FileIO(string name) {
  m_fileName = name;
}

FileIO::~FileIO() {
  delete m_fileText;
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
  //2. Create the registrar object based off of number of windows in text file
  //using the # of numbers from the top of the file (need to create track out
  //which line we are at on the file) lineCount == 1;

  int arraySize = 1000;
  m_fileText = new int[arraySize];
  int lineCount = 0;
  string currentLine = "";
  int numWindows = 0;
  int tempCount = 0; //keep track of this for the array in case you need to allocate more memory


  while (!inFS.eof()) {
    getline(inFS, currentLine);
    if (!inFS.fail()) {
      ++lineCount;
      if (lineCount == 1) {
        numWindows = stoi(currentLine);
      } else {
        if (tempCount == (arraySize - 1)) {
          m_fileText = allocateMoreMemory(m_fileText, arraySize);
        }
        m_fileText[tempCount] = stoi(currentLine);
        ++tempCount;
      }
    }
  }

  inFS.close();

  //create an instance of simulate and the registrar to pass into it
  //pass through the numWindows, window array, the queue, the string and other info??
  Registrar *r = new Registrar(numWindows);
  Simulate *s = new Simulate(numWindows, r, m_fileText, tempCount);

  s->simulate();
  s->calculateStats();
  s->printStats();
}

//allocate more memory to array if we need it
int* FileIO::allocateMoreMemory(int* curr, int currentSize) {
  int newSize = currentSize * 2;
  int* newArray = new int[newSize];
  for (int i = 0; i < currentSize; ++i) {
    newArray[i] = curr[i];
  }
  return newArray;
}
