#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#define VERSION "1.0.0"
#define PANEL_ROWS 20
#define PANEL_COLS 10

// Copyright ⓒ 2021 황부연 All rights reserved.
// 2021 호산고등학교 1학년 8반 12번 황부연

const char *mainString;
const int menuMax = 1;
const char BLOCKS[7] = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
int mainScene();
void gameScene();

int score;
char nextBlock;

void delay(clock_t s)
{
  clock_t start = clock();
  while(clock() - start < s);
}

void gotoxy(int x, int y)
{
	COORD pos = {x , y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

int main(int argc, char *argv[]) {
	// 커서 제거 
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    
	// 랜덤 시드 세팅
	srand((unsigned int)time(NULL)); 
		
	while (1)
	{	
		int menu = mainScene();
		switch (menu)
		{
			case 0:
				gameScene();
				continue;
			case 1:
				MessageBox(GetConsoleWindow(), "화살표 왼쪽, 오른쪽 키로 이동합니다.\n화살표 위쪽 키로 블럭을 회전합니다.\n화살표 아래 키로 블럭을 빠르게 내릴 수 있습니다.", "게임 방법", MB_ICONQUESTION | MB_OK);
				delay(50);
				break;
		}
		if (menu == 0) break;
	}
	
	return 0;
}

const char *mainString = ""\
"                                            ######## ######## ######## ########  ####  ######  \n"\
"                                               ##    ##          ##    ##     ##  ##  ##    ## \n"\
"                                               ##    ##          ##    ##     ##  ##  ##       \n"\
"                                               ##    ######      ##    ########   ##   ######  \n"\
"                                               ##    ##          ##    ##   ##    ##        ## \n"\
"                                               ##    ##          ##    ##    ##   ##  ##    ## \n"\
"                                               ##    ########    ##    ##     ## ####  ######  \n"\
"                                                                                               \n"\
"                                                           - C LANGUAGE EDITION -                ";

int mainScene()
{
	system("mode con cols=140 lines=40 | title TETRIS | color 9f");
	system("cls");
	// 메인 로고 출력 
	gotoxy(0, 7);
	printf(mainString);
	
	gotoxy(63, 20);
	
	// 메뉴 출력 
	setColor(0 ,15);
	printf("  시 작 하 기  ");
	setColor(15, 9);
	
	gotoxy(63, 22);
	printf("  게 임 방 법  ");
	
	gotoxy(52, 32);
	printf("▲: 위로  |  ▼: 아래로  |  엔터: 선택");
	gotoxy(2, 38);
	printf("VER. %s - ⓒ 2021 Hwang Buyeon All rights reserved.", VERSION);
	
	int menu = 0;
	
	while (1)
	{
		if (GetAsyncKeyState(VK_RETURN)) return menu;
		
		// 위쪽 화살표를 누르면  
		if (GetAsyncKeyState(VK_UP))
		{
			if (menu >= menuMax) menu--;
			else menu = menuMax;
		}
		
		// 아래쪽 화살표를 누르면 
		else if (GetAsyncKeyState(VK_DOWN))
		{
			if (menu < menuMax) menu++;
			else menu = 0;
		}
		else continue;
		
		setColor(15 ,9);
		
		gotoxy(0, 7);
		printf(mainString);
	
		gotoxy(63, 20);
		if (menu == 0) setColor(0 ,15);
		printf("  시 작 하 기  ");
		if (menu == 0) setColor(15 ,9);
		
		gotoxy(63, 22);
		if (menu == 1) setColor(0 ,15);
		printf("  게 임 방 법  ");
		if (menu == 1) setColor(15 ,9);
		
		gotoxy(52, 32);
		printf("▲: 위로  |  ▼: 아래로  |  엔터: 선택");
		gotoxy(2, 38);
		printf("VER. %s - ⓒ 2021 Hwang Buyeon All rights reserved.", VERSION);
		
		delay(180);
	}
}

// 블록을 선택한 좌표와 각도로 놓습니다. 
void putBlock(int (*panel)[PANEL_COLS], int row, int col, int rotation, char block)
{
	switch (block)
	{
		case 'I':
			switch (rotation)
			{
				case 0:
				case 2:
					panel[row][col-1] = 2;
					panel[row][col] = 2;
					panel[row][col+1] = 2;
					panel[row][col+2] = 2;
					break;
				case 1:
				case 3:
					panel[row-2][col] = 2;
					panel[row-1][col] = 2;
					panel[row][col] = 2;
					panel[row+1][col] = 2;
					break;
			}
			
			break;
			
		case 'J':
			switch (rotation)
			{
				case 0:
					panel[row][col-1] = 2;
					panel[row][col] = 2;
					panel[row][col+1] = 2;
					panel[row-1][col-1] = 2;
					break;
				case 1:
					panel[row-1][col+1] = 2;
					panel[row-1][col] = 2;
					panel[row][col] = 2;
					panel[row+1][col] = 2;
					break;
				case 2:
					panel[row][col-1] = 2;
					panel[row][col] = 2;
					panel[row][col+1] = 2;
					panel[row+1][col+1] = 2;
					break;
				case 3:
					panel[row-1][col] = 2;
					panel[row][col] = 2;
					panel[row+1][col] = 2;
					panel[row+1][col-1] = 2;
					break;
			}
			break;
			
		case 'L':
			switch (rotation)
			{
				case 0:
					panel[row][col-1] = 2;
					panel[row][col] = 2;
					panel[row][col+1] = 2;
					panel[row-1][col+1] = 2;
					break;
				case 1:
					panel[row-1][col] = 2;
					panel[row][col] = 2;
					panel[row+1][col] = 2;
					panel[row+1][col+1] = 2;
					break;
				case 2:
					panel[row][col-1] = 2;
					panel[row][col] = 2;
					panel[row][col+1] = 2;
					panel[row+1][col-1] = 2;
					break;
				case 3:
					panel[row-1][col] = 2;
					panel[row][col] = 2;
					panel[row+1][col] = 2;
					panel[row-1][col-1] = 2;
					break;
			}
			break;
			
		case 'O':
			panel[row][col] = 2;
			panel[row][col+1] = 2;
			panel[row+1][col] = 2;
			panel[row+1][col+1] = 2;
			break;
		
		case 'S':
			switch (rotation)
			{
				case 0:
					panel[row][col] = 2;
					panel[row][col-1] = 2;
					panel[row-1][col] = 2;
					panel[row-1][col+1] = 2;
					break;
				case 1:
					panel[row][col] = 2;
					panel[row-1][col] = 2;
					panel[row][col+1] = 2;
					panel[row+1][col+1] = 2;
					break;
				case 2:
					panel[row][col] = 2;
					panel[row][col+1] = 2;
					panel[row+1][col] = 2;
					panel[row+1][col-1] = 2;
					break;
				case 3:
					panel[row][col] = 2;
					panel[row+1][col] = 2;
					panel[row][col-1] = 2;
					panel[row-1][col-1] = 2;
					break;
			}
			break;
			
		case 'T':
			switch (rotation)
			{
				case 0:
					panel[row][col] = 2;
					panel[row-1][col] = 2;
					panel[row][col-1] = 2;
					panel[row][col+1] = 2;
					break;
				case 1:
					panel[row][col] = 2;
					panel[row+1][col] = 2;
					panel[row-1][col] = 2;
					panel[row][col+1] = 2;
					break;
				case 2:
					panel[row][col] = 2;
					panel[row+1][col] = 2;
					panel[row][col-1] = 2;
					panel[row][col+1] = 2;
					break;
				case 3:
					panel[row][col] = 2;
					panel[row+1][col] = 2;
					panel[row-1][col] = 2;
					panel[row][col-1] = 2;
					break;
			}
			
			break;
			
		case 'Z':
			switch (rotation)
			{
				case 0:
					panel[row][col] = 2;
					panel[row][col+1] = 2;
					panel[row-1][col] = 2;
					panel[row-1][col-1] = 2;
					break;
				case 1:
					panel[row][col] = 2;
					panel[row+1][col] = 2;
					panel[row][col+1] = 2;
					panel[row-1][col+1] = 2;
					break;
				case 2:
					panel[row][col] = 2;
					panel[row][col-1] = 2;
					panel[row+1][col] = 2;
					panel[row+1][col+1] = 2;
					break;
				case 3:
					panel[row][col] = 2;
					panel[row-1][col] = 2;
					panel[row][col-1] = 2;
					panel[row+1][col-1] = 2;
			}
	}
}

// 활성 블록을 제거합니다. 
void clearActiveBlock(int (*panel)[PANEL_COLS])
{
	int row, col;
	for (row = 0; row < PANEL_ROWS; row++)
	{
		for (col = 0; col < PANEL_COLS; col++)
		{
			if (panel[row][col] == 2) panel[row][col] = 0;
		}
	}	
} 

// 현재 패널을 읽어들여 새로고침합니다. 
void refreshPanel(int (*panel)[PANEL_COLS]) 
{
	// 게임 패널 표시 
	gotoxy(0, 8);
	char *tsp = "                       ";
	printf("%s▩▩▩▩▩▩▩▩▩▩▩▩\n", tsp);
	
	int row, col;
	for (row = 0; row < PANEL_ROWS; row++)
	{
		printf("%s▩", tsp);
		for (col = 0; col < PANEL_COLS; col++)
		{
			if (panel[row][col] == 1) printf("□");
			else if (panel[row][col] == 2) printf("■");
			else printf("  ");
		}
		printf("▩\n");
	}
	printf("%s▩▩▩▩▩▩▩▩▩▩▩▩\n", tsp);
	
	// 다음 블록 표시
	gotoxy(58, 8);
	printf("┏━━━  다음블록 ━━━┓");
	
	int i;
	for (i = 9; i < 15; i++) 
	{
		gotoxy(58, i);
		printf("┃                 ┃");
	
	}
	gotoxy(58, 15);
	printf("┗━━━━━━━━━━━━━━━━━┛");
	
	gotoxy(64, 11);
	switch(nextBlock) 
	{
		case 'I':
			printf("■■■■");
			break;
		case 'J':
			printf("■");
			gotoxy(64, 12);
			printf("■■■");
			break;
		case 'L':
			printf("    ■");
			gotoxy(64, 12);
			printf("■■■");
			break;
		case 'O':
			printf("  ■■");
			gotoxy(64, 12);
			printf("  ■■");
			break;
		case 'S':
			printf("  ■■");
			gotoxy(64, 12);
			printf("■■  ");
			break;
		case 'T':
			printf("  ■  ");
			gotoxy(64, 12);
			printf("■■■");
			break;
		case 'Z':
			printf("■■  ");
			gotoxy(64, 12);
			printf("  ■■");
			break;
	}
	
	gotoxy(58, 17);
	printf("┏━━━━━  점수 ━━━━━┓");
	gotoxy(58, 18);
	printf("┃                 ┃");
	gotoxy(58, 19);
	printf("┗━━━━━━━━━━━━━━━━━┛");
	
	gotoxy(60, 18);
	printf("%d", score);
}

/*
이 함수는 활성 블럭이 벽이나 다른 블럭에 닿아 있는지 여부를 검사합니다.
위에 닿은 경우: 0x1, 오른쪽에 닿은 경우: 0x2, 아래에 닿은 경우: 0x4, 왼쪽에 닿은 경우: 0x8 의 논리합(OR) 연산으로 리턴됩니다. 
*/
int checkTouchWall(int (*panel)[PANEL_COLS])
{
	int minRow = -1;
	int maxRow = -1;
	int minCol = -1;
	int maxCol = -1;
	
	int row, col;
	for (row = 0; row < PANEL_ROWS; row++)
	{
		for (col = 0; col < PANEL_COLS; col++)
		{
			if (panel[row][col] == 2)
			{
				if (minRow == -1 || row < minRow) minRow = row;
				if (minCol == -1 || col < minCol) minCol = col;
				
				if (maxRow == -1 || row > maxRow) maxRow = row;
				if (maxCol == -1 || col > maxCol) maxCol = col;
			}
		}
	}

	int width = maxCol - minCol + 1;
	int height = maxRow - minRow + 1;
	
	int result = 0;
	
	// 아래에 블록 있는지 검사.
	for (row = 0; row < height; row++) 
	{
		for (col = 0; col < width; col++)
		{
			if (panel[row + minRow][col + minCol] == 2 && panel[row + minRow + 1][col + minCol] == 1)
			{
				result |= 0x4;
				break;
			}
		}
		if (col != width) break;
	}
	
	// 왼쪽에 블록 있는지 검사.
	for (row = 0; row < height; row++) 
	{
		for (col = 0; col < width; col++)
		{
			if (panel[row + minRow][col + minCol] == 2 && panel[row + minRow][col + minCol - 1] == 1)
			{
				result |= 0x8;
				break;
			}
		}
		if (col != width) break;
	}
	
	// 오른쪽에 블록 있는지 검사.
	for (row = 0; row < height; row++) 
	{
		for (col = 0; col < width; col++)
		{
			if (panel[row + minRow][col + minCol] == 2 && panel[row + minRow][col + minCol + 1] == 1)
			{
				result |= 0x2;
				break;
			}
		}
		if (col != width) break;
	}
	
	// 위에 블록 있는지 검사.
	for (row = 0; row < height; row++) 
	{
		for (col = 0; col < width; col++)
		{
			if (panel[row + minRow][col + minCol] == 2 && panel[row + minRow - 1][col + minCol] == 1)
			{
				result |= 0x1;
				break;
			}
		}
		if (col != width) break;
	}
	
	// minRow가 0인 경우, 즉 블록이 천장벽과 닿는 경우는 구현하지 않음. 
	if (minCol == 0) // 왼쪽 벽과 닿는 경우 
	{
		result |= 0x8;
	}
	if (maxRow == PANEL_ROWS - 1) // 바닥과 닿는 경우 
	{
		result |= 0x4;
	}
	if (maxCol == PANEL_COLS - 1) // 오른쪽 벽과 닿는 경우 
	{
		result |= 0x2;
	}
	
	return result;
}

// 활성 블록을 확정하여 고정합니다. 
void comfirmActiveBlocks(int (*panel)[PANEL_COLS])
{
	int row, col;
	for (row = 0; row < PANEL_ROWS; row++)
	{
		for (col = 0; col < PANEL_COLS; col++)
		{
			if (panel[row][col] == 2) panel[row][col] = 1;
		}
	}
}

void clearLinedBlocks(int (*panel)[PANEL_COLS])
{
	int row, col, deleted;
	for (row = PANEL_ROWS; row > 0; row--)
	{
		for (col = 0; col < PANEL_COLS; col++)
		{
			if (panel[row + deleted][col] != 1) break;
		}
		if (col != PANEL_COLS) continue;
		else
		{
			//row: 찾은 줄넘버 
			int irow, icol;
			for (irow = 0; irow < row; irow++)
			{
				for (icol = 0; icol < PANEL_COLS; icol++)
				{
					panel[row + deleted - irow][icol] = panel[row + deleted - irow - 1][icol];
				}
			}
			deleted += 1;
			score += 100;
		}
	}
} 

void gameScene()
{
	system("cls");
	system("mode con cols=100 lines=40 | color 0f");
	
	score = 0;
	gotoxy(11, 36);
	printf("◁▷: 이동  |  △: 회전  |  ▽: 내리기  |  SPACE : 즉시놓기  |  ESC : 메인으로");
	
	int panel[PANEL_ROWS][PANEL_COLS] = {0};
	char currentBlock = BLOCKS[rand() % 7];
	
	do nextBlock = BLOCKS[rand() % 7];
	while (nextBlock == currentBlock);
	
	int currentPos[2] = {1, 4}; // 현재 블록 좌표 
	int currentRotation = 0; // 현재 블록 회전각(시계방향으로 0, 1, 2, 3)
	
	refreshPanel(panel);
	
	int a = 0;
	
	void finalRefresh()
	{
		clearActiveBlock(panel);
		putBlock(panel, currentPos[0]+a, currentPos[1], currentRotation, currentBlock);
		refreshPanel(panel);
	}
	
	while (1)
	{	
		finalRefresh();
		clock_t start = clock();
		while(clock() - start < 800)
		{	
			if (GetAsyncKeyState(VK_DOWN) && !(checkTouchWall(panel) & 0x4)) 
			{
				delay(50);
				break;
			}
			if (GetAsyncKeyState(VK_UP) && !(checkTouchWall(panel) & 0x4))
			{
				switch (currentBlock)
				{
					case 'I':
						if ((currentRotation == 1 || currentRotation == 3) && checkTouchWall(panel) & 0x8) currentPos[1]++;
						if ((currentRotation == 1 || currentRotation == 3) && checkTouchWall(panel) & 0x2) currentPos[1] -= 2;
						if ((currentRotation == 0 || currentRotation == 2) && checkTouchWall(panel) & 0x4) currentPos[0]--;
						if ((currentRotation == 1 || currentRotation == 3) && currentPos[1] == 8) currentPos[1]--;
						break;
					case 'J':
					case 'L':
						if (currentRotation == 1 && checkTouchWall(panel) & 0x8) currentPos[1]++;
						if (currentRotation == 3 && checkTouchWall(panel) & 0x2) currentPos[1]--;
						break;
					case 'S':
					case 'Z':
						if (currentRotation == 1 && checkTouchWall(panel) & 0x8) currentPos[1]++;
						break;
					case 'T':
						if (currentRotation == 1 && checkTouchWall(panel) & 0x8) currentPos[1]++;
						if (currentRotation == 3 && checkTouchWall(panel) & 0x2) currentPos[1]--;
						break;
				}
				
				if (currentRotation < 3) currentRotation++;
				else currentRotation = 0;
				finalRefresh();
				delay(50);
			}
			if (GetAsyncKeyState(VK_LEFT) && !(checkTouchWall(panel) & 0x8)) 
			{
				currentPos[1]--;
				finalRefresh();
			}
			if (GetAsyncKeyState(VK_RIGHT) && !(checkTouchWall(panel) & 0x2))
			{
				currentPos[1]++;
				finalRefresh();
			}
			if (GetAsyncKeyState(VK_SPACE))
			{
				while (!(checkTouchWall(panel) & 0x4))
				{
					currentPos[0]++;
					clearActiveBlock(panel);
					putBlock(panel, currentPos[0]+a, currentPos[1], currentRotation, currentBlock);
				}
				finalRefresh();
				delay(120);
			}
			if (GetAsyncKeyState(VK_ESCAPE)) return;
			delay(120);
		}

		if (checkTouchWall(panel) & 0x4)
		{
			comfirmActiveBlocks(panel);
			clearLinedBlocks(panel);
			a = 0;
			currentPos[0] = 1;
			currentPos[1] = 4;
			currentRotation = 0;
			
			currentBlock = nextBlock;
			do nextBlock = BLOCKS[rand() % 7];
			while (nextBlock == currentBlock);
			continue;
		}
		a++;
	}
}
