#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../global/debug_print.h"
#include "../global/dictionary.h"

// Scans the file
char* parser_scan_file(char* filename) {
  // Stores pointer of the dot in the filename
  const char* dot = strrchr(filename, '.');
  DEBUG_PRINT("[!!WARNING!!]: passed filename: %s", filename);

  // Opens the file
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    DEBUG_PRINT(
        "Error opening file. Incorrect name or it does not "
        "exist.");
    exit(1);
  }

  // Compares the stuff of the dot
  // Rejects files with invalid extensions
  if (!dot || strcmp(dot + 1, LANGUAGE_EXTENSION) != 0) {
    DEBUG_PRINT(
        "[!!WARNING!!]: Invalid file extension: cannot compile "
        "files that are not \".bx\"");
    exit(1);
  } else {
    printf("valid file extension. reading file.");
  }

  fseek(file, 0L, SEEK_END);
  long size = ftell(file);
  rewind(file);

  char* buffer = malloc(size + 1);
  if (!buffer) {
    DEBUG_PRINT("[!!WARNING!!]: memory allocation failed");
    fclose(file);
    exit(1);
  }

  size_t bytesRead = fread(buffer, 1, size, file);
  buffer[bytesRead] = '\0';

  DEBUG_PRINT("[!!SUCCESS!!] read %ld bytes. closing file...", bytesRead);

  fclose(file);

  return buffer;
}
