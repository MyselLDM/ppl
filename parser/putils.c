#include "putils.h"

// ========================
// Utility Functions
// ========================

void* safe_malloc(size_t size) {
  void* ptr = malloc(size);
  if (!ptr) {
    fprintf(stderr, "[FATAL] Memory allocation failed for %zu bytes\n", size);
    exit(EXIT_FAILURE);
  }
  return ptr;
}

void** resize_array(void** array, size_t new_size) {
  void** new_array = realloc(array, new_size * sizeof(void*));
  if (!new_array) {
    fprintf(stderr, "[FATAL] Memory reallocation failed for size %zu\n",
            new_size);
    exit(EXIT_FAILURE);
  }
  return new_array;
}
