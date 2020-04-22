#include "file_system.h"

FileSystem::FileSystem(std::string driveName, uint64_t driveSize, uint64_t blockSize) {
  this->driveName = driveName;

  drive.open(driveName.c_str());

  if (!drive.good()) {
    std::ofstream newFile;
    newFile.open(driveName);
    newFile.close();

    drive.open(driveName.c_str());
  }

  printf("%d\n", drive.good());
}

FileSystem::~FileSystem() {
  drive.close();
}