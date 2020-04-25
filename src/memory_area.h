#pragma once
#include <cstdint>
#include <list>
#include <utility>
#include <malloc.h>

void* allocateAligned(uint64_t size);

template <typename Type>
Type* allocateAligned(uint64_t count);

class MemoryArea {
private:
  uint64_t blockSize;

  uint64_t currentBlockPosition;
  uint64_t currentAllocationSize;
  uint8_t* currentBlock;

  std::list<std::pair<uint64_t, uint8_t*>> usedBlockList;
  std::list<std::pair<uint64_t, uint8_t*>> availableBlockList;
public:
  MemoryArea(uint64_t blockSize = 262144);
  ~MemoryArea();

  void* allocate(uint64_t nBytes);
  void reset();
};