#include "vulcan.h"

void* LoadRomIntoBuffer(const char* filePath) {
	FILE* romFile = NULL;
	void* buffer;
	size_t bytesRead;

	// The maximum ROM size is 2MB
	buffer = calloc(2, MB);
	if (buffer == NULL) {
		goto FailureCleanup;
	}

	// Open with "rb" means no text translation will take place
	romFile = fopen(filePath, "rb");
	if (romFile == NULL) {
		goto FailureCleanup;
	}

	bytesRead = fread(buffer, 2, MB, romFile);
	fclose(romFile);

	if (!ferror(romFile)) {
		return buffer;
	}

FailureCleanup:
	if (buffer != NULL) {
		free(buffer);
	}

	return NULL;
}