
int HandleOps(/*TODO:fix this arg*/short opCode) {
	switch (opCode) {

	}
}

unsigned char CodeArgLength(short opCode) {
	switch (opCode) {
		
		//////// 8 - bit loads ////////	
	// LD r1, r2
	case 0x7F:
	case 0x78:
	case 0x79:
	case 0x7A:
	case 0x7B:
	case 0x7C:
	case 0x7D:
	case 0x7E:
	case 0x40:
	case 0x41:
	case 0x42:
	case 0x43:
	case 0x44:
	case 0x45:
	case 0x46:
	case 0x47:
	case 0x48:
	case 0x49:
	case 0x4A:
	case 0x4B:
	case 0x4C:
	case 0x4D:
	case 0x4E:
	case 0x50:
	case 0x51:
	case 0x52:
	case 0x53:
	case 0x54:
	case 0x55:
	case 0x56:
	case 0x57:
	case 0x58:
	case 0x59:
	case 0x5A:
	case 0x5B:
	case 0x5C:
	case 0x5D:
	case 0x5E:
	case 0x60:
	case 0x61:
	case 0x62:
	case 0x63:
	case 0x64:
	case 0x65:
	case 0x66:
	case 0x67:
	case 0x68:
	case 0x69:
	case 0x6A:
	case 0x6B:
	case 0x6C:
	case 0x6D:
	case 0x6E:
	case 0x70:
	case 0x71:
	case 0x72:
	case 0x73:
	case 0x74:
	case 0x75:
	case 0x36:
		return 0;
	
	// LD r1, n --> n is 8 bits
	case 0x06:
	case 0x0E:
	case 0x16:
	case 0x26:
	case 0x2E:
		return 1;
	
	// LD A, n --> n is register or 2 byte value LS byte first
	case 0x0A:
	case 0x1A:
		return 0;
	case 0xFA:
	case 0x3E: // TODO: figure out what # means
		return 2;
	
	// LD n, A --> n is a pair of registers or 2 byte value (LS byte first)
	case 0x02:
	case 0x12:
	case 0x77:
		return 0;
	case 0xEA:
		return 2;
	
	case 0xF2: // LD A,(C)
	case 0xE2: // LD (C),A
	// LD A,(HLD) same as LD A,(HL-) same as LDD A, (HL)
	// LDD A,(HL)
	case 0x3A:
	// LD (HLD),A same as LD (HL-),A same as LDD (HL), A
	// LDD (HL),A
	case 0x32:
	// LD A,(HLI) same as LD A,(HL+) same as LDI A,(HL)
	// LDI A,(HL)
	case 0x2A:
	// LD (HLI),A same as LD (HL+),A same as LDI (HL),A
	// LDI (HL),A
	case 0x22:
		return 0;

	// LD (n),A --> n is one byte immediate value
	case 0xE0:
	// LD A,(n) --> n is one byte immediate value
	case 0xF0:
		return 1;

		//////// 16 - bit loads ////////
	// LD n,nn --> n is two-byte register, nn is 2 byte immediate value
	case 0x01:
	case 0x11:
	case 0x21:
	case 0x31:
		return 2;

	// LD SP,HL
	case 0xF9:
		return 0;

	// LD HL,SP+n same as LDHL SP,n
	// LDHL SP,n --> n is one byte signed immediate value
	case 0xF8:
		return 1;

	// LD (nn),SP --> nn is a 2 byte immediate address
	case 0x08:
		return 2;

	// PUSH nn --> nn is register pair
	case 0xF5:
	case 0xC5:
	case 0xD5:
	case 0xE5:
		return 0;

	// POP nn --> nn is register pair
	case 0xF1:
	case 0xC1:
	case 0xD1:
	case 0xE1:
		return 0;

		//////// 8 - bit ALU ////////
	// ADD A,n --> n is a register or #
	case 0x87:
	case 0x80:
	case 0x81:
	case 0x82:
	case 0x83:
	case 0x84:
	case 0x85:
	case 0x86:
	case 0xC6: //TODO: figure out what # is
		return 0;

	// ADC A,n --> n is a register or #
	case 0x8F:
	case 0x88:
	case 0x89:
	case 0x8A:
	case 0x8B:
	case 0x8C:
	case 0x8D:
	case 0x8E:
	case 0xCE: //TODO: figure out what # is
		return 0;

	// SUB n --> n is a register or #
	case 0x97:
	case 0x90:
	case 0x91:
	case 0x92:
	case 0x93:
	case 0x94:
	case 0x95:
	case 0x96:
	case 0xD6: //TODO: figure out what # is
		return 0;

	// SBC A,n --> n is a register
	case 0x9F:
	case 0x98:
	case 0x99:
	case 0x9A:
	case 0x9B:
	case 0x9C:
	case 0x9D:
	case 0x9E:
		return 0;

	// AND n --> n is a register or #
	case 0xA7:
	case 0xA0:
	case 0xA1:
	case 0xA2:
	case 0xA3:
	case 0xA4:
	case 0xA5:
	case 0xA6:
	case 0xE6: //TODO: figure out what # is
		return 0;

	// OR n --> n is a register or #
	case 0xB7:
	case 0xB0:
	case 0xB1:
	case 0xB2:
	case 0xB3:
	case 0xB4:
	case 0xB5:
	case 0xB6:
	case 0xF6: //TODO: figure out what # is
		return 0;

	// XOR n -- n is a register or #
	case 0xAF:
	case 0xA8:
	case 0xA9:
	case 0xAA:
	case 0xAB:
	case 0xAC:
	case 0xAD:
	case 0xAE:
	case 0xEE: //TODO: figure out what # is
		return 0;

	// CP n --> n is a register or #
	case 0xBF:
	case 0xB8:
	case 0xB9:
	case 0xBA:
	case 0xBB:
	case 0xBC:
	case 0xBD:
	case 0xBE:
	case 0xFE: //TODO: figure out what # is
		return 0;

	// INC n --> is a register
	case 0x3C:
	case 0x04:
	case 0x0C:
	case 0x14:
	case 0x1C:
	case 0x24:
	case 0x2C:
	case 0x34:
		return 0;

	// SUB n --> n is a register
	case 0x3D:
	case 0x05:
	case 0x0D:
	case 0x15:
	case 0x1D:
	case 0x25:
	case 0x2D:
	case 0x35:
		return 0;

		//////// 16 - bit ALU ////////
	// ADD HL,n --> n is a register pair
	case 0x09:
	case 0x19:
	case 0x29:
	case 0x39:
		return 0;

	// ADD SP,n --> n is one byte signed immediate value
	case 0xE8:
		return 1;

	// INC nn --> nn is a register pair
	case 0x03:
	case 0x13:
	case 0x23:
	case 0x33:
		return 0;

	// DEC nn --> nn is a register pair
	case 0x0B:
	case 0x1B:
	case 0x2B:
	case 0x3B:
		return 0;
	}
}