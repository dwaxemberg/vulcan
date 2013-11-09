
// OS headers
#include <Windows.h>

// C standard library headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Useful size definitions
#define KB 1024
#define MB (1024 * KB)

// romloader.c definitions
void* LoadRomIntoBuffer(const char* filePath);