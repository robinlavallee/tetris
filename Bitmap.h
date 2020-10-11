#ifndef _BITMAP_H_
#define _BITMAP_H_

BOOL LoadDisplayBitmap(IDirectDrawSurface *pdds, int dx, int dy, LPCSTR szBitmap);
IDirectDrawSurface * LoadBitmapIntoSurface(IDirectDraw2 *pdd, int sx, int sy, int dx, int dy, LPCSTR szBitmap);
BOOL CopyBitmapToSurface(IDirectDrawSurface *lpDDS, int x, int y, int xwidth, int yheight, HBITMAP hbm, int dx, int dy);

#endif // _BITMAP_H_