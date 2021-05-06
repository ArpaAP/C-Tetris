#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define VERSION "1.0.0"

// Copyright �� 2021 Ȳ�ο� All rights reserved.
// 2021 ȣ�����б� 1�г� 8�� 12�� Ȳ�ο�

const char *mainString;
const int menuMax = 1;
int mainScene(), gameScene();

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
		_kbhit();
		int firstKey = _getch();
		
		if (firstKey == 13) return menu; // ����Ű ������ ���� 
		
		int lastKey = _getch();
		
		// ���� ȭ��ǥ�� ������ 
		if (firstKey == 224 && lastKey == 72)
		{
			if (menu >= menuMax) menu--;
			else menu = menuMax;
		}
		
		// �Ʒ��� ȭ��ǥ�� ������ 
		else if (firstKey == 224 && lastKey == 80)
		{
			if (menu < menuMax) menu++;
			else menu = 0;
		}
		else continue;
		
		setColor(15 ,9);
		system("cls");
		
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

int gameScene()
{
	system("cls");
	system("color 0f");
	return 0; 
}
