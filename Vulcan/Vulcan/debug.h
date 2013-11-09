#include <stdio.h>

#define DBGLVL_NONE 0
#define DBGLVL_ERROR 1
#define DBGLVL_WARN 2
#define DBGLVL_INFO 3
#define DBGLVL_VERBOSE 4

extern int GlobalDebugLevel;

#define DBGPRINTLN(lvl, ...) \
	if (GlobalDebugLevel >= lvl) { \
		fprintf(stderr, __FILE__":%u ", __LINE__); \
		fprintf(stderr, __VA_ARGS__); \
		fprintf(stderr, "\n"); \
	}
