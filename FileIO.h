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

    //add extra helper methods here

  private:
    string m_fileName;
    ifstream inFS;
};
