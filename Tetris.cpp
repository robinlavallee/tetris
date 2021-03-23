/* Extreme big change.. instead of that long copy pasting stuff I've used...
 *We'll now be using.... STRUCTURE!!! :) Although, the colors of the block are 
 *going to be hard coded, they can be easily changed by changing the define.
 *So.. each structure is going to be a 4x4 square.. something like...
 *
 *[ ][X][ ][ ]
 *[ ][X][ ][ ]
 *[ ][X][ ][ ]
 *[ ][X][ ][ ]
 *
 *[ ][ ][ ][ ]
 *[X][X][X][X]
 *[ ][ ][ ][ ]
 *[ ][ ][ ][ ]
 *
 *
 *This structure can be found in tetris.h
 *
 *These fuctions are going to be added (those with an [X] preceding them mean they have been coded and work)
 *
 *[X]DisplayBlock(int x, int y, int flag, int color);
 *
 *Ok, easy, if flag == RELATIVE, then x, y is relative to the game coor (x=0, y=0 being the top left)
 *if flag == ABSOLUTE, then x, y is relative to the screen (x=0, y=0 being the top left of the screen)
 *in 640x480, the lower right corner is (x=31, y=23)
 *color is just the color... RED, YELLOW, PINK, BLUE, GREEN_BLUE, GREEN, BROWN.
 *
 *[X]CheckDown This one has to be changed.
 *[X]CheckRight This one has to be changed.
 *[X]CheckLeft This one has to be changed.
 *[X]StopBlock This one has to be changed.
 *[X]ReDisplayScreen This one has to be changed.
 *
 *[ ]DisplayString (just for number currently, 0-9)
 *[ ]PlaySound (a fuction to play sound with define)
 * And some other little changes.
 *
 *[ ]Next block...
 *[ ]Be able to record! :) (the file format will be in record.cpp)
 *... OpenRecord, CloseRecord, WriteRecord, Play, Read, stop, pause, etc.
 */
 
#include <windows.h>
#include "resource.h"
#include <windowsx.h>
#include <dsound.h>
#include <ddraw.h>
#include <mmsystem.h>
#include <time.h>
#include <stdio.h>
#include "tetris.h"
#include "bitmap.h"
#include "sound.h"
#include "font.h"
#include "dsutil.h"

#include <vector>

HRESULT					result;         // global variable

LPDIRECTDRAW            lpDD;           // DirectDraw object
LPDIRECTDRAW2           lpDD2;           // DirectDraw object
LPDIRECTDRAWSURFACE		lpDDSPrimary;   // DirectDraw primary surface
LPDIRECTDRAWSURFACE		lpDDSBack;      // DirectDraw back surface
LPDIRECTDRAWSURFACE		lpDDSBackground; // Background of the game
LPDIRECTDRAWSURFACE		lpDDSBackground2; // Background of the game
LPDIRECTDRAWSURFACE		lpDDSBlock;      // the tetris blocks :)

LPDIRECTSOUND			lpDS;			// DirectSound Object

HWND					hwnd;			// Handle of window
BLOCK					game[10][24];  // The tetris blocks

JOUEUR player[1];

struct Point {
	Point(int _x, int _y) : x(_x), y(_y) {}
	int x;
	int y;
};

struct RotationTest {
	RotationTest() = default;

	RotationTest(Point test1, Point test2, Point test3, Point test4) {
		tests.push_back(test1);
		tests.push_back(test2);
		tests.push_back(test3);
		tests.push_back(test4);
	}

	std::vector<Point> tests;
};

struct GenericWallKickData {
	std::vector<RotationTest> clockwises;
	std::vector<RotationTest> counterclockwises;
};

struct IWallKickData {
	std::vector<RotationTest> clockwises;
	std::vector<RotationTest> counterclockwises;
};

GenericWallKickData genericWallKickData;
IWallKickData iWallKickData;

int GetRandomBlock() {
	int types[] = { T_BLOCK, L1_BLOCK, L2_BLOCK, S1_BLOCK, S2_BLOCK, BAR_BLOCK, CUBE_BLOCK };
	int newBlockType = types[rand() % 7];
	return newBlockType;
}

// The tretrade are written in usual human form, but that means we have to index them with [y][x] which can be considered confusing
// instead, we swizzle them back so we can refer them to [x][y] instead
void SwizzleTetra() {
	for (int t = 0; t < 25; ++t) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < i; ++j) {
				char temp = tetra[t][i][j];
				tetra[t][i][j] = tetra[t][j][i];
				tetra[t][j][i] = temp;
			}
		}
	}
}

void InitWallKickData() {
	//            (0)       (1)   (2)      (3)
	// SpawnState --> Right --> 2 --> Left --> SpawnState
	genericWallKickData.clockwises.push_back(RotationTest(Point(-1, 0), Point(-1, 1), Point(0, -2), Point(-1, -2)));
	genericWallKickData.clockwises.push_back(RotationTest(Point(1, 0), Point(1, -1), Point(0, 2), Point(1, 2)));
	genericWallKickData.clockwises.push_back(RotationTest(Point(1, 0), Point(1, 1), Point(0, -2), Point(1, -2)));
	genericWallKickData.clockwises.push_back(RotationTest(Point(-1, 0), Point(-1, -1), Point(0, 2), Point(-1, 2)));

	//            (0)      (1)   (2)       (3)
	// SpawnState --> Left --> 2 --> Right --> SpawnState
	genericWallKickData.counterclockwises.push_back(RotationTest(Point(1, 0), Point(1, 1), Point(0, -2), Point(1, -2)));
	genericWallKickData.counterclockwises.push_back(RotationTest(Point(-1, 0), Point(-1, -1), Point(0, 2), Point(-1, 2)));
	genericWallKickData.counterclockwises.push_back(RotationTest(Point(-1, 0), Point(-1, 1), Point(0, -2), Point(-1, -2)));
	genericWallKickData.counterclockwises.push_back(RotationTest(Point(1, 0), Point(1, -1), Point(0, 2), Point(1, 2)));
}

int WINAPI WinMain(
	HINSTANCE  hInstance,	// handle to current instance
    HINSTANCE  hPrevInstance,	// handle to previous instance
    LPSTR  lpCmdLine,	// pointer to command line
    int  nShowCmd)
{
	MSG msg;

	SwizzleTetra();
	InitWallKickData();
	InitVar();
	DoInit(hInstance, nShowCmd);
	
    /*
     * create the main DirectDraw object
     */

	
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

		
	return msg.wParam;
}

LRESULT CALLBACK WindowProc(
    HWND  hwnd,	// handle of window
    UINT  uMsg,	// message identifier
    WPARAM  wParam,	// first message parameter
    LPARAM  lParam 	// second message parameter
 ) 
{
	if (uMsg == WM_TIMER) 
	{ // Timer :) Move the block down
		if (CheckDown(&player[0])) 
			player[0].tetrade.y++;
		else{
	 		LINE line;
			StopBlock(&player[0]);  //That stops the block
			if (CheckIfLine(&player[0], &line))  // Check if any line should be removed
				DestroyLine(&player[0], &line);
		
			CreateBlock(&player[0], 5, 1, NEXT);
			}
		}
		
	if (uMsg == WM_SETCURSOR)
		SetCursor(NULL);
	
	if (uMsg == WM_CREATE)
		return 0;
	
	if (uMsg == WM_KEYDOWN) {
        switch (wParam) {
		case VK_ESCAPE:
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			return 0;
		case VK_F9:
			player[0].tetrade.x =1;
			player[0].tetrade.y =1;
			player[0].tetrade.blocktype = T_BLOCK;
			break;
		case VK_F8:
			player[0].tetrade.x=1;
			player[0].tetrade.y=1;
			player[0].tetrade.blocktype = BAR_BLOCK;
			break;
		case VK_F7:
			player[0].tetrade.x=1;
			player[0].tetrade.y=1;
			player[0].tetrade.blocktype = CUBE_BLOCK;
			break;
		case VK_F6:
			player[0].tetrade.x=1;
			player[0].tetrade.y=1;
			player[0].tetrade.blocktype = L1_BLOCK;
			break;
		case VK_F5:
			player[0].tetrade.x=1;
			player[0].tetrade.y=1;
			player[0].tetrade.blocktype = L2_BLOCK;
			break;
		case VK_F4:
			player[0].tetrade.x =1;
			player[0].tetrade.y=1;
			player[0].tetrade.blocktype = S1_BLOCK;
			break;
		case VK_F3:
			player[0].tetrade.x =1;
			player[0].tetrade.y=1;
			player[0].tetrade.blocktype = S2_BLOCK;
			break;
		case VK_F12:
			StopBlock(&player[0]);
			break;

		case VK_LEFT:
			if (CheckLeft(&player[0]))
				player[0].tetrade.x--;
			break;

		case VK_RIGHT:
			if (CheckRight(&player[0]))
				player[0].tetrade.x++;
			break;

		case VK_UP:
			RotateClockwise(&player[0]);
			break;

		case VK_DOWN:
			if (CheckDown(&player[0])) {
				player[0].tetrade.y++;
			} else {
				LINE line;
				StopBlock(&player[0]);  //That stops the block
				if (CheckIfLine(&player[0], &line))  // Check if any line should be removed
					DestroyLine(&player[0], &line);
				CreateBlock(&player[0], 5, 1, NEXT);
				
				
			}
			break;
		}
		ReDisplayScreen();
	}

	if (uMsg == WM_TIMER) {
		ReDisplayScreen();
	}

	if (uMsg == WM_DESTROY) {
		if( lpDD2 != NULL )
		{

			if (lpDDSBackground != NULL) {
				lpDDSBackground->Release();
				lpDDSBackground = NULL;
			}
			
			if (lpDDSBackground2 != NULL) {
				lpDDSBackground2->Release();
				lpDDSBackground2 = NULL;
			}
			
			if (lpDDSBlock != NULL) {
				lpDDSBlock->Release();
				lpDDSBlock = NULL;
			}
			
			
			if (lpDDSBack != NULL) {
				lpDDSBack->Release();
				lpDDSBack = NULL;
			}

						
			if( lpDDSPrimary != NULL )
			{
				lpDDSPrimary->Release();
				lpDDSPrimary = NULL;
			}

			
			lpDD2->Release();
			lpDD2 = NULL;
			
		}
		if (lpDD != NULL) {
			lpDD->Release();
			lpDD = NULL;
		}
		PostQuitMessage(0);

	}

	return (DefWindowProc(hwnd, uMsg, wParam, lParam));
}

static BOOL DoInit(HINSTANCE hInstance, int nShowCmd)
{
	WNDCLASS				wc;
	DDSURFACEDESC			ddsd;    

    /*
     * set up and register window class
     */
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( hInstance, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "MainWndClass";
    RegisterClass(&wc);
    
    /*
     * create a window
     */
    hwnd = CreateWindowEx(
        WS_EX_TOPMOST,
        "MainWndClass",
        "Tetris",
        WS_POPUP,
        0, 0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        NULL,
        NULL,
        hInstance,
        NULL);

    if(!hwnd)
    {
        return FALSE;
    }

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);


	result = DirectDrawCreate(NULL, &lpDD, NULL);
	if (result == DD_OK) {
		result = lpDD->SetCooperativeLevel(hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
		if (result == DD_OK) {
			result = lpDD->QueryInterface(IID_IDirectDraw2, (LPVOID *)&lpDD2);
			if(result == DD_OK) {
				result = lpDD2->SetDisplayMode(640, 480, 8, 0, 0);
				if (result == DD_OK) {

					memset(&ddsd, 0, sizeof(ddsd));
					ddsd.dwSize = sizeof(ddsd);
					ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
					ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
					ddsd.dwBackBufferCount = 1;
					lpDD2->CreateSurface(&ddsd, &lpDDSPrimary, NULL);

					ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
					lpDDSPrimary->GetAttachedSurface(&ddsd.ddsCaps, &lpDDSBack);

					// This is for test purpose only.
					// Trying to learn Direct X.
					// Load a bitmap file and then try to display it.

					// This should load the bitmap into the surface
					lpDDSBackground = LoadBitmapIntoSurface(lpDD2, 0, 0, 220, 480, "back.bmp");
					lpDDSBackground2 = LoadBitmapIntoSurface(lpDD2, 0, 0, 420, 480, "back2.bmp");
					if (lpDDSBackground == NULL)
						return FALSE;
					

					// Load the block tiles
					lpDDSBlock = LoadBitmapIntoSurface(lpDD2, 0, 0, 140, 20, "block.bmp");

					Flipper();
					SetTimer(hwnd, 1, 1200, NULL);
				}
			}
		}
	}
	return TRUE;
}

void Flipper(void) 
{
	// flip the backbuffer into the primary buffer (screen)
    while(1)
    {
        result = lpDDSPrimary->Flip(NULL, 0);
        if(result == DD_OK)
        {
            break;
        }
        if(result == DDERR_SURFACELOST)
        {
            if(!RestoreSurface())
            {
                return;
            }
        }
        if(result != DDERR_WASSTILLDRAWING)
        {
            break;
        }
    }
}

void CreateBlock(struct JOUEUR *player, int x, int y, int flag)
{
	player[0].tetrade.x = x;
	player[0].tetrade.y = y;
	
	int newBlockType = GetRandomBlock();

	if (flag == RANDOM) {
		player[0].tetrade.blocktype = newBlockType;
	}
	
	if (flag == NEXT) 
	{
		// this simple create the block showed by the player.next
		player[0].tetrade.blocktype = player[0].next.blocktype;
		// create a new next block...
		player[0].next.blocktype = newBlockType;
	}	
}

BOOL CanMove()
{
	return FALSE;
}

void Move()
{
}

void ReDisplayScreen()
{
	RECT		rect;
	DDBLTFX     ddbltfx;
	int xx;
	int yy;
	
	// First thing, erase the screen

    ddbltfx.dwSize = sizeof(ddbltfx);
    ddbltfx.dwFillColor = 0;

	lpDDSBack->Blt(NULL, NULL, NULL, DDBLT_COLORFILL, &ddbltfx);

	rect.top = 0;
	rect.left = 0;
	rect.right = 220;
	rect.bottom = 480;
				
	while (1)
	{
		result = lpDDSBack->BltFast(0, 0, lpDDSBackground, &rect, 0);
		if (result == DD_OK)
			break;
        if(result == DDERR_SURFACELOST)
        {
	        if(!RestoreSurface())
				break;
        }
        if(result != DDERR_WASSTILLDRAWING)
			break;
	}
	while (1)
	{
		result = lpDDSBack->BltFast(420, 0, lpDDSBackground2, &rect, 0);
		if (result == DD_OK)
			break;
        if(result == DDERR_SURFACELOST)
        {
	        if(!RestoreSurface())
				break;
        }
        if(result != DDERR_WASSTILLDRAWING)
			break;
	}

	rect.bottom = 20;
	rect.right = 20;
	

	// Display the screen blocks
	for (yy=0;yy!=24;yy++) {
		for (xx=0;xx!=10;xx++) {
			if (game[xx][yy].flag & FULL)
				DisplayBlock(xx, yy, xx%7, RELA);
		}
	}
	
	// Display the current block
	for (yy=0;yy!=4;yy++) {
		for (xx=0;xx!=4;xx++) {
			if (tetra[player[0].tetrade.blocktype][xx][yy]) // there's a block
				DisplayBlock(player[0].tetrade.x+xx, player[0].tetrade.y+yy, BLUE, RELA); // display it
		}
	}

	// Display the next block

	for (yy=0;yy!=4;yy++) {
		for (xx=0;xx!=4;xx++) {
			if (tetra[player[0].next.blocktype][xx][yy]) // there's a block
				DisplayBlock(xx+26, yy+3, RED, ABSOLUTE); // display it
		}
	}

	// display the number of line

	char text[256];
	snprintf(text, sizeof(text), "%i", player[0].line);
	DisplayString(lpDDSBack, text, 480, 160);
	
	Flipper();
}


void InitVar()
{
	// Clear the structure of random garbage data
	ZeroMemory(&game, sizeof(game));
	ZeroMemory(&player, sizeof(player));
	// start the randomizer
	srand(time(NULL));
	player[0].next.blocktype = GetRandomBlock();
}

// Check if the blockType is in a valid position
bool CheckValid(const TETRADE& tetrade, int blockType) {
	for (int y = 0; y != 4; y++) {
		for (int x = 0; x != 4; x++) {
			if (tetra[blockType][x][y]) { // block there
				if (game[tetrade.x + x][tetrade.y + y].flag & FULL)
					return false;
				if (tetrade.x + x == -1)
					return false;
				if (tetrade.x + x == 10)
					return false;
				if (tetrade.y + y == 24)
					return false;
			}
		}
	}

	return true;
}

BOOL RotateClockwise(struct JOUEUR *player)
{
	int type = player[0].tetrade.blocktype;
	int newtype = type + 1;

	if (newtype == L1_BLOCK)
		newtype = T_BLOCK;
	if (newtype == L2_BLOCK)
		newtype = L1_BLOCK;
	if (newtype == S1_BLOCK)
		newtype = L2_BLOCK;
	if (newtype == S2_BLOCK)
		newtype = S1_BLOCK;
	if (newtype == BAR_BLOCK)
		newtype = S2_BLOCK;
	if (newtype == CUBE_BLOCK)
		newtype = BAR_BLOCK;
	if (newtype == CUBE_BLOCK+1)
		newtype = CUBE_BLOCK;

	// Check if valid position
	if (!CheckValid(player[0].tetrade, newtype)) {
		// Try various wallkicks

		return FALSE;
	}

	player[0].tetrade.blocktype = newtype;
	return TRUE;
}

BOOL CheckLeft(struct JOUEUR *player)
{
	// We are moving left. Easy, just check the blocks on the left if they are full
	// Should work for all blocks. As it's only checking the game array.. not the current block
	// Inplementation for two players in the same game can't be done with this. But however,
	// it can be changed very easily. :)

	int x;
	int y;
	
	// Let's find if any of them would be going -out- of the game playable area

	for (y=0;y!=4;y++) {
		for (x=0;x!=4;x++) {
			if (tetra[player[0].tetrade.blocktype][x][y]) {
				if (player[0].tetrade.x+x-1 == -1) // we're going out!
					return FALSE;
			}
		}
	}

	// now, let's check if there's not a block in the way
	
	for (y=0;y!=4;y++) {
		for (x=0;x!=4;x++) {
			if (tetra[player[0].tetrade.blocktype][x][y]) { // if == 1
				if (game[player[0].tetrade.x+x-1][player[0].tetrade.y+y].flag & FULL) // check the block on the left
					return FALSE;							 // if you get here, then it can't move
			}
		}
	}

	// else, you can move it.
	return TRUE;
}


BOOL CheckRight(struct JOUEUR *player)
{
	// see CheckLeft for future explanation.
	int x;
	int y;
	
	// Let's find if any of them would be going -out- of the game playable area

	for (y=0;y!=4;y++) {
		for (x=0;x!=4;x++) {
			if (tetra[player[0].tetrade.blocktype][x][y]) {
				if (player[0].tetrade.x+x+1 == 10) // we're going out!
					return FALSE;
			}
		}
	}

	// now, let's check if there's not a block in the way
	
	for (y=0;y!=4;y++) {
		for (x=0;x!=4;x++) {
			if (tetra[player[0].tetrade.blocktype][x][y]) { // if == 1
				if (game[player[0].tetrade.x+x+1][player[0].tetrade.y+y].flag & FULL) // check the block on the right
					return FALSE;							 // if you get here, then it can't move
			}
		}
	}

	// else, you can move it.
	return TRUE;
}


BOOL CheckDown(struct JOUEUR *player)
{
	int x;
	int y;

	for (x=0;x!=4;x++) {
		for (y=0;y!=4;y++) {
			if (tetra[player[0].tetrade.blocktype][x][y]) { // if == 1
				if (game[player[0].tetrade.x+x][player[0].tetrade.y+y+1].flag & FULL) // regarde le bloc en bas
					return FALSE;
			}
		}
	}

	for (x=0;x!=4;x++) {
		for (y=0;y!=4;y++) {
			if (tetra[player[0].tetrade.blocktype][x][y]) { // if == 1
				if (player[0].tetrade.y+y+1 == 24) // on sort du jeu!!
					return FALSE;
			}
		}
	}
	return TRUE;
}





BOOL CheckIfLine(struct JOUEUR *player, struct LINE *line)
{
	int y;
	int total=0;
	
	// reset the structure
	ZeroMemory(line, sizeof(line));
	
	for (y=0;y!=24;y++)
	{
		// Yes, this looks stupid, but I was -sick- and -tired- of some stupid bug.

		if ((game[0][y].flag & FULL) && (game[1][y].flag & FULL) && (game[2][y].flag & FULL) && (game[3][y].flag & FULL) && (game[4][y].flag & FULL) && (game[5][y].flag & FULL) && (game[6][y].flag & FULL) && (game[7][y].flag & FULL) && (game[8][y].flag & FULL) && (game[9][y].flag & FULL)) {
			line->line[total] = y;
			total++;
		}
	}

	line->numline = total; // set the number of line
	line->special = 0; // reserved (must be 0)

	if (total>0)
		return TRUE;
	else
		return FALSE;

}

BOOL DestroyLine(struct JOUEUR *player, struct LINE *line)
{
	// the LINE structure is created such as:
	// numline is the number of line done (1 to 4)
	// line[4] is an array of 4 integers containing the line to be destroyed (in y=0, y=1 order, IMPORTANT)
	// special is a reserved flag (currently), going to be used for special effect and/or future implementations.

	int x;
	int y;
	int count;
	for (count=0;count!=line->numline;count++) // number of line
	{
		for (y=line->line[count];y!=0;y--)
		{
			for (x=0;x!=10;x++) 
			{
				game[x][y].flag = 0; // reset flag
				game[x][y].flag = game[x][y-1].flag;
			}
		}
	}

	// everything done, let's add the total line numbers.

	player[0].line += line->numline;
	return TRUE;
}

BOOL StopBlock(struct JOUEUR *player)
{
	int x;
	int y;

	for (x=0;x!=4;x++) {
		for (y=0;y!=4;y++) {
			if (tetra[player[0].tetrade.blocktype][x][y])  // if == 1
				game[player[0].tetrade.x+x][player[0].tetrade.y+y].flag |= FULL;
			
		}
	}

	return TRUE;
}

BOOL DisplayBlock(int x, int y, int color, int flag)
{
	// x = x
	// y = y
	// flag = RELATIVE or ABSOLUTE
	// color = CoLoR :)

	RECT rect;
	rect.top=0;
	rect.bottom=20;
	rect.left = color*20;
	rect.right = (color+1)*20;
	
	if (flag == ABSOLUTE)
	{
		while (1) {
			result = lpDDSBack->BltFast(x*20, y*20, lpDDSBlock, &rect, 0);
			if (result == DD_OK)
				break;									// everything all right, exit loop
			
			if (result == DDERR_SURFACELOST) {
				if (!RestoreSurface())                 // if restore ok then try again, if not, exit loop   
					return FALSE;					
			}

			if (result == DDERR_WASSTILLDRAWING) // can't do much here
				return FALSE;
		}
				
	}
	if (flag == RELA)
	{
		while (1) {
			result = lpDDSBack->BltFast(220+x*20, y*20, lpDDSBlock, &rect, 0);
			if (result == DD_OK)
				break;									// everything all right, exit loop
			
			if (result == DDERR_SURFACELOST) {
				if (!RestoreSurface())                 // if restore ok then try again, if not, exit loop   
					return FALSE;					
			}

			if (result == DDERR_WASSTILLDRAWING) // can't do much here
				return FALSE;
		}

	}
	return TRUE; // resulted in a DD_OK
}

BOOL RestoreSurface(void)
{
	BOOL i;
	HBITMAP hbm;

	// first thing, restore all the surface.

	if (lpDDSPrimary->Restore() != DD_OK)
		return FALSE;
	if (lpDDSBackground->Restore() != DD_OK)
		return FALSE;
	if (lpDDSBackground2->Restore() != DD_OK)
		return FALSE;
	if (lpDDSBlock->Restore() != DD_OK)
		return FALSE;

	// now we just need to reload (copy) them again

	hbm = (HBITMAP)LoadImage(NULL, "back.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbm == NULL)
		return FALSE;
	i = CopyBitmapToSurface(lpDDSBackground, 0, 0, 220, 480, hbm, 0, 0);
	if (i == FALSE)
		return FALSE;

	hbm = (HBITMAP)LoadImage(NULL, "back2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbm == NULL)
		return FALSE;
	i = CopyBitmapToSurface(lpDDSBackground2, 0, 0, 220, 480, hbm, 0, 0);
	if (i == FALSE)
		return FALSE;

	// the block tiles too
	hbm = (HBITMAP)LoadImage(NULL, "block.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbm == NULL)
		return FALSE;
	i = CopyBitmapToSurface(lpDDSBlock, 0, 0, 140, 20, hbm, 0, 0);
	if (i == FALSE)
		return FALSE;

	return TRUE; // everything is cool
}
