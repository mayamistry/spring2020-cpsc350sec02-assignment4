#include "Simulate.h"
#include <fstream>

//Class that reads in file and gets all necessary info to run simulation
class FileIO {
  public:
    FileIO();
    FileIO(string name);
    ~FileIO();
    void setFileName(string name);
    string getFileName();
    void readInFile();

    //helper method
    int* allocateMoreMemory(int* curr, int currentSize);

  private:
    string m_fileName;
    ifstream inFS;
    int *m_fileText;
};
