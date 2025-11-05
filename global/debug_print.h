#ifndef DEBUG_PRINT_H
#define DEBUG_PRINT_H

#include <stdarg.h>
#include <stdio.h>

// Global debug flag
extern int debug;

// Global debug log file pointer
extern FILE* debug_log;

// Initialize debug system (call in main)
static inline void debug_init(const char* filename) {
  debug_log = fopen(filename, "w");
  if (!debug_log) {
    perror("Failed to open debug log");
  }
}

// Close debug log
static inline void debug_close() {
  if (debug_log) {
    fclose(debug_log);
    debug_log = NULL;
  }
}

// Variadic debug print
static inline void debug_print(const char* FILENAME, const int LINE,
                               const char* FUNCNAME, const char* format, ...) {
  if (!debug) return;

  va_list args;
  va_start(args, format);

  char prefix[256];
  snprintf(prefix, sizeof(prefix), "['%s'::'%d'::'%s']:", FILENAME, LINE,
           FUNCNAME);

  // Print to console
  fprintf(stdout, "%-70s", prefix);
  vfprintf(stdout, format, args);
  fprintf(stdout, "\n");

  // Print to file if open
  if (debug_log) {
    va_list args_copy;
    va_copy(args_copy, args);

    fprintf(debug_log, "%-70s", prefix);
    vfprintf(debug_log, format, args_copy);
    fprintf(debug_log, "\n");

    va_end(args_copy);
  }

  va_end(args);
}

// Optional macro for legacy code
#define DEBUG_PRINT(...) debug_print(__FILE__, __LINE__, __func__, __VA_ARGS__)

#endif
