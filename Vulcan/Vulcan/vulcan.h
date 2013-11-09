
// OS headers
#include <Windows.h>

// Vulcan headers
#include "hardware.h"
#include "debug.h"

// C standard library headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Useful definitions
#define KB 1024
#define MB (1024 * KB)
#define ADD_BYTE_OFFSET(x, y) ((void*)(((unsigned long)(x)) + (y)))
#define TO_UINT(x) (*((unsigned int*)(x)))
#define TO_INT(x) (*((int*)(x)))
#define TO_USHORT(x) (*((unsigned short*)(x)))
#define TO_SHORT(x) (*((short*)(x)))
#define TO_UCHAR(x) (*((unsigned char*)(x)))
#define TO_CHAR(x) (*((char*)(x)))

// romloader.c definitions
void* LoadRomIntoBuffer(const char* filePath);

// memory.c definitions
void* TranslateAddress(unsigned short address);