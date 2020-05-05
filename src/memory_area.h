#pragma once
#include <cstdint>
#include <list>
#include <utility>
#include <malloc.h>

void* allocateAligned(uint64_t size);

template <typename Type>
Type* allocateAligned(uint64_t count) {
  return (Type*)allocateAligned(count * sizeof(Type));
}

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

  template <typename Type> 
  Type* allocate(uint64_t n = 1, bool runConstructor = true);

  void reset();
};

template <typename Type>
Type* MemoryArea::allocate(uint64_t n, bool runConstructor) {
  Type* space = (Type*)allocate(n * sizeof(Type));
  if (runConstructor) {
    for (uint64_t x = 0; x < n; x++) {
      new (&space[x])Type();
    }
  }
  return space;
}