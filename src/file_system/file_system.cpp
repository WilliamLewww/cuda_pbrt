#include "file_system.h"

const std::string FileSystemDriver::FILE_SYSTEM_PREFIX = "raytrace-file-system";
const uint64_t FileSystemDriver::FILE_SYSTEM_SIGNATURE_START = 0x26F7726624502524;
const uint64_t FileSystemDriver::FILE_SYSTEM_SIGNATURE_END = 0x26F7726624502525;

FileSystemDriver::FileSystemDriver(std::string driveName, uint64_t blockCount, uint64_t blockSize) {
  if (access(driveName.c_str(), F_OK) != 0) {
    drive = fopen(driveName.c_str(), "w");
    fclose(drive);
  }

  drive = fopen(driveName.c_str(), "r+");

  FileSystem* fileSystemBuffer = (FileSystem*)malloc(blockSize);
  fread(fileSystemBuffer, 1, blockSize, drive);

  if (strcmp(fileSystemBuffer->prefix, FILE_SYSTEM_PREFIX.c_str()) != 0) {
    free(fileSystemBuffer);

    fileSystemBuffer->startSignature = FILE_SYSTEM_SIGNATURE_START;

    fileSystemBuffer = (FileSystem*)malloc(blockSize);
    strcpy(fileSystemBuffer->prefix, FILE_SYSTEM_PREFIX.c_str());
    fileSystemBuffer->blockCount = blockCount;
    fileSystemBuffer->blockSize = blockSize;

    fileSystemBuffer->endSignature = FILE_SYSTEM_SIGNATURE_END;

    fwrite(fileSystemBuffer, 1, blockSize, drive);
  }
  else {

  }

  free(fileSystemBuffer);
}

FileSystemDriver::~FileSystemDriver() {
  fclose(drive);
}

void readBlock(void* buffer, uint64_t blockCount, uint64_t blockPosition) {

}

void writeBlock(void* buffer, uint64_t blockCount, uint64_t blockPosition) {

}