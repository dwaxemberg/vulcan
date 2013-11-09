
typedef struct _GB_CPU {
	union {
		struct {
			unsigned char rA;
			unsigned char rF;
		};
		unsigned short rAF;
	};

	union {
		struct {
			unsigned char rB;
			unsigned char rC;
		};
		unsigned short rBC;
	};

	union {
		struct {
			unsigned char rD;
			unsigned char rE;
		};
		unsigned short rDE;
	};

	union {
		struct {
			unsigned char rH;
			unsigned char rL;
		};
		unsigned short rHL;
	};

	unsigned short rPC;
	unsigned short rSP;
} GB_CPU, *PGB_CPU;