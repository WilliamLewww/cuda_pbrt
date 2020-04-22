#pragma once
#include <string>
#include <cstdint>
#include <cstring>
#include <unistd.h>

class FileSystem {
private:
  std::string driveName;

  FILE* drive;
public:
  FileSystem(std::string driveName, uint64_t driveSize, uint64_t blockSize);
  ~FileSystem();
};