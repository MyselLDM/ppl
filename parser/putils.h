#pragma once
#include <stdio.h>
#include <stdlib.h>

// ========================
// Utility Functions
// ========================

// Safe memory allocation wrapper
void* safe_malloc(size_t size);

// Dynamic array helpers (resize arrays, etc.)
void** resize_array(void** array, size_t new_size);
