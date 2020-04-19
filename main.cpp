#include "FileIO.h"

int main(int argc, char**argv) {
  string filePath = "";
  if (argc > 1) {
    filePath = argv[1];
    FileIO *file = new FileIO(filePath);
    file->readInFile();
  } else {
    cout << "USAGE: ./a.out [input string]" << endl;
    return 1;
  }
  return 0;

}
