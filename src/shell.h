#pragma once
#include <vector>
#include <string>
#include <algorithm>

#include "scene_parser/parser.h"
#include "file_system/file_system.h"

enum class ShellMode {
  RunOnce, Interactive, Help
};

class Shell {
private:
  ShellMode mode;
  std::vector<std::string> arguments;

  void parseArguments();

  void interactive();
public:
  Shell(int argn, const char** argv);
  ~Shell();
};