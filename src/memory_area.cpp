#include "memory_area.h"

void* allocateAligned(uint64_t size) {
  return memalign(64, size);
}

MemoryArea::MemoryArea(uint64_t blockSize) {
  this->blockSize = blockSize;

  currentBlockPosition = 0;
  currentAllocationSize = 0;
  currentBlock = nullptr;
}

MemoryArea::~MemoryArea() {

}

void* MemoryArea::allocate(uint64_t nBytes) {
  nBytes = ((nBytes + 15) & (~15));

  if (currentBlockPosition + nBytes > currentAllocationSize) {
    if (currentBlock) {
      usedBlockList.push_back(std::make_pair(currentAllocationSize, currentBlock));
      currentBlock = nullptr;
    }

    for (auto iterator = availableBlockList.begin(); iterator != availableBlockList.end(); iterator++) {
      if (iterator->first >= nBytes) {
        currentAllocationSize = iterator->first;
        currentBlock = iterator->second;
        availableBlockList.erase(iterator);
        break;
      }
    }

    if (!currentBlock) {
      currentAllocationSize = std::max(nBytes, blockSize);
      currentBlock = allocateAligned<uint8_t>(currentAllocationSize);
    }
    currentBlockPosition = 0;
  }

  void* blockOffset = currentBlock + currentBlockPosition;
  currentBlockPosition += nBytes;
  return blockOffset;
}

void MemoryArea::reset() {
  currentBlockPosition = 0;
  availableBlockList.splice(availableBlockList.begin(), usedBlockList);
}