#ifndef _SOUND_H_
#define _SOUND_H_

IDirectSoundBuffer * InitSound(LPDIRECTSOUND ppDS);

IDirectSoundBuffer * LoadWAVIntoBuffer(LPDIRECTSOUND lpDS, LPCSTR szFilename);
// This was something I created.... forget it (the LoadWAVIntoBuffer)

BOOL PlaySound(int sound);
BOOL DeInitSound(void);

#endif // _SOUND_H_