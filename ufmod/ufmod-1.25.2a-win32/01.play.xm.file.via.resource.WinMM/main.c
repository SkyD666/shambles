/*
 * main.c
 * 2011 (c) maracuja/ZUUL
 */

#include "resource.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
/* uFMOD (WINMM) */
#include "ufmod.h"


int main(int argc, char *argv[])
{

	/* Start playback */
	if (uFMOD_PlaySong(MAKEINTRESOURCE(CHIPTUNE_MUS), 0, XM_RESOURCE)){

		printf("Press any key to quit\n");
		{
			char key = 0;

			do
			{
				if (kbhit()) {
					key = getch();
				}
			} while (key != 27);

		}

		/* Stop playback */
		uFMOD_StopSong();
		return EXIT_FAILURE;
	}
	printf("Can't initialize the ufmod lib\n");
	return EXIT_FAILURE;

}
