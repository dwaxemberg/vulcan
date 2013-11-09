#include "vulcan.h"

// Traces with this debug level and below display
int GlobalDebugLevel = DBGLVL_VERBOSE;

int main(int argc, char* argv)
{
	char* rom = (char*)LoadRomIntoBuffer("..\\..\\ROM\\Super Mario Land (World).gb");
	if (rom != NULL) {
		int i;
		for (i = 0; i < 2 * MB; i++) {
			if (i % 16 == 0) {
				printf("\n");
			}
			else if (i % 8 == 0) {
				printf(" ");
			}

			printf("%02x ", (unsigned char) rom[i]);
		}
	}

	return 0;
}