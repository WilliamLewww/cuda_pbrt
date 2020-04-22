#include "file_system.h"

FileSystem::FileSystem(std::string driveName, uint64_t driveSize, uint64_t blockSize) {
  this->driveName = driveName;

  if (access(driveName.c_str(), F_OK) != 0) {
    drive = fopen(driveName.c_str(), "w");
    fclose(drive);
  }

  drive = fopen(driveName.c_str(), "r+");

  char* buffer = (char*)malloc(blockSize);
  fread(buffer, sizeof(char), blockSize, drive);

  if (strcmp(buffer, "raytrace-file-system") != 0) {
    char* firstBlock = (char*)malloc(blockSize);
    memcpy(firstBlock, "raytrace-file-system\0", 21);

    fwrite(firstBlock, sizeof(char), blockSize, drive);
    free(firstBlock);
  }
  else {

  }

  free(buffer);
}

FileSystem::~FileSystem() {
  fclose(drive);
}