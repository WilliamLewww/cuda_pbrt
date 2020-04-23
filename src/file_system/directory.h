#pragma once
#include <cstdint>

enum DirectoryType {
  DIRECTORY_TYPE_DIRECTORY, DIRECTORY_TYPE_FILE
};

struct Directory {
  uint64_t signatureStart;

  char name[128];
  DirectoryType type;

  uint64_t block;

  uint64_t freeBlock;
  uint64_t freeBlockCount;

  uint64_t parentDirectoryBlock;
  uint64_t subDirectoryBlock;
  uint64_t nextDirectoryBlock;

  uint64_t signatureEnd;
};