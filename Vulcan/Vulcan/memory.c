#include "vulcan.h"
#include "hardware.h"

void* RomBase;
void* SelectedRomBankBase;
void* VramBase;
void* SelectedRamBankBase;
void* InternalRamBase;
void* SpriteAttribMemoryBase;

void* TranslateAddress(unsigned short address) {
	if (address < ROM_BANK_0_END_ADDR) {
		return ADD_BYTE_OFFSET(RomBase,
			address - ROM_BANK_0_START_ADDR);
	}
	else if (address < ROM_SWITCHABLE_BANK_END_ADDR) {
		return ADD_BYTE_OFFSET(SelectedRomBankBase,
			address - ROM_SWITCHABLE_BANK_START_ADDR);
	}
	else if (address < VRAM_END_ADDR) {
		return ADD_BYTE_OFFSET(VramBase,
			address - VRAM_START_ADDR);
	}
	else if (address < RAM_SWITCHABLE_BANK_END_ADDR) {
		return ADD_BYTE_OFFSET(SelectedRamBankBase,
			address - RAM_SWITCHABLE_BANK_START_ADDR);
	}
	else if (address < RAM_INTERNAL_END_ADDR) {
		return ADD_BYTE_OFFSET(InternalRamBase,
			address - RAM_INTERNAL_START_ADDR);
	}
	else if (address < RAM_INTERNAL_ECHO_END_ADDR) {
		return ADD_BYTE_OFFSET(InternalRamBase,
			address - RAM_INTERNAL_ECHO_START_ADDR);
	}
	else if (address < OAM_END_ADDR) {
		return ADD_BYTE_OFFSET(SpriteAttribMemoryBase,
			address - OAM_START_ADDR);
	}
	else if (address < RESERVED0_END_ADDR) {
		// WI, RAZ?
		DBGPRINTLN(DBGLVL_WARN, "Reserved 0 section requested");
		return NULL;
	}
	else if (address < IO_PORTS_END_ADDR) {
		// TODO
		DBGPRINTLN(DBGLVL_WARN, "I/O ports unimplemented");
		return NULL;
	}
	else if (address < RESERVED1_END_ADDR) {
		// WI, RAZ?
		DBGPRINTLN(DBGLVL_WARN, "Reserved 1 section requested");
		return NULL;
	}
	else if (address < RAM_INTERNAL_TINY_END_ADDR) {
		// What memory does this map to?
		DBGPRINTLN(DBGLVL_WARN, "Tiny RAM section unimplemented");
		return NULL;
	}
	else if (address < INTERRUPT_ENABLE_END_ADDR) {
		// TODO
		DBGPRINTLN(DBGLVL_WARN, "IER unimplemented");
		return NULL;
	}

	DBGPRINTLN(DBGLVL_ERROR, "Invalid memory address");
	return NULL;
}