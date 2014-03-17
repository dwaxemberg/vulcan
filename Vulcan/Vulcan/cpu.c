#include "vulcan.h"

GB_CPU cpu;

int HandleOps(unsigned char* programCode) {
	unsigned char regs[8] = { cpu.rB, cpu.rC, cpu.rD, cpu.rE, cpu.rH, cpu.rL, cpu.rHL, cpu.rA };
	unsigned char n;
	switch (programCode[0]) {
		// LD A, (BC)
		/*cpu.rA = FUSED_REG_TO_UCHAR(cpu.rBC);

		// LD (BC), A
		FUSED_REG_TO_UCHAR(cpu.rBC) = cpu.rA;

		// LD BC, nn
		cpu.rBC = 0x1234;

		// PUSH AF
		cpu.rSP -= 2;
		FUSED_REG_TO_USHORT(cpu.rSP) = cpu.rAF;

		// POP AF
		cpu.rAF = FUSED_REG_TO_USHORT(cpu.rSP);
		cpu.rSP += 2;
		*/
	
#pragma region 8 bit loads		
		//////// 8 - bit loads ////////	
		// LD nn,n --> nn is a register, n is a 1 byte immediate value
	case 0x06:
		n = programCode[1]; 
		cpu.rB = FUSED_REG_TO_UCHAR(n);
		return 2;
	case 0x0E:
		n = programCode[1];
		cpu.rC = FUSED_REG_TO_UCHAR(n);
		return 2;
	case 0x16:
		n = programCode[1];
		cpu.rD = FUSED_REG_TO_UCHAR(n);
		return 2;
	case 0x1E:
		n = programCode[1];
		cpu.rE = FUSED_REG_TO_UCHAR(n);
		return 2;
	case 0x26:
		n = programCode[1];
		cpu.rH = FUSED_REG_TO_UCHAR(n);
		return 2;
	case 0x2E:
		n = programCode[1];
		cpu.rL = FUSED_REG_TO_UCHAR(n);
		return 2;
		
		// LD r1, r2
	case 0x7F:
	case 0x78:
	case 0x79:
	case 0x7A:
	case 0x7B:
	case 0x7C:
	case 0x7D:
	case 0x7E:
		cpu.rA = regs[programCode[0] - 0x78];
		return 1;
	case 0x40:
	case 0x41:
	case 0x42:
	case 0x43:
	case 0x44:
	case 0x45:
	case 0x46:
		cpu.rB = regs[programCode[0] - 0x40];
		return 1;
	case 0x48:
	case 0x49:
	case 0x4A:
	case 0x4B:
	case 0x4C:
	case 0x4D:
	case 0x4E:
		cpu.rC = regs[programCode[0] - 0x48];
		return 1;
	case 0x50:
	case 0x51:
	case 0x52:
	case 0x53:
	case 0x54:
	case 0x55:
	case 0x56:
		cpu.rD = regs[programCode[0] - 0x50];
		return 1;
	case 0x58:
	case 0x59:
	case 0x5A:
	case 0x5B:
	case 0x5C:
	case 0x5D:
	case 0x5E:
		cpu.rE = regs[programCode[0] - 0x58];
		return 1;
	case 0x60:
	case 0x61:
	case 0x62:
	case 0x63:
	case 0x64:
	case 0x65:
	case 0x66:
		cpu.rH = regs[programCode[0] - 0x60];
		return 1;
	case 0x68:
	case 0x69:
	case 0x6A:
	case 0x6B:
	case 0x6C:
	case 0x6D:
	case 0x6E:
		cpu.rL = regs[programCode[0] - 0x68];
		return 1;
	case 0x70:
	case 0x71:
	case 0x72:
	case 0x73:
	case 0x74:
	case 0x75:
		cpu.rHL = regs[programCode[0] - 0x70];
		return 1;
	case 0x36:
		cpu.rHL = programCode[1];
		return 2;
		// LD A, n --> n is register, 2 byte value LS byte first, or # (unsigned immediate value)
	case 0x0A:
	case 0x1A:
		cpu.rA = cpu.rBC;
		return 1;
	case 0xFA:
		cpu.rA = CHARS_TO_SHORT(programCode[1], programCode[2]);
		return 3;
	case 0x3E:
		cpu.rA = programCode[1];
		return 2;

		// LD n, A --> n is a pair of registers or 2 byte value (LS byte first)
	case 0x02:
		cpu.rBC = cpu.rA;
		return 1;
	case 0x12:
		cpu.rDE = cpu.rA;
		return 1;
	case 0x77:
		cpu.rHL = cpu.rA;
		return 1;
	case 0xEA:
		TO_USHORT(TranslateAddress(CHARS_TO_SHORT(programCode[1], programCode[2]))) = cpu.rA;
		return 3;
	case 0xF2: // LD A,(C)
		cpu.rA = TO_UCHAR(TranslateAddress(0xFF00 + cpu.rC));
		return 1;
	case 0xE2: // LD (C),A
		TO_UCHAR(TranslateAddress(0xFF00 + cpu.rC)) = cpu.rA;
		return 1;
		// LD A,(HLD) same as LD A,(HL-) same as LDD A, (HL)
		// LDD A,(HL)
	case 0x3A:
		cpu.rA = cpu.rHL;
		return 1;
		// LD (HLD),A same as LD (HL-),A same as LDD (HL), A
		// LDD (HL),A
	case 0x32:
		cpu.rHL = cpu.rA - 1;
		return 1;
		// LD A,(HLI) same as LD A,(HL+) same as LDI A,(HL)
		// LDI A,(HL)
	case 0x2A:
		cpu.rA = cpu.rHL++;
		return 1;
		// LD (HLI),A same as LD (HL+),A same as LDI (HL),A
		// LDI (HL),A
	case 0x22:
		cpu.rHL = cpu.rA + 1;
		return 1;

		// LD (n),A --> n is one byte immediate value
	case 0xE0:
		TO_UCHAR(TranslateAddress(0xFF00 + programCode[1])) = cpu.rA;
		return 2;
		// LD A,(n) --> n is one byte immediate value
	case 0xF0:
		cpu.rA = TO_UCHAR(TranslateAddress(0xFF00 + programCode[1]));
		return 2;
#pragma endregion

#pragma region 16 bit loads
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

#pragma endregion

#pragma region 8 bit ALU
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
		return 0;
	case 0xC6:
		return 1;

		// ADC A,n --> n is a register or #
	case 0x8F:
	case 0x88:
	case 0x89:
	case 0x8A:
	case 0x8B:
	case 0x8C:
	case 0x8D:
	case 0x8E:
		return 0;
	case 0xCE:
		return 1;

		// SUB n --> n is a register or #
	case 0x97:
	case 0x90:
	case 0x91:
	case 0x92:
	case 0x93:
	case 0x94:
	case 0x95:
	case 0x96:
		return 0;
	case 0xD6:
		return 1;

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
		return 0;
	case 0xE6:
		return 1;

		// OR n --> n is a register or #
	case 0xB7:
	case 0xB0:
	case 0xB1:
	case 0xB2:
	case 0xB3:
	case 0xB4:
	case 0xB5:
	case 0xB6:
		return 0;
	case 0xF6:
		return 1;

		// XOR n -- n is a register or #
	case 0xAF:
	case 0xA8:
	case 0xA9:
	case 0xAA:
	case 0xAB:
	case 0xAC:
	case 0xAD:
	case 0xAE:
		return 0;
	case 0xEE:
		return 1;

		// CP n --> n is a register or #
	case 0xBF:
	case 0xB8:
	case 0xB9:
	case 0xBA:
	case 0xBB:
	case 0xBC:
	case 0xBD:
	case 0xBE:
		return 0;
	case 0xFE:
		return 1;

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
#pragma endregion

#pragma region 16 bit ALU
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

#pragma endregion

#pragma region Miscellaneous
		//////// Miscellaneous ////////
		// SWAP n --> n is a register
	case 0xCB37:
	case 0xCB30:
	case 0xCB31:
	case 0xCB32:
	case 0xCB33:
	case 0xCB34:
	case 0xCB35:
	case 0xCB36:
		// DAA
	case 0x27:
		// CPL
	case 0x2F:
		// CCF
	case 0x3F:
		// SCF
	case 0x37:
		// NOP
	case 0x00:
		// HALT
	case 0x76:
		// STOP
	case 0x1000:
		// DI
	case 0xF3:
		// EI
	case 0xFB:
		return 0;
#pragma endregion

#pragma region Rotates and Shifts
		//////// Rotates and Shifts ////////
		// RLCA
	case 0x07:
		// RLA
	case 0x17:
		// RRCA
	case 0x0F:
		// RRA
	case 0x1F:
		// RLC n --> n is a register
	case 0xCB07:
	case 0xCB00:
	case 0xCB01:
	case 0xCB02:
	case 0xCB03:
	case 0xCB04:
	case 0xCB05:
	case 0xCB06:
		// RL n --> n is a register
	case 0xCB17:
	case 0xCB10:
	case 0xCB11:
	case 0xCB12:
	case 0xCB13:
	case 0xCB14:
	case 0xCB15:
	case 0xCB16:
		// RRC n --> n is a register
	case 0xCB0F:
	case 0xCB08:
	case 0xCB09:
	case 0xCB0A:
	case 0xCB0B:
	case 0xCB0C:
	case 0xCB0D:
	case 0xCB0E:
		// RR n --> n is a register
	case 0xCB1F:
	case 0xCB18:
	case 0xCB19:
	case 0xCB1A:
	case 0xCB1B:
	case 0xCB1C:
	case 0xCB1D:
	case 0xCB1E:
		// SLA n --> n is a register
	case 0xCB27:
	case 0xCB20:
	case 0xCB21:
	case 0xCB22:
	case 0xCB23:
	case 0xCB24:
	case 0xCB25:
	case 0xCB26:
		// SRA n --> n is a register
	case 0xCB2F:
	case 0xCB28:
	case 0xCB29:
	case 0xCB2A:
	case 0xCB2B:
	case 0xCB2C:
	case 0xCB2D:
	case 0xCB2E:
		// SRL n --> n is a register
	case 0xCB3F:
	case 0xCB38:
	case 0xCB39:
	case 0xCB3A:
	case 0xCB3B:
	case 0xCB3C:
	case 0xCB3D:
	case 0xCB3E:
		return 0;
#pragma endregion

#pragma region Bit Opcodes
		//////// Bit Opcodes ////////
		// BIT b,r --> b is a byte, r is a register
	case 0xCB47:
	case 0xCB40:
	case 0xCB41:
	case 0xCB42:
	case 0xCB43:
	case 0xCB44:
	case 0xCB45:
	case 0xCB46:
		return 1;

		// SET b,r --> b is a byte, r is a register
	case 0xCBC7:
	case 0xCBC0:
	case 0xCBC1:
	case 0xCBC2:
	case 0xCBC3:
	case 0xCBC4:
	case 0xCBC5:
	case 0xCBC6:
		return 1;

		// RES b,r --> b is a byte, r is a register
	case 0xCB87:
	case 0xCB80:
	case 0xCB81:
	case 0xCB82:
	case 0xCB83:
	case 0xCB84:
	case 0xCB85:
	case 0xCB86:
		return 1;

#pragma endregion

#pragma region Jumps
		//////// Jumps ////////
		// JP nn --> nn is a 2 byte immediate value (LS byte first)
	case 0xC3:
		return 2;

		// JP cc,nn --> nn is a 2 byte immediate value (LS byte first)
	case 0xC2:
	case 0xCA:
	case 0xD2:
	case 0xDA:
		return 2;

		// JP (HL)
	case 0xE9:
		return 0;

		// JR n --> n is one byte signed immediate value
	case 0x18:
		return 1;

		// JR cc,n --> n is one byte signed immediate value
	case 0x20:
	case 0x28:
	case 0x30:
	case 0x38:
		return 1;

#pragma endregion

#pragma region Calls
		//////// Calls ////////
		// CALL nn --> nn is 2 byte immediate value (LS byte first)
	case 0xCD:
		return 2;

		// CALL cc,nn --> nn is 2 byte immediate value (LS byte first)
	case 0xC4:
	case 0xCC:
	case 0xD4:
	case 0xDC:
		return 2;
#pragma endregion

#pragma region Restarts
		//////// Restarts ////////
		// RST n --> n is a restart address
	case 0xC7:
	case 0xCF:
	case 0xD7:
	case 0xDF:
	case 0xE7:
	case 0xEF:
	case 0xF7:
	case 0xFF:
		return 0;

#pragma endregion

#pragma region Returns
		//////// Returns ////////
		// RET
	case 0xc9:
		// RET cc
	case 0xC0:
	case 0xC8:
	case 0xD0:
	case 0xD8:
		// RETI
	case 0xD9:
		return 0;
#pragma endregion
	}
}