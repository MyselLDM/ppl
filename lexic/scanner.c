#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>

#include "../global/debug_print.h"
#include "../global/dictionary.h"

// Manual function to check if a filename ends with a given extension
int has_extension(const char* filename, const char* extension) {
  // Find length of filename
  int len_filename = 0;
  while (filename[len_filename] != '\0') len_filename++;

  // Find length of extension
  int len_ext = 0;
  while (extension[len_ext] != '\0') len_ext++;

  // Filename must be longer than extension + 1 (for the dot)
  if (len_filename <= len_ext) return 0;

  // Check that the character before extension is a dot
  if (filename[len_filename - len_ext - 1] != '.') return 0;

  // Compare characters from the end
  for (int i = 0; i < len_ext; i++) {
    if (filename[len_filename - len_ext + i] != extension[i]) return 0;
  }

  return 1;  // extension matches
}

// Scans the file
char* parser_scan_file(char* filename) {
  DEBUG_PRINT("passed filename: %s", filename);

  // Opens the file
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    DEBUG_PRINT("Error opening file. Incorrect name or it does not exist.");
    exit(1);
  }

  // Check file extension manually
  if (!has_extension(filename, LANGUAGE_EXTENSION)) {
    DEBUG_PRINT(
        "[!!WARNING!!]: Invalid file extension: cannot compile "
        "files that are not \".bx\"");
    fclose(file);
    exit(1);
  } else {
    printf("valid file extension. reading file.\n");
  }

  // Determine file size
  fseek(file, 0L, SEEK_END);
  long size = ftell(file);
  rewind(file);

  // Allocate buffer for file content
  char* buffer = malloc(size + 1);
  if (!buffer) {
    DEBUG_PRINT("[!!WARNING!!]: memory allocation failed");
    fclose(file);
    exit(1);
  }

  // Read file content into buffer
  size_t bytesRead = fread(buffer, 1, size, file);
  buffer[bytesRead] = '\0';

  DEBUG_PRINT("[!!SUCCESS!!] read %ld bytes. closing file...", bytesRead);

  fclose(file);

  return buffer;
}
