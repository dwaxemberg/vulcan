
typedef struct _GB_CPU {
	unsigned char rA;
	unsigned char rF;

	unsigned char rB;
	unsigned char rC;

	unsigned char rD;
	unsigned char rE;

	unsigned char rH;
	unsigned char rL;

	unsigned short rPC;
	unsigned short rSP;
} GB_CPU, *PGB_CPU;