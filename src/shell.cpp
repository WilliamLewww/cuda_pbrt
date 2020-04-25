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
  shellMode = ShellMode::Help;

  if (std::find(arguments.begin(), arguments.end(), "--interactive") != arguments.end()) {
    shellMode = ShellMode::Interactive;
  }

  if (std::find(arguments.begin(), arguments.end(), "--input") != arguments.end()) {
    shellMode = ShellMode::RunOnce;
  }

  if (shellMode == ShellMode::Help) {
    printf("Usage:\n");
    printf("  cuda-pbrt.out [options]\n");
    printf("\n");
    printf("  --help                 display help description\n");
    printf("  --interactive          start program in interactive mode\n");
    printf("  --input <file>         render scene with provided scene file\n");
  }

  if (shellMode == ShellMode::Interactive) {
    interactive();
  }

  if (shellMode == ShellMode::RunOnce) {

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
  printf("  1 - start file system\n");
  printf("  2 - parse scene file\n");
  printf("  0 - exit program\n");
  printf("\n");
  printf("------------------------------------------------------------------------\n");

  char* optionBuffer = (char*)malloc(2);
  interactiveMode = InteractiveMode::None;

  while (interactiveMode == InteractiveMode::None) {
    printf("enter an option: ");
    fgets(optionBuffer, 2, stdin);

    if (optionBuffer[0] == '0') {
      interactiveMode = InteractiveMode::Exit;
    }

    if (optionBuffer[0] == '1') {
      interactiveMode = InteractiveMode::FileSystem;
    }

    if (optionBuffer[0] == '2') {
      interactiveMode = InteractiveMode::Parser;
    }

    while (optionBuffer[0] != '\n' && optionBuffer[0] != EOF) {
      fread(optionBuffer, sizeof(char), 1, stdin);
    }
  }

  free(optionBuffer);

  if (interactiveMode == InteractiveMode::FileSystem) {
    interactiveFileSystem();
  }
}

void Shell::interactiveFileSystem() {
  printf("\n");
  printf("enter path of file system: ");

  char* pathBuffer = (char*)malloc(128);
  fgets(pathBuffer, 128, stdin);
  strtok(pathBuffer, "\n");

  uint64_t blockCount = 0;
  uint64_t blockSize = 512;

  bool validFileSystem = FileSystemDriver::checkValidFileSystem(pathBuffer, blockSize);

  if (!validFileSystem && access(pathBuffer, F_OK) != 0) {
    printf("enter block count: ");
    scanf("%ld", &blockCount);
  }

  // printf("enter block size: ");
  // scanf("%ld", &blockSize);

  if (validFileSystem) {
    printf("using file system: %s\n", pathBuffer);
  }
  else {
    if (access(pathBuffer, F_OK) != 0) {
      printf("creating new file system: %s\n", pathBuffer);
    }
    else {
      printf("not a valid file system: %s\n", pathBuffer);
      free(pathBuffer);
      return;
    }
  }

  printf("\n");

  FileSystemDriver* fileSystemDriver = new FileSystemDriver(pathBuffer, blockCount, blockSize);
  free(pathBuffer);

  while (interactiveMode == InteractiveMode::FileSystem) {
    printf("rfs:%s$\n", fileSystemDriver->getWorkingDirectory().c_str());
  }

  delete fileSystemDriver;
}