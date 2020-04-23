#pragma once
#include <string>
#include <cstdint>
#include <cstring>
#include <unistd.h>

struct FileSystem {
  uint64_t startSignature;

  char prefix[21];
  uint64_t blockCount;
  uint64_t blockSize;

  uint64_t rootDirectoryBlock;

  uint64_t endSignature;
};

class FileSystemDriver {
private:
  static const std::string FILE_SYSTEM_PREFIX;
  static const uint64_t FILE_SYSTEM_SIGNATURE_START;
  static const uint64_t FILE_SYSTEM_SIGNATURE_END;

  FILE* drive;
  FileSystem* fileSystem;

  void readBlock(void* buffer, uint64_t blockCount, uint64_t blockPosition);
  void writeBlock(void* buffer, uint64_t blockCount, uint64_t blockPosition);
public:
  FileSystemDriver(std::string driveName, uint64_t blockCount, uint64_t blockSize);
  ~FileSystemDriver();
};