#ifndef _TETRIS_H_
#define _TETRIS_H_

#define RANDOM 0

#define FULL 1
#define MOVE 2

#define RANDOM 0
#define NEXT 1


#define T_BLOCK		0	// 4 phases
#define L1_BLOCK	4	// 4 phases
#define L2_BLOCK	8	// 4 phases
#define S1_BLOCK	12	// 4 phases
#define S2_BLOCK	16	// 4 phases
#define BAR_BLOCK	20	// 4 phases
#define CUBE_BLOCK	24	// 1 phase

#define RED 0
#define YELLOW 1
#define PINK 2
#define BLUE 3
#define GREEN_BLUE 4
#define GREEN 5
#define BROWN 6

//DisplayBlock defines...
#define RELA 0
#define ABSOLUTE 1

typedef struct BLOCK {
	int color;
	int flag;
} BLOCK;

typedef struct TETRADE {
	int	x;
	int y;
	int blocktype;
} TETRADE;

typedef struct LINE {
	short numline;
	int line[4];
	int special;   // special flag, maybe used for future version? :> (reserved, must be 0)
} LINE;

typedef struct JOUEUR {
	unsigned int line;
	unsigned int score;
	TETRADE tetrade;
	TETRADE next;
} JOUEUR;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
static BOOL DoInit(HINSTANCE hInstance, int nShowCmd);   
void Flipper(void);

void InitVar(void);
void CreateBlock(struct JOUEUR *player, int x, int y, int flag);
BOOL CanMove();
void Move();

void ReDisplayScreen();
BOOL DisplayBlock(int x, int y, int flag, int color);
BOOL RestoreSurface();

BOOL CheckLeft(struct JOUEUR *player);
BOOL CheckRight(struct JOUEUR *player);
BOOL CheckDown(struct JOUEUR *player);


BOOL CheckIfLine(struct JOUEUR *player, struct LINE *line);
BOOL DestroyLine(struct JOUEUR *player, struct LINE *line);

// The CheckIfLine function verify if lines are there, it fills a LINE structure.
// The DestroyLine function simply use the LINE structure and destroys the appropriate line, and
// move the block down accorinding. Adding score calculation and everything.

BOOL StopBlock(struct JOUEUR *player);
BOOL RotateClockwise(struct JOUEUR *player);

char tetra[25][4][4] =
{
	// T_BLOCK
	{
		{0, 1, 0, 0},
		{1, 1, 1, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 1, 0, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0},
		{1, 1, 1, 0},
		{0, 1, 0, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 1, 0, 0},
		{1, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 0, 0}
	},
	// L1_BLOCK
	{
		{0, 0, 1, 0},
		{1, 1, 1, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0},
		{1, 1, 1, 0},
		{1, 0, 0, 0},
		{0, 0, 0, 0}
	},
	{
		{1, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 0, 0}
	},
	// L2_BLOCK
	{
		{1, 0, 0, 0},
		{1, 1, 1, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	},
	{
		{0, 1, 1, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0},
		{1, 1, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 0},
	},
	{
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{1, 1, 0, 0},
		{0, 0, 0, 0}
	},
	// S1_BLOCK
	{
		{0, 1, 1, 0},
		{1, 1, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0},
		{0, 1, 1, 0},
		{1, 1, 0, 0},
		{0, 0, 0, 0}
	},
	{
		{1, 0, 0, 0},
		{1, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 0, 0}
	},
	// S2_BLOCK
	{
		{1, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 0, 1, 0},
		{0, 1, 1, 0},
		{0, 1, 0, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0},
		{1, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0},
	},
	{
		{0, 1, 0, 0},
		{1, 1, 0, 0},
		{1, 0, 0, 0},
		{0, 0, 0, 0}
	},
	// BAR_BLOCK
	{
		{0, 0, 0, 0},
		{1, 1, 1, 1},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 0, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 1, 0}
	},
	{
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{1, 1, 1, 1},
		{0, 0, 0, 0}
	},
	{
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0}
	},
	// CUBE_BLOCK
	{
		{0, 1, 1, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	},
};

/* FLAG
0: Type of block
	0 = Nothing
	1 = A block is there.
*/


#endif // _TETRIS_H_