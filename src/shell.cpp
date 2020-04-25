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

void Shell::clearInputBuffer() {
  char* clearBuffer = (char*)malloc(2);
  fread(clearBuffer, sizeof(char), 1, stdin);
  while (clearBuffer[0] != '\n' && clearBuffer[0] != EOF) {
    fread(clearBuffer, sizeof(char), 1, stdin);
  }
  free(clearBuffer);
}

void Shell::separateBuffer(char* buffer, std::vector<char*>& bufferSeparated) {
  char* tempBuffer = (char*)malloc(strlen(buffer) + 1);
  strcpy(tempBuffer, buffer);

  char* token = strtok(tempBuffer, " ");
  while (token != NULL) {
    char* tempToken = (char*)malloc(strlen(token) + 1);
    strcpy(tempToken, token);

    bufferSeparated.push_back(tempToken);
    token = strtok(NULL, " ");
  }

  free(tempBuffer);
}

void Shell::interactive() {
  printf("\033[1;32m  ██████╗██╗   ██╗██████╗  █████╗     ██████╗ ██████╗ ██████╗ ████████╗ \033[0m\n");
  printf("\033[1;32m ██╔════╝██║   ██║██╔══██╗██╔══██╗    ██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝ \033[0m\n");
  printf("\033[1;32m ██║     ██║   ██║██║  ██║███████║    ██████╔╝██████╔╝██████╔╝   ██║    \033[0m\n");
  printf("\033[1;32m ██║     ██║   ██║██║  ██║██╔══██║    ██╔═══╝ ██╔══██╗██╔══██╗   ██║    \033[0m\n");
  printf("\033[1;32m ╚██████╗╚██████╔╝██████╔╝██║  ██║    ██║     ██████╔╝██║  ██║   ██║    \033[0m\n");
  printf("\033[1;32m  ╚═════╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝    ╚═╝     ╚═════╝ ╚═╝  ╚═╝   ╚═╝    \033[0m\n");
  printf("\n");
  printf("  \033[1;34m%s\033[0m - \033[1;36m%s\033[0m\n", "1", "start file system");
  printf("  \033[1;34m%s\033[0m - \033[1;36m%s\033[0m\n", "2", "parse scene file");
  printf("  \033[1;34m%s\033[0m - \033[1;36m%s\033[0m\n", "0", "exit program");
  printf("\n");
  printf("------------------------------------------------------------------------\n");

  char* optionBuffer = (char*)malloc(2);
  interactiveMode = InteractiveMode::None;

  while (interactiveMode == InteractiveMode::None) {
    printf("\033[1;36m%s\033[0m", "enter an option: ");
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

    clearInputBuffer();
  }

  free(optionBuffer);

  if (interactiveMode == InteractiveMode::FileSystem) {
    interactiveFileSystem();
  }
}

void Shell::interactiveFileSystem() {
  printf("\n");
  printf("\033[1;36m%s\033[0m", "enter path of file system: ");

  char* pathBuffer = (char*)malloc(128);
  fgets(pathBuffer, 128, stdin);
  strtok(pathBuffer, "\n");

  uint64_t blockCount = 0;
  uint64_t blockSize = 512;

  bool validFileSystem = FileSystemDriver::checkValidFileSystem(pathBuffer, blockSize);

  if (!validFileSystem && access(pathBuffer, F_OK) != 0) {
    printf("\033[1;36m%s\033[0m", "enter block count: ");
    scanf("%ld", &blockCount);
  }

  // printf("enter block size: ");
  // scanf("%ld", &blockSize);

  if (validFileSystem) {
    printf("\033[1;33m%s\033[0m\033[1;37m%s\033[0m", "using file system: ", pathBuffer);
  }
  else {
    if (access(pathBuffer, F_OK) != 0) {
      printf("\033[1;33m%s\033[0m\033[1;37m%s\033[0m", "created new file system: ", pathBuffer);
    }
    else {
      printf("\033[1;33m%s\033[0m\033[1;37m%s\033[0m", "not a valid file system: ", pathBuffer);
      free(pathBuffer);
      return;
    }
  }

  printf("\n");

  FileSystemDriver* fileSystemDriver = new FileSystemDriver(pathBuffer, blockCount, blockSize);
  free(pathBuffer);

  clearInputBuffer();

  char* commandBuffer = (char*)malloc(128);
  while (interactiveMode == InteractiveMode::FileSystem) {
    printf("\033[1;32m%s\033[0m:\033[1;35m%s\033[0m$ ", "rfs", fileSystemDriver->getWorkingDirectory().c_str());
    fgets(commandBuffer, 128, stdin);
    strtok(pathBuffer, "\n");

    std::vector<char*> commandBufferSeparated;
    separateBuffer(commandBuffer, commandBufferSeparated);

    if (strcmp(commandBufferSeparated[0], "mkdir") == 0) {
      fileSystemDriver->createDirectory(commandBufferSeparated[1], (uint64_t)atoi(commandBufferSeparated[2]));
    }

    if (strcmp(commandBufferSeparated[0], "cd") == 0) {
      fileSystemDriver->changeDirectory(commandBufferSeparated[1]);
    }

    if (strcmp(commandBufferSeparated[0], "pwd") == 0) {
      printf("%s\n", fileSystemDriver->getWorkingDirectory().c_str());
    }

    if (strcmp(commandBufferSeparated[0], "ls") == 0) {
      std::vector<std::string> directoryContents = fileSystemDriver->getDirectoryContentsColored();

      if (directoryContents.size() > 0) {
        for (int x = 0; x < directoryContents.size(); x++) {
          printf("%s  ", directoryContents[x].c_str());
        }
        printf("\n");
      }
    }

    if (strcmp(commandBufferSeparated[0], "pwdd") == 0) {
      printf("%s\n", fileSystemDriver->getWorkingDirectoryDetails().c_str());
    }

    for (int x = 0; x < commandBufferSeparated.size(); x++) {
      free(commandBufferSeparated[x]);
    }
  }
  free(commandBuffer);

  delete fileSystemDriver;
}