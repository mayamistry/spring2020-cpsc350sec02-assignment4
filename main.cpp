#include "FileIO.h"

//Main - runs the program here and in FileIO
int main(int argc, char**argv) {
  string filePath = "";
  if (argc > 1) {
    filePath = argv[1];
    FileIO *file = new FileIO(filePath);
    file->readInFile();
    delete file;
  } else {
    cout << "USAGE: ./a.out [input string]" << endl;
    return 1;
  }
  return 0;

}
