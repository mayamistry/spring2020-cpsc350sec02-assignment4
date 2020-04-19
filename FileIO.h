#include "Simulate.h"
#include <fstream>

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
};
