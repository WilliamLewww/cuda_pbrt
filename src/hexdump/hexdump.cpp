#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>

int main(int argn, const char** argv) {
  uint64_t blockSize = 512;

  if (access(argv[1], F_OK) == 0) {
    FILE* file = fopen(argv[1], "rb");

    fseek(file, 0, SEEK_END);
    uint64_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    uint64_t bytesPerLine = 32;
    uint64_t numberOfLines = fileSize / bytesPerLine;

    char* buffer = (char*)malloc(bytesPerLine);
    for (int x = 0; x < numberOfLines; x++) {
      if (x != 0 && x * bytesPerLine % blockSize == 0) {
        printf("\n");
      }

      fread(buffer, 1, bytesPerLine, file);
      printf("%06X: ", (unsigned int)(x * bytesPerLine));
      for (int y = 0; y < bytesPerLine; y++) {
        if (y != 0 && y % 8 == 0) {
          printf(" ");
        }

        printf("%02X ", buffer[y] & 0xff);
      }

      printf("\n");
    }

    fclose(file);
  }

  return 0;
}