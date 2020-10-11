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

BOOL LoadDisplayBitmap(IDirectDrawSurface2 *pdds, int dx, int dy, LPCSTR szBitmap)
{
	// Pretty simple function. Get a bitmap, and display it at dx, dy.
	// It doesn't do any checking to see of the bitmap is bigger than the screen or anything of that
	// sort. This need to be added. (TODO)

	HBITMAP		hbm;
	BITMAP		bitmap;
	HDC			hdc;
	HDC			hdcimage;
	HRESULT		result;

	hbm = (HBITMAP)LoadImage(NULL, szBitmap, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbm == NULL)
		return FALSE;

	
	// Create a compatible DC to hold the loaded bitmap.

	hdcimage = CreateCompatibleDC(NULL);
	if (hdcimage == NULL)
		return FALSE;

	if (SelectObject(hdcimage, (HGDIOBJ) hbm) == NULL)
		return FALSE;
	
	// Get the size of the bitmap

	result = GetObject(hbm, sizeof(bitmap), &bitmap);
	if (result == 0)
		return FALSE;
	
	// Lock the back buffer.
	
	result = pdds->GetDC(&hdc);
	if (result != DD_OK)
		return FALSE;
	
	// copy the bitmap

	BitBlt(hdc, dx, dy, bitmap.bmWidth, bitmap.bmHeight, hdcimage, 0, 0, SRCCOPY);

	// unlock the backbuffer
	
	result = pdds->ReleaseDC(hdc);
	DeleteDC(hdcimage);
	return TRUE;

}

IDirectDrawSurface * LoadBitmapIntoSurface(IDirectDraw2 *pdd, int sx, int sy, int dx, int dy, LPCSTR szBitmap)
{
	// pdds is the surface
	// sx, sy is the top left corner
	// dx, dy are the width and height of the bitmap
	// szBitmap is the filename of the bitmap

	HBITMAP				hbm;
	BITMAP				bm;
    DDSURFACEDESC       ddsd;
    IDirectDrawSurface	*pdds;
	HDC					hdc;
	HDC					newhdc;

	hbm = (HBITMAP)LoadImage(NULL, szBitmap, IMAGE_BITMAP, sx, sy, LR_LOADFROMFILE); // Load the bmp from the file
	if (hbm == NULL)
		return NULL;
	
	if (GetObject(hbm, sizeof(bm), &bm) == 0)
		return NULL;

    ZeroMemory(&ddsd, sizeof(ddsd)); // Prepare the creation of a new surface.
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth = bm.bmWidth;
    ddsd.dwHeight = bm.bmHeight;

    if (pdd->CreateSurface(&ddsd, &pdds, NULL) != DD_OK) // Create the surface
        return NULL;

	newhdc = CreateCompatibleDC(NULL); // Create a copy the bitmap into the DC
	if (newhdc == NULL)
		return NULL;
	if (SelectObject(newhdc, hbm) == NULL)
		return NULL;
	
	pdds->GetDC(&hdc); // Lock it to copy the bmp

	if (BitBlt(hdc, 0, 0, dx, dy, newhdc, 0, 0, SRCCOPY) == FALSE) // copy the bitmap
		return NULL;
	
	pdds->ReleaseDC(hdc); // unlock

	DeleteDC(newhdc);

	return pdds;

}

BOOL CopyBitmapToSurface(IDirectDrawSurface *lpDDS, int x, int y, int xwidth, int yheight, HBITMAP hbm, int dx, int dy)
{
	HDC hdc; // this will be the destination hdc
	HDC hdcimage; // this is our bitmap
	HRESULT hr; // result
	
	hdcimage = CreateCompatibleDC(NULL);
	if (hdcimage == NULL)
		return FALSE;

	SelectObject(hdcimage, hbm); // select the bitmap into the Device context
	
	// ready to copy I think... lock surface

	hr = lpDDS->GetDC(&hdc);
	if (hr != DD_OK)
		return FALSE;

	// blit it

	BitBlt(hdc, x, y, xwidth, yheight, hdcimage, dx, dy, SRCCOPY);
	lpDDS->ReleaseDC(hdc);

	// delete the useless dc

	DeleteDC(hdcimage);

	return TRUE;

}