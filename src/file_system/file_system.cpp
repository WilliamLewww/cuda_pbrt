#include "file_system.h"

std::map<int, std::string> FileSystemDriver::directoryTypeStringMap = {
  {DIRECTORY_TYPE_DIRECTORY, "directory"}, {DIRECTORY_TYPE_FILE, "file"}
};

std::map<int, std::string> FileSystemDriver::directoryTypeColorStringStartMap = {
  {DIRECTORY_TYPE_DIRECTORY, "\033[1;34m"}, {DIRECTORY_TYPE_FILE, "\033[1;32m"}
};
std::string FileSystemDriver::colorStringEnd = "\033[0m";

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

    currentFileSystem->rootDirectoryBlock = 1;

    currentFileSystem->signatureEnd = FILE_SYSTEM_SIGNATURE_END;

    fwrite(currentFileSystem, 1, blockSize, drive);

    char* clearBuffer = (char*)malloc(currentFileSystem->blockCount*currentFileSystem->blockSize);
    writeBlock(clearBuffer, currentFileSystem->blockCount, 0);
    free(clearBuffer);

    createRootDirectory();
  }

  currentDirectory = (Directory*)malloc(blockSize);
  readBlock(currentDirectory, 1, currentFileSystem->rootDirectoryBlock);
}

FileSystemDriver::~FileSystemDriver() {
  free(currentDirectory);
  free(currentFileSystem);
  fclose(drive);
}

bool FileSystemDriver::checkValidFileSystem(const char* path, uint64_t blockSize) {
  if (access(path, F_OK) != 0) {
    return false;
  }

  FILE* file = fopen(path, "r");
  FileSystem* fileSystem = (FileSystem*)malloc(blockSize);
  fread(fileSystem, 1, blockSize, file);

  bool validFileSystem = false;

  if (fileSystem->signatureStart == FILE_SYSTEM_SIGNATURE_START && fileSystem->signatureEnd == FILE_SYSTEM_SIGNATURE_END) {
    validFileSystem = true;
  }

  free(fileSystem);
  fclose(file);
  return validFileSystem;
}

void FileSystemDriver::readBlock(void* buffer, uint64_t blockCount, uint64_t blockPosition) {
  fseek(drive, (currentFileSystem->blockSize * (blockPosition + 1)), SEEK_SET);
  fread(buffer, 1, currentFileSystem->blockSize * blockCount, drive);
}

void FileSystemDriver::writeBlock(void* buffer, uint64_t blockCount, uint64_t blockPosition) {
  fseek(drive, (currentFileSystem->blockSize * (blockPosition + 1)), SEEK_SET);
  fwrite(buffer, 1, currentFileSystem->blockSize * blockCount, drive);
}

uint64_t FileSystemDriver::getDirectoryBlockFromPath(const char* path) {
  if (strcmp(path, "") == 0) {
    return currentFileSystem->rootDirectoryBlock;
  }
  std::vector<char*> tokenList;
  int pathType = parsePath(path, tokenList);

  Directory* directory = (Directory*)malloc(currentFileSystem->blockSize);
  if (pathType == PATH_TYPE_ABSOLUTE) {
    readBlock(directory, 1, currentFileSystem->rootDirectoryBlock);
  }
  else {
    readBlock(directory, 1, currentDirectory->block);
  }

  bool doesNotExist = false;
  for (int x = 0; x < tokenList.size(); x++) {
    if (strcmp(tokenList[x], "..") == 0) {
      readBlock(directory, 1, directory->parentDirectoryBlock);
    }
    else {
      if (strcmp(tokenList[x], ".") != 0) {
        readBlock(directory, 1, directory->subDirectoryBlock);
        while (strcmp(directory->name, tokenList[x]) != 0 && directory->nextDirectoryBlock != 0) {
          readBlock(directory, 1, directory->nextDirectoryBlock);
        }

        if (strcmp(directory->name, tokenList[x]) != 0) {
          doesNotExist = true;
        }
      }
    }

    free(tokenList[x]);
  }

  if (doesNotExist) {
    return 0;
  }

  uint64_t directoryBlock = directory->block;
  free(directory);
  return directoryBlock;
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

void FileSystemDriver::createDirectory(char* path, uint64_t freeBlockCount) {
  std::vector<char*> tokenList;
  parsePath(path, tokenList);

  char* lastToken;
  if (getDirectoryBlockFromPath(path) == 0) {
    lastToken = (char*)malloc(strlen(tokenList[tokenList.size() - 1]) + 1);
    strcpy(lastToken, tokenList[tokenList.size() - 1]);

    for (int x = 0; x < tokenList.size(); x++) {
      free(tokenList[x]);
    }
  }
  else {
    printf("Directory already exists!\n");

    for (int x = 0; x < tokenList.size(); x++) {
      free(tokenList[x]);
    }

    return;
  }

  char* parentPath = (char*)malloc(strlen(path) + 1);
  strcpy(parentPath, path);
  if (strlen(parentPath) - strlen(lastToken) == 0) {
    strcpy(parentPath, "."); 
  }
  else {
    parentPath[strlen(parentPath) - strlen(lastToken) - 1] = 0;
  }

  Directory* parentDirectory = (Directory*)malloc(currentFileSystem->blockSize);
  readBlock(parentDirectory, 1, getDirectoryBlockFromPath(parentPath));
  free(parentPath);

  Directory* directory = (Directory*)malloc(currentFileSystem->blockSize);
  directory->signatureStart = DIRECTORY_SIGNATURE_START;

  strcpy(directory->name, lastToken);
  directory->type = DIRECTORY_TYPE_DIRECTORY;

  directory->block = parentDirectory->freeBlock;

  directory->freeBlock = directory->block + 1;
  directory->freeBlockCount = freeBlockCount;

  directory->parentDirectoryBlock = parentDirectory->block;
  directory->subDirectoryBlock = 0;
  directory->nextDirectoryBlock = 0;

  directory->signatureEnd = DIRECTORY_SIGNATURE_END;
  writeBlock(directory, 1, parentDirectory->freeBlock);

  parentDirectory->freeBlock = directory->block + directory->freeBlockCount + 1;
  parentDirectory->freeBlockCount -= directory->freeBlockCount + 1;

  if (parentDirectory->subDirectoryBlock == 0) {
    parentDirectory->subDirectoryBlock = directory->block;
  }
  else {
    Directory* previousDirectory = (Directory*)malloc(currentFileSystem->blockSize);
    readBlock(previousDirectory, 1, parentDirectory->subDirectoryBlock);

    while (previousDirectory->nextDirectoryBlock != 0) {
      readBlock(previousDirectory, 1, previousDirectory->nextDirectoryBlock);
    }

    previousDirectory->nextDirectoryBlock = directory->block;
    writeBlock(previousDirectory, 1, previousDirectory->block);
    free(previousDirectory);
  }

  writeBlock(parentDirectory, 1, parentDirectory->block);
  free(directory);
  free(parentDirectory);

  free(lastToken);
}

void FileSystemDriver::changeDirectory(char* path) {
  uint64_t directoryBlock = getDirectoryBlockFromPath(path);

  if (directoryBlock == 0) {
    printf("Directory does not exists!\n");
  }
  else {
    readBlock(currentDirectory, 1, directoryBlock);
  }
}

std::string FileSystemDriver::getWorkingDirectory() {
  Directory* directory = (Directory*)malloc(currentFileSystem->blockSize);
  readBlock(directory, 1, currentDirectory->block);

  std::string path;
  if (directory->block == currentFileSystem->rootDirectoryBlock) {
    path = "";
  }
  else {
    path = std::string(directory->name);
  }

  while (directory->parentDirectoryBlock != currentFileSystem->rootDirectoryBlock) {
    readBlock(directory, 1, directory->parentDirectoryBlock);
    path = std::string(directory->name) + "/" + path;
  }
  path = "/" + path;

  free(directory);
  return path;
}

std::vector<std::string> FileSystemDriver::getDirectoryContents() {
  readBlock(currentDirectory, 1, currentDirectory->block);

  std::vector<std::string> contentList;

  if (currentDirectory->subDirectoryBlock != 0) {
    Directory* directory = (Directory*)malloc(currentFileSystem->blockSize);
    readBlock(directory, 1, currentDirectory->subDirectoryBlock);

    contentList.push_back(std::string(directory->name));

    while (directory->nextDirectoryBlock != 0) {
      readBlock(directory, 1, directory->nextDirectoryBlock);
      contentList.push_back(std::string(directory->name));
    }
  }

  return contentList;
}

std::vector<std::string> FileSystemDriver::getDirectoryContentsColored() {
  readBlock(currentDirectory, 1, currentDirectory->block);
  
  std::vector<std::string> contentList;

  if (currentDirectory->subDirectoryBlock != 0) {
    Directory* directory = (Directory*)malloc(currentFileSystem->blockSize);
    readBlock(directory, 1, currentDirectory->subDirectoryBlock);

    std::string content = directoryTypeColorStringStartMap[directory->type] + std::string(directory->name) + colorStringEnd;
    contentList.push_back(content);

    while (directory->nextDirectoryBlock != 0) {
      readBlock(directory, 1, directory->nextDirectoryBlock);
      contentList.push_back(std::string(directory->name));
    }
  }

  return contentList;
}

std::string FileSystemDriver::getWorkingDirectoryDetails() {
  readBlock(currentDirectory, 1, currentDirectory->block);
  
  std::string details = "";
  details += "\033[1;36mname:\033[0m.....................\033[1;34m" + std::string(currentDirectory->name) + "\033[0m\n";
  details += "\033[1;36mtype:\033[0m.....................\033[1;34m" + directoryTypeStringMap[currentDirectory->type] + "\033[0m\n";

  details += "\033[1;36mblock:\033[0m....................\033[1;34m" + std::to_string(currentDirectory->block) + "\033[0m\n";
  
  details += "\033[1;36mfreeBlock:\033[0m................\033[1;34m" + std::to_string(currentDirectory->freeBlock) + "\033[0m\n";
  details += "\033[1;36mfreeBlockCount:\033[0m...........\033[1;34m" + std::to_string(currentDirectory->freeBlockCount) + "\033[0m\n";
  
  details += "\033[1;36mparentDirectoryBlock:\033[0m.....\033[1;34m" + std::to_string(currentDirectory->parentDirectoryBlock) + "\033[0m\n";
  details += "\033[1;36msubDirectoryBlock:\033[0m........\033[1;34m" + std::to_string(currentDirectory->subDirectoryBlock) + "\033[0m\n";
  details += "\033[1;36mnextDirectoryBlock:\033[0m.......\033[1;34m" + std::to_string(currentDirectory->nextDirectoryBlock) + "\033[0m";

  return details;
}