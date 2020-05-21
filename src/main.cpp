#include "shell.h"

int main(int argn, const char** argv) {
  Shell* shell = new Shell(argn, argv);
  delete shell;
  
  return 0;
}