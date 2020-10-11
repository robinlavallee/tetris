#include <windows.h>
#include <ddraw.h>
#include "font.h"


BOOL DisplayString(IDirectDrawSurface *pdds, LPCSTR szString, int x, int y)
{
	HDC hdc;

	// this use the windows GDI functions...
	
	if (pdds->GetDC(&hdc) != DD_OK)
		return FALSE;
	
	TextOut(hdc, x, y, szString, lstrlen(szString));

	if (pdds->ReleaseDC(hdc) != DD_OK)
		return FALSE;
	
	return TRUE;
}