#include <windows.h>
#include <dsound.h>
#include "sound.h"

IDirectSoundBuffer * InitSound(HWND hwnd, LPDIRECTSOUND lpDS)
{
	// this function inits everything and return the PrimaryBuffer
	
	HRESULT hr;
	DSBUFFERDESC dsbdesc;
	LPDIRECTSOUNDBUFFER dsb;
	PCMWAVEFORMAT pcm;

	hr = DirectSoundCreate(NULL, &lpDS, NULL);
	if (hr != DS_OK)
		return NULL;

	if (lpDS->SetCooperativeLevel(hwnd, DSSCL_NORMAL) != DS_OK)
		return NULL;

	// Create the primary buffer...
	
	
	ZeroMemory(&pcm, sizeof(pcm));
	pcm.wf.wFormatTag = WAVE_FORMAT_PCM;
	pcm.wf.nChannels = 2;
    pcm.wf.nSamplesPerSec = 22050;
    pcm.wf.nBlockAlign = 4;
    pcm.wf.nAvgBytesPerSec = pcm.wf.nSamplesPerSec * pcm.wf.nBlockAlign;
    pcm.wBitsPerSample = 16;

	ZeroMemory(&dsbdesc, sizeof(dsb));
	dsbdesc.dwSize = sizeof(dsb);
	dsbdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsbdesc.dwBufferBytes = 0;
	dsbdesc.dwReserved = 0;
    dsbdesc.lpwfxFormat = (LPWAVEFORMATEX)&pcm;
	
	if (lpDS->CreateSoundBuffer(&dsbdesc, &dsb, NULL) != DS_OK)
		return NULL;

	return dsb;

}

IDirectSoundBuffer *LoadWAVIntoBuffer(LPDIRECTSOUND lpDS, LPCSTR szFilename)
{
    DSBUFFERDESC dsbdesc;
	LPDIRECTSOUNDBUFFER dsb;
	PCMWAVEFORMAT pcm;
	int lenght;

	// Wave structure

	ZeroMemory(&pcm, sizeof(pcm));
	pcm.wf.wFormatTag = WAVE_FORMAT_PCM;
	pcm.wf.nChannels = 2;
    pcm.wf.nSamplesPerSec = 22050;
    pcm.wf.nBlockAlign = 4;
    pcm.wf.nAvgBytesPerSec = pcm.wf.nSamplesPerSec * pcm.wf.nBlockAlign;
    pcm.wBitsPerSample = 16;


	ZeroMemory(&dsbdesc, sizeof(dsb));
	dsbdesc.dwSize = sizeof(dsb);
	dsbdesc.dwFlags = DSBCAPS_STATIC;
	dsbdesc.dwReserved = 0;
	
	dsbdesc.dwBufferBytes = lenght * pcm.wf.nAvgBytesPerSec; 
    dsbdesc.lpwfxFormat = (LPWAVEFORMATEX)&pcm;

	if (lpDS->CreateSoundBuffer(&dsbdesc, &dsb, NULL) != DS_OK)
		return NULL;



	return dsb;
}

BOOL PlaySound(int sound)
{
	return TRUE;
}

BOOL DeInitSound()
{

	return TRUE;
}