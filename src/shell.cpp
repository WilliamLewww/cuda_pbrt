#include "shell.h"

Shell::Shell(int argn, const char** argv) {
  for (int x = 0; x < argn; x++) {
    arguments.push_back(std::string(argv[x]));
  }

  parseArguments();
}

Shell::~Shell() {

}

void Shell::parseArguments() {
  mode = ShellMode::RunOnce;

  if (std::find(arguments.begin(), arguments.end(), "--interactive") != arguments.end()) {
    mode = ShellMode::Interactive;
  }

  if (std::find(arguments.begin(), arguments.end(), "--help") != arguments.end()) {
    mode = ShellMode::Help;
  }

  if (mode == ShellMode::Interactive) {
    interactive();
  }

  if (mode == ShellMode::RunOnce) {
    
  }

  if (mode == ShellMode::Help) {
    printf("Usage:\n");
    printf("  cuda-pbrt.out [options]\n");
    printf("\n");
    printf("  --help                 display help description\n");
    printf("  --interactive          start program in interactive mode\n");
  }
}

void Shell::interactive() {

}