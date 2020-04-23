#include "file_system.h"

const std::string FileSystemDriver::FILE_SYSTEM_PREFIX = "raytrace-file-system";
const uint64_t FileSystemDriver::FILE_SYSTEM_SIGNATURE_START = 0x26F7726624502524;
const uint64_t FileSystemDriver::FILE_SYSTEM_SIGNATURE_END = 0x26F7726624502525;
const uint64_t FileSystemDriver::DIRECTORY_SIGNATURE_START = 0x26F7726624502526;
const uint64_t FileSystemDriver::DIRECTORY_SIGNATURE_END = 0x26F7726624502527;

FileSystemDriver::FileSystemDriver(std::string driveName, uint64_t blockCount, uint64_t blockSize) {
  if (access(driveName.c_str(), F_OK) != 0) {
    drive = fopen(driveName.c_str(), "w");
    fclose(drive);
  }

  drive = fopen(driveName.c_str(), "r+");

  currentFileSystem = (FileSystem*)malloc(blockSize);
  fread(currentFileSystem, 1, blockSize, drive);

  if (strcmp(currentFileSystem->prefix, FILE_SYSTEM_PREFIX.c_str()) != 0) {
    free(currentFileSystem);
    currentFileSystem = (FileSystem*)malloc(blockSize);

    currentFileSystem->signatureStart = FILE_SYSTEM_SIGNATURE_START;

    strcpy(currentFileSystem->prefix, FILE_SYSTEM_PREFIX.c_str());
    currentFileSystem->blockCount = blockCount;
    currentFileSystem->blockSize = blockSize;

    currentFileSystem->rootDirectoryBlock = 0;

    currentFileSystem->signatureEnd = FILE_SYSTEM_SIGNATURE_END;

    fwrite(currentFileSystem, 1, blockSize, drive);

    char* clearBuffer = (char*)malloc(currentFileSystem->blockCount*currentFileSystem->blockSize);
    writeBlock(clearBuffer, currentFileSystem->blockCount, 0);
    free(clearBuffer);

    createRootDirectory();
  }

  currentDirectory = (Directory*)malloc(blockSize);
  readBlock(currentDirectory, 1, 1);
}

FileSystemDriver::~FileSystemDriver() {
  free(currentDirectory);
  free(currentFileSystem);
  fclose(drive);
}

void FileSystemDriver::readBlock(void* buffer, uint64_t blockCount, uint64_t blockPosition) {
  fseek(drive, (currentFileSystem->blockSize * (blockPosition + 1)), SEEK_SET);
  fread(buffer, 1, currentFileSystem->blockSize * blockCount, drive);
}

void FileSystemDriver::writeBlock(void* buffer, uint64_t blockCount, uint64_t blockPosition) {
  fseek(drive, (currentFileSystem->blockSize * (blockPosition + 1)), SEEK_SET);
  fwrite(buffer, 1, currentFileSystem->blockSize * blockCount, drive);
}

void FileSystemDriver::createRootDirectory() {
  Directory* rootDirectory = (Directory*)malloc(currentFileSystem->blockSize);
  rootDirectory->signatureStart = DIRECTORY_SIGNATURE_START;

  strcpy(rootDirectory->name, "root");
  rootDirectory->type = DIRECTORY_TYPE_DIRECTORY;

  rootDirectory->block = 1;

  rootDirectory->freeBlock = rootDirectory->block + 1;
  rootDirectory->freeBlockCount = currentFileSystem->blockCount - 1;

  rootDirectory->parentDirectoryBlock = 1;
  rootDirectory->subDirectoryBlock = 0;
  rootDirectory->nextDirectoryBlock = 0;

  rootDirectory->signatureEnd = DIRECTORY_SIGNATURE_END;

  writeBlock(rootDirectory, 1, 1);
  free(rootDirectory);
}