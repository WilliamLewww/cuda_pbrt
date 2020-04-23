#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>

int main(int argn, const char** argv) {
  uint64_t blockSize = 512;

  const char* fileName = argv[1];
  int characterSpacing = 2;
  if (argn == 3) {
    characterSpacing = std::atoi(argv[2]);
  }

  if (access(fileName, F_OK) == 0) {
    FILE* file = fopen(fileName, "rb");

    fseek(file, 0, SEEK_END);
    uint64_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    uint64_t bytesPerLine = 32;
    uint64_t numberOfLines = fileSize / bytesPerLine;

    printf("Hexdump for %s with %ld blocks:\n\n", fileName, fileSize / blockSize);

    char* buffer = (char*)malloc(bytesPerLine);
    for (int x = 0; x < numberOfLines; x++) {
      if (x != 0 && x * bytesPerLine % blockSize == 0) {
        printf("\n");
      }

      fread(buffer, 1, bytesPerLine, file);
      printf("%06X: ", (unsigned int)(x * bytesPerLine));
      for (int y = 0; y < bytesPerLine; y++) {
        if (y != 0) {
          if (y % 8 == 0) {
            printf(" ");
          }

          if (y % characterSpacing == 0) {
            printf(" ");
          }
        }

        printf("%02X", buffer[y] & 0xff);
      }

      printf(" | ");

      for (int y = 0; y < bytesPerLine; y++) {
        printf("%c", buffer[y] < 32 ? '.' : buffer[y]);
      }

      if (x * bytesPerLine % blockSize == 0) {
        printf("        block: %ld", x * bytesPerLine / blockSize);
      }

      printf("\n");
    }

    free(buffer);
    fclose(file);
  }

  return 0;
}