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

  if (std::find(arguments.begin(), arguments.end(), "-i") != arguments.end()) {
    mode == ShellMode::Interactive;
  }

  if (std::find(arguments.begin(), arguments.end(), "-h") != arguments.end()) {
    mode == ShellMode::Help;
  }

  if (mode == ShellMode::RunOnce) {

  }

  if (mode == ShellMode::Interactive) {
    runInteractive();
  }

  if (mode == ShellMode::Help) {

  }
}

void Shell::runInteractive() {

}