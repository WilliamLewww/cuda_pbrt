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

  fileSystem = (FileSystem*)malloc(blockSize);
  fread(fileSystem, 1, blockSize, drive);

  if (strcmp(fileSystem->prefix, FILE_SYSTEM_PREFIX.c_str()) != 0) {
    free(fileSystem);

    fileSystem->startSignature = FILE_SYSTEM_SIGNATURE_START;

    fileSystem = (FileSystem*)malloc(blockSize);
    strcpy(fileSystem->prefix, FILE_SYSTEM_PREFIX.c_str());
    fileSystem->blockCount = blockCount;
    fileSystem->blockSize = blockSize;

    fileSystem->endSignature = FILE_SYSTEM_SIGNATURE_END;

    fwrite(fileSystem, 1, blockSize, drive);
  }
}

FileSystemDriver::~FileSystemDriver() {
  free(fileSystem);
  fclose(drive);
}

void FileSystemDriver::readBlock(void* buffer, uint64_t blockCount, uint64_t blockPosition) {
  fseek(drive, (fileSystem->blockSize * (blockPosition + 1)), SEEK_SET);
  fread(buffer, 1, fileSystem->blockSize * blockCount, drive);
}

void FileSystemDriver::writeBlock(void* buffer, uint64_t blockCount, uint64_t blockPosition) {
  fseek(drive, (fileSystem->blockSize * (blockPosition + 1)), SEEK_SET);
  fwrite(buffer, 1, fileSystem->blockSize * blockCount, drive);
}