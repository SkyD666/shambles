/*
   The following example shows how to load OPENAL API at runtime,
   not using an import library. This way, it is able to run when
   OpenAL32.DLL is not installed.
*/

/* However, if you do want to use static importing, just uncomment
   the following line: */
// #define OPENAL_STATIC

/* Enable Unicode for optimal NT/XP performance */
// #define UNICODE

#ifdef UNICODE
	typedef unsigned short CHR;
#else
	typedef unsigned char CHR;
#endif

#include <windows.h>
#include "oalufmod.h"

/* Let's embed the XM file right inside the data section. */
unsigned char xm[905] = {
     0x45,0x78,0x74,0x65,0x6E,0x64,0x65,0x64,0x20,0x4D,0x6F,0x64,0x75,0x6C,0x65,0x3A,
     0x20,0x73,0x6F,0x66,0x74,0x20,0x6D,0x61,0x6E,0x69,0x61,0x63,0x2D,0x6D,0x69,0x6E,
     0x69,0x6D,0x61,0x6C,0x00,0x1A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x01,0x34,0x00,0x00,0x00,
     0x20,0x00,0x00,0x00,0x02,0x00,0x0D,0x00,0x01,0x00,0x01,0x00,0x0A,0x00,0x91,0x00,
     0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
     0x08,0x09,0x0A,0x0B,0x08,0x09,0x0C,0x0B,0x08,0x09,0x0A,0x0B,0x08,0x09,0x0C,0x0B,
     0x09,0x00,0x00,0x00,0x00,0x04,0x00,0x01,0x00,0x83,0x16,0x01,0x80,0x80,0x2E,0x01,
     0x00,0x0E,0x60,0x80,0x3A,0x01,0x00,0x0E,0x62,0x81,0x61,0x83,0x35,0x01,0x09,0x00,
     0x00,0x00,0x00,0x04,0x00,0x01,0x00,0x83,0x16,0x01,0x80,0x80,0x2E,0x01,0x00,0x0E,
     0x60,0x80,0x35,0x01,0x00,0x0E,0x62,0x81,0x61,0x83,0x38,0x01,0x09,0x00,0x00,0x00,
     0x00,0x04,0x00,0x01,0x00,0x83,0x16,0x01,0x80,0x80,0x2E,0x01,0x00,0x0E,0x60,0x80,
     0x38,0x01,0x00,0x0E,0x62,0x80,0x83,0x33,0x01,0x09,0x00,0x00,0x00,0x00,0x06,0x00,
     0x01,0x00,0x83,0x16,0x01,0x80,0x80,0x2E,0x01,0x00,0x0E,0x60,0x80,0x33,0x01,0x00,
     0x0E,0x61,0x81,0x61,0x83,0x35,0x01,0x83,0x0D,0x01,0x83,0x36,0x01,0x80,0x83,0x36,
     0x01,0x09,0x00,0x00,0x00,0x00,0x04,0x00,0x01,0x00,0x83,0x0F,0x01,0x80,0x80,0x2E,
     0x01,0x00,0x0E,0x60,0x80,0x36,0x01,0x00,0x0E,0x62,0x81,0x61,0x83,0x33,0x01,0x09,
     0x00,0x00,0x00,0x00,0x06,0x00,0x01,0x00,0x83,0x0F,0x01,0x80,0x80,0x2E,0x01,0x00,
     0x0E,0x60,0x80,0x33,0x01,0x00,0x0E,0x61,0x81,0x61,0x83,0x2E,0x01,0x83,0x12,0x01,
     0x83,0x33,0x01,0x80,0x83,0x35,0x01,0x09,0x00,0x00,0x00,0x00,0x06,0x00,0x01,0x00,
     0x83,0x16,0x01,0x80,0x80,0x2E,0x01,0x00,0x0E,0x60,0x80,0x35,0x01,0x00,0x0E,0x61,
     0x81,0x61,0x83,0x2E,0x01,0x83,0x0D,0x01,0x83,0x31,0x01,0x80,0x83,0x2E,0x01,0x09,
     0x00,0x00,0x00,0x00,0x08,0x00,0x01,0x00,0x83,0x12,0x01,0x98,0x0A,0x01,0x83,0x19,
     0x01,0x88,0x0A,0x83,0x1E,0x01,0x81,0x61,0x83,0x12,0x01,0x80,0x83,0x14,0x01,0x80,
     0x83,0x1B,0x01,0x80,0x83,0x20,0x01,0x80,0x83,0x14,0x01,0x80,0x09,0x00,0x00,0x00,
     0x00,0x08,0x00,0x01,0x00,0x83,0x12,0x01,0x81,0x61,0x83,0x19,0x01,0x80,0x83,0x1E,
     0x01,0x80,0x83,0x12,0x01,0x80,0x83,0x19,0x01,0x83,0x31,0x01,0x83,0x1E,0x01,0x80,
     0x83,0x12,0x01,0x83,0x31,0x01,0x83,0x19,0x01,0x80,0x09,0x00,0x00,0x00,0x00,0x08,
     0x00,0x01,0x00,0x83,0x14,0x01,0x83,0x33,0x01,0x83,0x1B,0x01,0x80,0x83,0x20,0x01,
     0x83,0x31,0x01,0x83,0x14,0x01,0x80,0x83,0x1B,0x01,0x83,0x30,0x01,0x83,0x20,0x01,
     0x80,0x83,0x14,0x01,0x83,0x31,0x01,0x83,0x1B,0x01,0x80,0x09,0x00,0x00,0x00,0x00,
     0x08,0x00,0x01,0x00,0x83,0x16,0x01,0x83,0x30,0x01,0x83,0x1D,0x01,0x83,0x31,0x01,
     0x83,0x22,0x01,0x83,0x35,0x01,0x83,0x16,0x01,0x98,0x0A,0x01,0x83,0x1D,0x01,0x88,
     0x0A,0x83,0x22,0x01,0x81,0x61,0x83,0x16,0x01,0x80,0x83,0x1D,0x01,0x80,0x09,0x00,
     0x00,0x00,0x00,0x08,0x00,0x01,0x00,0x83,0x16,0x01,0x80,0x83,0x1D,0x01,0x80,0x83,
     0x22,0x01,0x80,0x83,0x16,0x01,0x80,0x83,0x18,0x01,0x80,0x83,0x1D,0x01,0x80,0x83,
     0x11,0x01,0x80,0x83,0x18,0x01,0x80,0x09,0x00,0x00,0x00,0x00,0x08,0x00,0x01,0x00,
     0x83,0x16,0x01,0x83,0x30,0x01,0x83,0x1D,0x01,0x83,0x31,0x01,0x83,0x19,0x01,0x83,
     0x2E,0x01,0x83,0x16,0x01,0x98,0x0A,0x01,0x83,0x1D,0x01,0x88,0x0A,0x83,0x19,0x01,
     0x81,0x61,0x83,0x16,0x01,0x80,0x83,0x1D,0x01,0x80,0xF1,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x27,0x01,0x00,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x08,
     0x00,0x2C,0x00,0x0E,0x00,0x08,0x00,0x18,0x00,0x16,0x00,0x20,0x00,0x08,0x00,0x2D,
     0x00,0x0D,0x00,0x32,0x00,0x04,0x00,0x3C,0x00,0x07,0x00,0x44,0x00,0x04,0x00,0x5A,
     0x00,0x00,0x00,0x64,0x00,0x00,0x00,0x6E,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x0A,
     0x00,0x28,0x00,0x1E,0x00,0x18,0x00,0x32,0x00,0x20,0x00,0x3C,0x00,0x20,0x00,0x46,
     0x00,0x20,0x00,0x50,0x00,0x20,0x00,0x5A,0x00,0x20,0x00,0x64,0x00,0x20,0x00,0x6E,
     0x00,0x20,0x00,0x78,0x00,0x20,0x00,0x82,0x00,0x20,0x00,0x09,0x06,0x01,0x02,0x04,
     0x02,0x03,0x05,0x01,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x0C,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x40,0x00,0x01,0x80,0xF9,0x00,0xBF,0x00,0xC3,
     0x00,0x0A,0x00,0x57,0x00,0x6E,0x00,0x23,0x00
   };

/* OpenAL32.DLL symbols */

#ifdef OPENAL_STATIC
	#pragma comment(lib, "openal32.lib")

	int   __cdecl alGetError();
	void* __cdecl alcOpenDevice(char*);
	void* __cdecl alcCreateContext(void*, char*);
	void  __cdecl alcMakeContextCurrent(void*);
	void  __cdecl alGenSources(int, void*);
	void  __cdecl alcDestroyContext(void*);
	void  __cdecl alcCloseDevice(void*);

#else
	/* Link to OpenAL dynamically at run time. */

	typedef void* (__cdecl *LPOPENALFUNC_ARG0)();
	typedef void* (__cdecl *LPOPENALFUNC_ARG1)(void*);
	typedef void* (__cdecl *LPOPENALFUNC_ARG2)(void*, char*);
	typedef void  (__cdecl *LPOPENALFUNC_ARGI)(int, void*);

	LPOPENALFUNC_ARG0 _imp__alGetError;
	LPOPENALFUNC_ARG1 _imp__alcOpenDevice;
	LPOPENALFUNC_ARG2 _imp__alcCreateContext;
	LPOPENALFUNC_ARG1 _imp__alcMakeContextCurrent;
	LPOPENALFUNC_ARGI _imp__alGenSources;
	LPOPENALFUNC_ARG1 _imp__alcDestroyContext;
	LPOPENALFUNC_ARG1 _imp__alcCloseDevice;
	#define alGetError()               _imp__alGetError()
	#define alcOpenDevice(op1)         _imp__alcOpenDevice(op1)
	#define alcCreateContext(op1, op2) _imp__alcCreateContext(op1, op2)
	#define alcMakeContextCurrent(op1) _imp__alcMakeContextCurrent(op1)
	#define alGenSources(op1, op2)     _imp__alGenSources(op1, op2)
	#define alcDestroyContext(op1)     _imp__alcDestroyContext(op1)
	#define alcCloseDevice(op1)        _imp__alcCloseDevice(op1)
	void *_imp__alBufferData,
	     *_imp__alDeleteBuffers,
	     *_imp__alGenBuffers,
	     *_imp__alGetSourcei,
	     *_imp__alSourcei,
	     *_imp__alSourcePlay,
	     *_imp__alSourceQueueBuffers,
	     *_imp__alSourceStop,
	     *_imp__alSourceUnqueueBuffers;

	typedef struct{
		const char *pubname;
		void *f;
	}IAT_NODE;
	IAT_NODE OPENAL32[] = {
		{ "alBufferData",           &_imp__alBufferData },
		{ "alDeleteBuffers",        &_imp__alDeleteBuffers },
		{ "alGenBuffers",           &_imp__alGenBuffers },
		{ "alGetError",             &_imp__alGetError },
		{ "alGetSourcei",           &_imp__alGetSourcei },
		{ "alSourcei",              &_imp__alSourcei },
		{ "alSourcePlay",           &_imp__alSourcePlay },
		{ "alSourceQueueBuffers",   &_imp__alSourceQueueBuffers },
		{ "alSourceStop",           &_imp__alSourceStop },
		{ "alSourceUnqueueBuffers", &_imp__alSourceUnqueueBuffers },
		{ "alcOpenDevice",          &_imp__alcOpenDevice },
		{ "alcCreateContext",       &_imp__alcCreateContext },
		{ "alcMakeContextCurrent",  &_imp__alcMakeContextCurrent },
		{ "alGenSources",           &_imp__alGenSources },
		{ "alcDestroyContext",      &_imp__alcDestroyContext },
		{ "alcCloseDevice",         &_imp__alcCloseDevice }
	};

	/* Load OPENAL32.DLL and resolve thunk symbols. */
	const CHR szOAL[]  = { 'O','P','E','N','A','L','3','2',0 };
	const CHR szErr0[] = { 'F','a','i','l','e','d',' ','t','o',' ',
	                       'l','o','a','d',' ','O','P','E','N','A','L','3','2',0 };
	int LoadOpenAL(){
	int i;
	void *addr;
	HANDLE hLibOpenAL = LoadLibrary(szOAL);
		if(!hLibOpenAL) return 0;
		for(i = 0; i < sizeof(OPENAL32)/sizeof(IAT_NODE); i++){
			addr = GetProcAddress(hLibOpenAL,OPENAL32[i].pubname);
			*((void**)OPENAL32[i].f) = addr;
			if(!addr) return 0;
		}
		return 1; /* OK */
	}

#endif

const CHR szErr1[] = { 'C','o','u','l','d',' ','n','o','t',' ','o','p','e','n',' ',
                       't','h','e',' ','d','e','f','a','u','l','t',' ',
                       'O','p','e','n','A','L',' ','d','e','v','i','c','e',0 };
const CHR szErr2[] = { 'O','p','e','n','A','L',' ','e','r','r','o','r',0 };
const CHR szMsg[]  = { 'u','F','M','O','D',' ','r','u','l','e','Z','!',0 };
const CHR szTtl[]  = { 'C',0 };

void start(void){
void *OAL_device = 0, *OAL_context = 0;
unsigned int OAL_source = 0;

	/* Load OpenAL. */
	#ifndef OPENAL_STATIC
		if(!LoadOpenAL()){
			/* Failed to load OpenAL DLL. */
			MessageBox(0, szErr0, 0, MB_ICONSTOP);
			ExitProcess(0);
		}
	#endif

	/* Init OpenAL. */
	if( !(OAL_device = alcOpenDevice(0)) )
		MessageBox(0, szErr1, 0, MB_ICONSTOP);
	else{

		/* Create a context and make it current. */
		OAL_context = alcCreateContext(OAL_device, 0);
		alcMakeContextCurrent(OAL_context);
		/* Generate 1 source for playback. */
		alGenSources(1, &OAL_source);

		/* Start playback if no error so far. */
		if(alGetError() ||
			!uFMOD_OALPlaySong(xm, (void*)sizeof(xm), XM_MEMORY, OAL_source))
			MessageBox(0, szErr2, 0, MB_ICONSTOP);
		else{

			/* Wait for user input. */
			MessageBox(0, szMsg, szTtl, 0);

			/* Stop playback. */
			uFMOD_StopSong();
		}

		/* Release the current context and destroy it (the source gets destroyed as well). */
		alcMakeContextCurrent(0);
		alcDestroyContext(OAL_context);
	}
	/* Close the actual device. */
	alcCloseDevice(OAL_device);
	ExitProcess(0);
}
