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
  mode = ShellMode::Help;

  if (std::find(arguments.begin(), arguments.end(), "--interactive") != arguments.end()) {
    mode = ShellMode::Interactive;
  }

  if (std::find(arguments.begin(), arguments.end(), "--input") != arguments.end()) {
    mode = ShellMode::RunOnce;
  }

  if (mode == ShellMode::Help) {
    printf("Usage:\n");
    printf("  cuda-pbrt.out [options]\n");
    printf("\n");
    printf("  --help                 display help description\n");
    printf("  --interactive          start program in interactive mode\n");
    printf("  --input <file>         render scene with provided scene file\n");
  }

  if (mode == ShellMode::Interactive) {
    interactive();
  }

  if (mode == ShellMode::RunOnce) {

  }
}

void Shell::interactive() {
  printf("  ██████╗██╗   ██╗██████╗  █████╗     ██████╗ ██████╗ ██████╗ ████████╗ \n");
  printf(" ██╔════╝██║   ██║██╔══██╗██╔══██╗    ██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝ \n");
  printf(" ██║     ██║   ██║██║  ██║███████║    ██████╔╝██████╔╝██████╔╝   ██║    \n");
  printf(" ██║     ██║   ██║██║  ██║██╔══██║    ██╔═══╝ ██╔══██╗██╔══██╗   ██║    \n");
  printf(" ╚██████╗╚██████╔╝██████╔╝██║  ██║    ██║     ██████╔╝██║  ██║   ██║    \n");
  printf("  ╚═════╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝    ╚═╝     ╚═════╝ ╚═╝  ╚═╝   ╚═╝    \n");
  printf("\n");
  printf("  1 - open file system\n");
  printf("  2 - parse scene file\n");
  printf("  9 - exit program\n");
  printf("\n");
}