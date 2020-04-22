#pragma once
#include <string>
#include <fstream>
#include <cstdint>

class FileSystem {
private:
  std::string driveName;
  std::fstream drive;
public:
  FileSystem(std::string driveName, uint64_t driveSize, uint64_t blockSize);
  ~FileSystem();
};