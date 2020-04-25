#pragma once
#include <vector>
#include <string>
#include <algorithm>

#include "scene_parser/parser.h"
#include "file_system/file_system.h"

enum class ShellMode {
  RunOnce, Interactive, Help
};

enum class InteractiveMode {
  None, Exit, FileSystem, Parser
};

class Shell {
private:
  ShellMode shellMode;
  InteractiveMode interactiveMode;

  std::vector<std::string> arguments;

  void parseArguments();
  void clearInputBuffer();
  void separateBuffer(char* buffer, std::vector<char*>& bufferSeparated);

  void interactive();
  void interactiveFileSystem();
public:
  Shell(int argn, const char** argv);
  ~Shell();
};