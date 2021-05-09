#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <mmsystem.h>
#define VERSION "1.0.0"
#define PANEL_ROWS 20
#define PANEL_COLS 10

// Copyright �� 2021 Ȳ�ο� All rights reserved.
// 2021 ȣ�����б� 1�г� 8�� 12�� Ȳ�ο�

const char *mainString;
const int menuMax = 1;
int mainScene();
void gameScene();

void delay(clock_t s)
{
  clock_t start = clock();
  while(clock() - start < s);
}

void setColor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

int main(int argc, char *argv[]) {
	// Ŀ�� ���� 
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    
    // �ܼ� ���� 
	system("mode con cols=140 lines=40 | title TETRIS | color 9f");
	
	while (1)
	{
		int menu = mainScene();
		switch (menu)
		{
			case 0:
				gameScene();
				break;
			case 1:
				MessageBox(GetConsoleWindow(), "ȭ��ǥ ����, ������ Ű�� �̵��մϴ�.\nȭ��ǥ ���� Ű�� ���� ȸ���մϴ�.\nȭ��ǥ �Ʒ� Ű�� ���� ������ ���� �� �ֽ��ϴ�.", "���� ���", MB_ICONQUESTION | MB_OK);
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
	system("cls");
	// ���� �ΰ� ��� 
	printf("\n\n\n\n\n\n\n");
	printf(mainString);
	printf("\n\n\n\n\n");
	
	// �޴� ��� 
	printf("                                                               ");
	setColor(0 ,15);
	printf("  �� �� �� ��  \n\n");
	setColor(15, 9);
	
	printf("                                                               ");
	printf("  �� �� �� ��  \n\n");
	
	printf("\n\n\n\n\n\n\n\n                                                    ");
	printf("��: ����  |  ��: �Ʒ���  |  ����: ����");
	printf("\n\n\n\n\n\n  VER. %s - �� 2021 Hwang Buyeon All rights reserved.", VERSION);
	
	int menu = 0;
	
	while (1)
	{
		_getch();
		if (GetAsyncKeyState(VK_RETURN)) return menu;
		_getch();
		
		// ���� ȭ��ǥ�� ������  
		if (GetAsyncKeyState(VK_UP))
		{
			if (menu >= menuMax) menu--;
			else menu = menuMax;
		}
		
		// �Ʒ��� ȭ��ǥ�� ������ 
		else if (GetAsyncKeyState(VK_DOWN))
		{
			if (menu < menuMax) menu++;
			else menu = 0;
		}
		else continue;
		
		setColor(15 ,9);
		COORD pos = {0 , 0};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		
		printf("\n\n\n\n\n\n\n");
		printf(mainString);
		printf("\n\n\n\n\n");
	
		printf("                                                               ");
		if (menu == 0) setColor(0 ,15);
		printf("  �� �� �� ��  \n\n");
		if (menu == 0) setColor(15 ,9);
		
		printf("                                                               ");
		if (menu == 1) setColor(0 ,15);
		printf("  �� �� �� ��  \n\n");
		if (menu == 1) setColor(15 ,9);
		
		printf("\n\n\n\n\n\n\n\n                                                    ");
		printf("��: ����  |  ��: �Ʒ���  |  ����: ����");
		printf("\n\n\n\n\n\n  VER. %s - �� 2021 Hwang Buyeon All rights reserved.", VERSION);
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
					panel[row][col-1] = 2;
					panel[row][col] = 2;
					panel[row][col+1] = 2;
					panel[row][col+2] = 2;
					break;
				case 2:
					panel[row+1][col-1] = 2;
					panel[row+1][col] = 2;
					panel[row+1][col+1] = 2;
					panel[row+1][col+2] = 2;
					break;
				case 1:
					panel[row-1][col+1] = 2;
					panel[row][col+1] = 2;
					panel[row+1][col+1] = 2;
					panel[row+2][col+1] = 2;
					break;
				case 3:
					panel[row-1][col] = 2;
					panel[row][col] = 2;
					panel[row+1][col] = 2;
					panel[row+2][col] = 2;
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
	COORD pos = {0 , 0};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	char *tsp = "                       ";
	printf("\n\n\n\n\n\n\n\n\n");
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
	
	int result = 0;
	
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

void gameScene()
{
	system("cls");
	system("mode con cols=100 lines=40 | color 0f");
	int panel[PANEL_ROWS][PANEL_COLS] = {0};
	char currentBlock = 'I';
	int currentPos[2] = {1, 4}; // ���� ��� ��ǥ 
	int currentRotation = 0; // ���� ��� ȸ����(�ð�������� 0, 1, 2, 3)
	
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
			if (GetAsyncKeyState(VK_UP)) 
			{
				switch (currentBlock)
				{
					case 'T':
						if (currentRotation == 1 && checkTouchWall(panel) & 0x8) currentPos[1]++;
						if (currentRotation == 3 && checkTouchWall(panel) & 0x2) currentPos[1]--;
						break;
				}
				
				if (currentRotation < 3) currentRotation++;
				else currentRotation = 0;
				finalRefresh();
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
			delay(100);
		}
		
		if (checkTouchWall(panel) & 0x4)
		{
			comfirmActiveBlocks(panel);
			a = 0;
			currentPos[0] = 1;
			currentPos[1] = 4;
			currentRotation = 0;
			continue;
		}
		a++;
	}
}
