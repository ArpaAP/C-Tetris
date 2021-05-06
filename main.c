#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define VERSION "1.0.0"

// Copyright ⓒ 2021 황부연 All rights reserved.
// 2021 호산고등학교 1학년 8반 12번 황부연

const char *mainString;
const int menuMax = 1;
int mainScene(), gameScene();

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
    
    // 콘솔 세팅 
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
				MessageBox(GetConsoleWindow(), "화살표 왼쪽, 오른쪽 키로 이동합니다.\n화살표 위쪽 키로 블럭을 회전합니다.\n화살표 아래 키로 블럭을 빠르게 내릴 수 있습니다.", "게임 방법", MB_ICONQUESTION | MB_OK);
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
	// 메인 로고 출력 
	printf("\n\n\n\n\n\n\n");
	printf(mainString);
	printf("\n\n\n\n\n");
	
	// 메뉴 출력 
	printf("                                                               ");
	setColor(0 ,15);
	printf("  시 작 하 기  \n\n");
	setColor(15, 9);
	
	printf("                                                               ");
	printf("  게 임 방 법  \n\n");
	
	printf("\n\n\n\n\n\n\n\n                                                    ");
	printf("▲: 위로  |  ▼: 아래로  |  엔터: 선택");
	printf("\n\n\n\n\n\n  VER. %s - ⓒ 2021 Hwang Buyeon All rights reserved.", VERSION);
	
	int menu = 0;
	
	while (1)
	{
		_kbhit();
		int firstKey = _getch();
		
		if (firstKey == 13) return menu; // 엔터키 누르면 종료 
		
		int lastKey = _getch();
		
		// 위쪽 화살표를 누르면 
		if (firstKey == 224 && lastKey == 72)
		{
			if (menu >= menuMax) menu--;
			else menu = menuMax;
		}
		
		// 아래쪽 화살표를 누르면 
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
		printf("  시 작 하 기  \n\n");
		if (menu == 0) setColor(15 ,9);
		
		printf("                                                               ");
		if (menu == 1) setColor(0 ,15);
		printf("  게 임 방 법  \n\n");
		if (menu == 1) setColor(15 ,9);
		
		printf("\n\n\n\n\n\n\n\n                                                    ");
		printf("▲: 위로  |  ▼: 아래로  |  엔터: 선택");
		printf("\n\n\n\n\n\n  VER. %s - ⓒ 2021 Hwang Buyeon All rights reserved.", VERSION);
	}
}

int gameScene()
{
	system("cls");
	system("color 0f");
	return 0; 
}
