#include "vulcan.h"

// Traces with this debug level and below display
int GlobalDebugLevel = DBGLVL_VERBOSE;

extern char* RomBase;

int main(int argc, char* argv)
{
	char* rom = (char*)LoadRomIntoBuffer("..\\..\\ROM\\Super Mario Land (World).gb");
	RomBase = rom;

	if (rom != NULL) {
		/*int i;
		for (i = 0; i < 2 * MB; i++) {
			if (i % 16 == 0) {
				printf("\n");
			}
			else if (i % 8 == 0) {
				printf(" ");
			}

			printf("%02x ", (unsigned char) rom[i]);
		}*/


		char* title = TranslateAddress(0x0134);
		int i;
		printf("Cart title: ");
		for (i = 0; i < 16; i++) {
			printf("%c", title[i]);
		}
		printf("\n");
	}

	return 0;
}