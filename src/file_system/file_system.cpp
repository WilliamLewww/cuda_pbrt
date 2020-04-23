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

  std::vector<char*> tokenList;
  int type = parsePath("/root/test/first/second", tokenList);
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

int FileSystemDriver::parsePath(const char* path, std::vector<char*>& tokenList) {
  char* tempPath = (char*)malloc(strlen(path) + 1);
  strcpy(tempPath, path);

  char* token = strtok(tempPath, "/");
  while (token != NULL) {
    char* tempToken = (char*)malloc(strlen(token) + 1);
    strcpy(tempToken, token);

    tokenList.push_back(tempToken);
    token = strtok(NULL, "/");
  }

  free(tempPath);

  if (path[0] == '/') {
    return PATH_TYPE_ABSOLUTE;
  }

  return PATH_TYPE_RELATIVE;
}

void FileSystemDriver::createRootDirectory() {
  Directory* rootDirectory = (Directory*)malloc(currentFileSystem->blockSize);
  rootDirectory->signatureStart = DIRECTORY_SIGNATURE_START;

  strcpy(rootDirectory->name, "root");
  rootDirectory->type = DIRECTORY_TYPE_DIRECTORY;

  rootDirectory->block = 1;

  rootDirectory->freeBlock = rootDirectory->block + 1;
  rootDirectory->freeBlockCount = currentFileSystem->blockCount - 2;

  rootDirectory->parentDirectoryBlock = 1;
  rootDirectory->subDirectoryBlock = 0;
  rootDirectory->nextDirectoryBlock = 0;

  rootDirectory->signatureEnd = DIRECTORY_SIGNATURE_END;

  writeBlock(rootDirectory, 1, 1);
  free(rootDirectory);
}

void FileSystemDriver::createDirectory(const char* name, uint64_t freeBlockCount) {
  Directory* directory = (Directory*)malloc(currentFileSystem->blockSize);
  directory->signatureStart = DIRECTORY_SIGNATURE_START;

  strcpy(directory->name, name);
  directory->type = DIRECTORY_TYPE_DIRECTORY;

  directory->block = currentDirectory->freeBlock;

  directory->freeBlock = directory->block + 1;
  directory->freeBlockCount = freeBlockCount;

  directory->parentDirectoryBlock = currentDirectory->block;
  directory->subDirectoryBlock = 0;
  directory->nextDirectoryBlock = 0;

  directory->signatureEnd = DIRECTORY_SIGNATURE_END;
  writeBlock(directory, 1, currentDirectory->freeBlock);

  currentDirectory->freeBlock = directory->block + directory->freeBlockCount + 1;
  currentDirectory->freeBlockCount -= directory->freeBlockCount + 1;

  if (currentDirectory->subDirectoryBlock == 0) {
    currentDirectory->subDirectoryBlock = directory->block;
  }
  else {
    Directory* previousDirectory = (Directory*)malloc(currentFileSystem->blockSize);
    readBlock(previousDirectory, 1, currentDirectory->subDirectoryBlock);

    while (previousDirectory->nextDirectoryBlock != 0) {
      readBlock(previousDirectory, 1, previousDirectory->nextDirectoryBlock);
    }

    previousDirectory->nextDirectoryBlock = directory->block;
    writeBlock(previousDirectory, 1, previousDirectory->block);
    free(previousDirectory);
  }

  writeBlock(currentDirectory, 1, currentDirectory->block);
  free(directory);
}