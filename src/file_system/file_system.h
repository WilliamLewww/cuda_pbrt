#pragma once
#include <string>
#include <cstdint>
#include <cstring>
#include <unistd.h>
#include <map>
#include <vector>

#include "directory.h"

enum PathType {
  PATH_TYPE_ABSOLUTE, PATH_TYPE_RELATIVE
};

struct FileSystem {
  uint64_t signatureStart;

  char prefix[21];
  uint64_t blockCount;
  uint64_t blockSize;

  uint64_t rootDirectoryBlock;

  uint64_t signatureEnd;
};

class FileSystemDriver {
private:
  static std::map<int, std::string> directoryTypeStringMap;
  static std::map<int, std::string> directoryTypeColorStringStartMap;
  static std::string colorStringEnd;

  static const std::string FILE_SYSTEM_PREFIX;
  static const uint64_t FILE_SYSTEM_SIGNATURE_START;
  static const uint64_t FILE_SYSTEM_SIGNATURE_END;
  static const uint64_t DIRECTORY_SIGNATURE_START;
  static const uint64_t DIRECTORY_SIGNATURE_END;

  FILE* drive;
  FileSystem* currentFileSystem;
  Directory* currentDirectory;

  void readBlock(void* buffer, uint64_t blockCount, uint64_t blockPosition);
  void writeBlock(void* buffer, uint64_t blockCount, uint64_t blockPosition);

  uint64_t getDirectoryBlockFromPath(const char* path);
  int parsePath(const char* path, std::vector<char*>& tokenList);

  void createRootDirectory();
public:
  FileSystemDriver(std::string driveName, uint64_t blockCount, uint64_t blockSize);
  ~FileSystemDriver();

  static bool checkValidFileSystem(const char* path, uint64_t blockSize);

  void createDirectory(char* path, uint64_t freeBlockCount, DirectoryType directoryType);
  void changeDirectory(char* path);

  std::string getWorkingDirectory();
  std::vector<std::string> getDirectoryContents();
  std::vector<std::string> getDirectoryContentsColored();

  std::string getWorkingDirectoryDetails();
};