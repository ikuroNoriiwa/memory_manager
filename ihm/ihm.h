#ifndef _IHM_H
#define _IHM_H

#include <ncurses.h>
#include "../structs.h"

	void initAllColor();
	void affichMain();
	void affichMenuTopCPU(WINDOW *menu);
	int afficherCPU(WINDOW *haut, WINDOW *graph, WINDOW *ram);
	void affichRam(WINDOW *ram, DefMemory *memory, int posy);
	void affichMenuRam(WINDOW *ram);
	void affichCPU_core(WINDOW *cpu[], WINDOW *ram);
#endif
