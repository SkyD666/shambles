#include "resource.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

int FC_Initialize(bool inMem, void* pMusicBuffer, int inMemSize, char* filename);
int FC_StartPlayer();
int FC_StopPlayer();

#ifdef __cplusplus
};
#endif

int main(int argc, char *argv[])
{
    HRSRC res = NULL;
    HGLOBAL hglobal = NULL;
    LPVOID musicbuffer = NULL;
    DWORD musicbufferlength = 0;


	printf("tiny Future Composer library replayer v.0.97\nby SLiPPY/VeCTRONiX! rel. 10/04/2007\n");
	printf("=====================================\n");


    res = FindResource(NULL, MAKEINTRESOURCE(CHIPTUNE_MUS), RT_RCDATA);

    if (res == NULL)
        return EXIT_FAILURE;

    musicbufferlength = SizeofResource(NULL, res);

    if (musicbufferlength == 0)
        return EXIT_FAILURE;

    hglobal = LoadResource(NULL, res);

    if (hglobal == NULL)
        return EXIT_FAILURE;


    musicbuffer = LockResource(hglobal);

    if (musicbuffer == NULL)
        return EXIT_FAILURE;


	FC_Initialize(true, musicbuffer, musicbufferlength, NULL);
	FC_StartPlayer();

	{
	    char key = 0;
	    do
	    {
	        if (kbhit())
	        {
	            key = getch();
	        }
	        Sleep(10);
	    } while (key != 27);
	}

	FC_StopPlayer();

	return EXIT_SUCCESS;
}

