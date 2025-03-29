#include <stdio.h>

#include "m_argv.h"
#include "doomgeneric.h"
#include "system.h"

pixel_t* DG_ScreenBuffer = NULL;

void M_FindResponseFile(void);
void D_DoomMain (void);


void doomgeneric_Create(int argc, char **argv)
{
	// save arguments
    myargc = argc;
    myargv = argv;

	M_FindResponseFile();

#ifdef PLATFORM_RISCV_BARE
	DG_ScreenBuffer = (pixel_t*)(DISP_VRAM_ADDR);
#else
	DG_ScreenBuffer = malloc(DOOMGENERIC_RESX * DOOMGENERIC_RESY * 4);
#endif

	DG_Init();

	D_DoomMain ();
}

