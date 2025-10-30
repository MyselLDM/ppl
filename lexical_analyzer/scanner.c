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
  debug_print("%s: passed filename: %s\n", __func__, filename);

  // Opens the file
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    debug_print(
        "[WARNING] %s: Error opening file. Incorrect name or it does not "
        "exist.\n",
        __func__);
    exit(1);
  }

  // Compares the stuff of the dot
  // Rejects files with invalid extensions
  if (!dot || strcmp(dot + 1, LANGUAGE_EXTENSION) != 0) {
    debug_print(
        "[WARNING] %s: Invalid file extension: cannot compile "
        "files that are not \".bx\"\n",
        __func__);
    exit(1);
  } else {
    printf("%s: valid file extension. reading file.\n", __func__);
  }

  fseek(file, 0L, SEEK_END);
  long size = ftell(file);
  rewind(file);

  char* buffer = malloc(size + 1);
  if (!buffer) {
    debug_print("[WARNING] %s: memory allocation failed", __func__);
    fclose(file);
    exit(1);
  }

  size_t bytesRead = fread(buffer, 1, size, file);
  buffer[bytesRead] = '\0';

  debug_print("%s: SUCCESS! read %ld bytes. closing file...\n", __func__,
              bytesRead);

  fclose(file);

  return buffer;
}
