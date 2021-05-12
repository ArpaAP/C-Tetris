#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include<mmsystem.h> 
#pragma comment(lib,"winmm.lib")
#define VERSION "1.0.0"
#define PANEL_ROWS 20
#define PANEL_COLS 10

// Copyright �� 2021 Ȳ�ο� All rights reserved.
// 2021 ȣ�����б� 1�г� 8�� 12�� Ȳ�ο�

const char *mainString;
const char BLOCKS[7] = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
int mainScene();
void gameScene();

HWND w;
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

// â�� Ȱ�� �������� �ƴ��� Ȯ�� 
int windowActive()
{
	return w == GetForegroundWindow();
}

int main(int argc, char *argv[]) {
	w = GetForegroundWindow();

	// Ŀ�� ���� 
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    
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
				MessageBox(
					GetConsoleWindow(), 
					""\
					"ȭ��ǥ ����, ������ Ű�� �̵��մϴ�.\n\n"\
					"ȭ��ǥ ���� Ű�� ���� ȸ���մϴ�.\n\n"\
					"ȭ��ǥ �Ʒ� Ű�� ���� ������ ���� �� �ֽ��ϴ�.\n\n"\
					"�����̽� Ű�� ���� �ٷ� ���� �� �ֽ��ϴ�.",
					"���� ���", 
					MB_ICONQUESTION | MB_OK
				);
				while (windowActive() && GetAsyncKeyState(VK_RETURN));
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
	PlaySound (TEXT("main.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	// ���� �ΰ� ��� 
	gotoxy(0, 7);
	printf(mainString);
	
	gotoxy(63, 20);
	
	// �޴� ��� 
	setColor(0 ,15);
	printf("  �� �� �� ��  ");
	setColor(15, 9);
	
	gotoxy(63, 22);
	printf("  �� �� �� ��  ");
	
	gotoxy(52, 32);
	printf("��: ����  |  ��: �Ʒ���  |  ����: ����");
	gotoxy(2, 38);
	printf("VER. %s - �� 2021 Hwang Buyeon All rights reserved.", VERSION);
	
	const int menuMax = 1;
	int menu = 0;
	
	while (1)
	{
		if (windowActive() && GetAsyncKeyState(VK_RETURN))
		{
			while (windowActive() && GetAsyncKeyState(VK_RETURN));
			return menu;
		}
		
		// ���� ȭ��ǥ�� ������  
		if (windowActive() && GetAsyncKeyState(VK_UP))
		{
			if (menu >= menuMax) menu--;
			else menu = menuMax;
		}
		
		// �Ʒ��� ȭ��ǥ�� ������ 
		else if (windowActive() && GetAsyncKeyState(VK_DOWN))
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
		printf("  �� �� �� ��  ");
		if (menu == 0) setColor(15 ,9);
		
		gotoxy(63, 22);
		if (menu == 1) setColor(0 ,15);
		printf("  �� �� �� ��  ");
		if (menu == 1) setColor(15 ,9);
		
		gotoxy(52, 32);
		printf("��: ����  |  ��: �Ʒ���  |  ����: ����");
		gotoxy(2, 38);
		printf("VER. %s - �� 2021 Hwang Buyeon All rights reserved.", VERSION);
		
		delay(180);
	}
}

// ����� ������ ��ǥ�� ������ �����ϴ�. 
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

// Ȱ�� ����� �����մϴ�. 
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

// ���� �г��� �о�鿩 ���ΰ�ħ�մϴ�. 
void refreshPanel(int (*panel)[PANEL_COLS]) 
{
	// ���� �г� ǥ�� 
	gotoxy(0, 8);
	char *tsp = "                       ";
	printf("%s�̢̢̢̢̢̢̢̢̢̢̢�\n", tsp);
	
	int row, col;
	for (row = 0; row < PANEL_ROWS; row++)
	{
		printf("%s��", tsp);
		for (col = 0; col < PANEL_COLS; col++)
		{
			if (panel[row][col] == 1) printf("��");
			else if (panel[row][col] == 2) printf("��");
			else printf("  ");
		}
		printf("��\n");
	}
	printf("%s�̢̢̢̢̢̢̢̢̢̢̢�\n", tsp);
	
	// ���� ��� ǥ��
	gotoxy(58, 8);
	printf("��������  ������� ��������");
	
	int i;
	for (i = 9; i < 15; i++) 
	{
		gotoxy(58, i);
		printf("��                 ��");
	
	}
	gotoxy(58, 15);
	printf("��������������������������������������");
	
	gotoxy(64, 11);
	switch(nextBlock) 
	{
		case 'I':
			printf("�����");
			break;
		case 'J':
			printf("��");
			gotoxy(64, 12);
			printf("����");
			break;
		case 'L':
			printf("    ��");
			gotoxy(64, 12);
			printf("����");
			break;
		case 'O':
			printf("  ���");
			gotoxy(64, 12);
			printf("  ���");
			break;
		case 'S':
			printf("  ���");
			gotoxy(64, 12);
			printf("���  ");
			break;
		case 'T':
			printf("  ��  ");
			gotoxy(64, 12);
			printf("����");
			break;
		case 'Z':
			printf("���  ");
			gotoxy(64, 12);
			printf("  ���");
			break;
	}
	
	gotoxy(58, 17);
	printf("������������  ���� ������������");
	gotoxy(58, 18);
	printf("��                 ��");
	gotoxy(58, 19);
	printf("��������������������������������������");
	
	gotoxy(60, 18);
	printf("%d", score);
	
	gotoxy(11, 36);
	printf("����: �̵�  |  ��: ȸ��  |  ��: ������  |  SPACE : ��ó���  |  ESC : ��������");
}

/*
�� �Լ��� Ȱ�� ���� ���̳� �ٸ� ���� ��� �ִ��� ���θ� �˻��մϴ�.
���� ���� ���: 0x1, �����ʿ� ���� ���: 0x2, �Ʒ��� ���� ���: 0x4, ���ʿ� ���� ���: 0x8 �� ����(OR) �������� ���ϵ˴ϴ�. 
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
	
	// �Ʒ��� ��� �ִ��� �˻�.
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
	
	// ���ʿ� ��� �ִ��� �˻�.
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
	
	// �����ʿ� ��� �ִ��� �˻�.
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
	
	// ���� ��� �ִ��� �˻�.
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
	
	// minRow�� 0�� ���, �� ����� õ�庮�� ��� ���� �������� ����. 
	if (minCol == 0) // ���� ���� ��� ��� 
	{
		result |= 0x8;
	}
	if (maxRow == PANEL_ROWS - 1) // �ٴڰ� ��� ��� 
	{
		result |= 0x4;
	}
	if (maxCol == PANEL_COLS - 1) // ������ ���� ��� ��� 
	{
		result |= 0x2;
	}
	
	return result;
}

// Ȱ�� ����� Ȯ���Ͽ� �����մϴ�. 
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
	int row, col;
	
	while (1)
	{
		for (row = PANEL_ROWS; row > 0; row--)
		{
			for (col = 0; col < PANEL_COLS; col++)
			{
				if (panel[row][col] != 1) break;
			}
			if (col != PANEL_COLS) continue;
			else
			{
				//row: ã�� �ٳѹ� 
				int irow, icol;
				for (irow = 0; irow < row; irow++)
				{
					for (icol = 0; icol < PANEL_COLS; icol++)
					{
						panel[row - irow][icol] = panel[row - irow - 1][icol];
					}
				}
				score += 100;
				break;
			}
		}
		if (row == 0) break;
	}
}

int gameOver()
{	
	PlaySound (TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
	gotoxy(18, 11);
	setColor(12, 0);
	printf(" ��������������������������������������������������  ���� ���� ��������������������������������������������������");
	
	int i;
	for (i = 12; i < 27; i++)
	{
		gotoxy(18, i);
		printf(" ��                                                            ��");
	}
	gotoxy(18, 27);
	printf(" ����������������������������������������������������������������������������������������������������������������������������");
	
	gotoxy(34, 16);
	setColor(15, 0);
	printf("�� �̻� ����� ���� �� �����ϴ�!");
	
	gotoxy(42, 20);
	setColor(0 ,15);
	printf("  �ٽ� �÷���  ");
	setColor(15, 0);
	
	gotoxy(42, 22);
	printf("    ��������    ");
	
	const int menuMax = 1;
	int menu = 0;
	
	while (1)
	{
		if (windowActive() && GetAsyncKeyState(VK_RETURN))
		{
			while (windowActive() && GetAsyncKeyState(VK_RETURN));
			return menu;
		}
		
		// ���� ȭ��ǥ�� ������  
		if (windowActive() && GetAsyncKeyState(VK_UP))
		{
			if (menu >= menuMax) menu--;
			else menu = menuMax;
		}
		
		// �Ʒ��� ȭ��ǥ�� ������ 
		else if (windowActive() && GetAsyncKeyState(VK_DOWN))
		{
			if (menu < menuMax) menu++;
			else menu = 0;
		}
		else continue;
		
		gotoxy(42, 20);
		if (menu == 0) setColor(0, 15);
		printf("  �ٽ� �÷���  ");
		setColor(15, 0);
		
		gotoxy(42, 22);
		if (menu == 1) setColor(0, 15);
		printf("    ��������    ");
		
		delay(180);
	}
}

void gameScene()
{
	system("cls");
	system("mode con cols=100 lines=40 | color 0f");
	PlaySound (TEXT("bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	
	score = 0;
	
	int panel[PANEL_ROWS][PANEL_COLS] = {0};
	char currentBlock = BLOCKS[rand() % 7];
	
	do nextBlock = BLOCKS[rand() % 7];
	while (nextBlock == currentBlock);
	
	int currentPos[2] = {1, 4}; // ���� ��� ��ǥ 
	int currentRotation = 0; // ���� ��� ȸ����(�ð�������� 0, 1, 2, 3)
	
	int a = 0;
	
	void finalRefresh()
	{
		clearActiveBlock(panel);
		putBlock(panel, currentPos[0]+a, currentPos[1], currentRotation, currentBlock);
		refreshPanel(panel);
	}
	
	while (1)
	{	
		int movingFloor = 0;
		finalRefresh();
		clock_t start = clock();
		while(clock() - start < (movingFloor ? 1000 : 800))
		{	
			if (windowActive() && GetAsyncKeyState(VK_DOWN) && !(checkTouchWall(panel) & 0x4)) 
			{
				delay(50);
				break;
			}
			if (windowActive() && GetAsyncKeyState(VK_UP) && !(checkTouchWall(panel) & 0x4))
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
			if (windowActive() && GetAsyncKeyState(VK_LEFT) && !(checkTouchWall(panel) & 0x8)) 
			{
				currentPos[1]--;
				finalRefresh();
			}
			if (windowActive() && GetAsyncKeyState(VK_RIGHT) && !(checkTouchWall(panel) & 0x2))
			{
				currentPos[1]++;
				finalRefresh();
			}
			if (windowActive() && GetAsyncKeyState(VK_SPACE))
			{
				while (!(checkTouchWall(panel) & 0x4))
				{
					currentPos[0]++;
					clearActiveBlock(panel);
					putBlock(panel, currentPos[0]+a, currentPos[1], currentRotation, currentBlock);
				}
				finalRefresh();
				movingFloor = 1;
			}
			if (windowActive() && GetAsyncKeyState(VK_ESCAPE)) return;
			delay(120);
		}

		if (checkTouchWall(panel) & 0x4)
		{	
			comfirmActiveBlocks(panel);
			clearLinedBlocks(panel);
			
			int i;
			for (i = 0; i < PANEL_COLS; i++)
			{
				if (panel[1][i] != 0)
				{
					setColor(7, 0);
					refreshPanel(panel);
					delay(300);
					
					setColor(8, 0);
					refreshPanel(panel);
					delay(600);
					
					int menu = gameOver();
					
					// ���� ����� 
					if (menu == 0) 
					{
						int j, k;
						for (j = 0; j < PANEL_ROWS; j++)
						{
							for (k = 0; k < PANEL_COLS; k++)
							{
								panel[j][k] = 0;
							}
						}
						
						system("cls");
						score = 0;
						PlaySound (TEXT("bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
						
						break;
					}
					else return;
				}
			}
			
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
