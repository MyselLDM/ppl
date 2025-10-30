#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"

char* parser_scan_file(char* filename) {
  // Stores pointer of the dot in the filename
  const char* dot = strrchr(filename, '.');

  // Compares the stuff of the dot
  if (!dot || strcmp(dot + 1, "bx") != 0) {
    printf(
        "[WARNING] parser_scan_file: Invalid file extension: cannot compile "
        "files that are not \".bx\"\n");
    exit(1);
  } else {
    printf("parser_scan_file: valid file extension. reading file.\n");
  }

  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    exit(1);
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

  //    printf("parser_scan_file: parser successsful\nparser_scan_file: file
  //    contents:\n %s\n", buffer);
  return buffer;
}
