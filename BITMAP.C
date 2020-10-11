/*
 * bitmap.c
 * This file contains bitmap functiom
 *
 *
 *
 */

#include <windows.h>
#include <ddraw.h>
#include "bitmap.h"

BOOL LoadDisplayBitmap(IDirectDrawSurface *pdds, LPCSTR szBitmap)
{
	// Pretty simple function. Get a bitmap, and display it from the left-top corner.
	// It doesn't do any checking to see of the bitmap is bigger than the screen or anything of that
	// sort. This need to be added. (TODO)

	HBITMAP		hbm;
	BITMAP		bitmap;
	HDC			hdc;
	HDC			hdcimage;

	hbm = (HBITMAP)LoadImage(NULL, "love.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbm == NULL)
		return FALSE;

	
	// Create a compatible DC to hold the loaded bitmap.

	hdcimage = CreateCompatibleDC(NULL);
	if (hdcimage == NULL)
		return FALSE;

	if (SelectObject(hdcimage, (HGDIOBJ) hbm) == NULL)
		return FALSE;
	
	// Get the size of the bitmap

	GetObject((HGDIOBJ) hdcimage, sizeof(bitmap), &bitmap);
	
	
	// Lock the back buffer.
	
	result = pdds->GetDC(&hdc);
	if (result != DD_OK)
		return FALSE;
	
	// copy the bitmap

	BitBlt(hdc, 0, 0, bitmap.height, bitmap.width, hdcimage, 0, 0, SRCCOPY);

	// unlock the backbuffer
	
	result = lpDDSBack->ReleaseDC(hdc);

}

