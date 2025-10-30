#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Scans the file
char* parser_scan_file(char* filename) {
  // Stores pointer of the dot in the filename
  const char* dot = strrchr(filename, '.');

  // Opens the file
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    printf(
        "[WARNING] parser_scan_file: Error opening file. Incorrect name or it "
        "does not "
        "exist.");
    exit(1);
  }

  // Compares the stuff of the dot
  // Rejects files with invalid extensions
  if (!dot || strcmp(dot + 1, LANGUAGE_EXTENSION) != 0) {
    printf(
        "[WARNING] parser_scan_file: Invalid file extension: cannot compile "
        "files that are not \".bx\"\n");
    exit(1);
  } else {
    printf("parser_scan_file: valid file extension. reading file.\n");
  }

  fseek(file, 0L, SEEK_END);
  long size = ftell(file);
  rewind(file);

  char* buffer = malloc(size + 1);
  if (!buffer) {
    perror("[WARNING] parser_scan_file: memory allocation failed");
    fclose(file);
    exit(1);
  }

  size_t bytesRead = fread(buffer, 1, size, file);
  buffer[bytesRead] = '\0';

  fclose(file);

  return buffer;
}
