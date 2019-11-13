#pragma once
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include "Input.h" 
#include "DoubleBuffer.h"

//플레이어
enum Player
{
	Playercheck1,
	Playercheck2,
};

typedef struct Object
{
	int Hp;
	int x, y;
	bool block;
	int BoobLength;
	Player player;

}Object;

Object Player1;
Object Player2;
Object Map[30][20];

bool Writeboob1;
bool Writeboob2;
long long int Player1coolTime;
long long int Player2coolTime;

long long int currentTime;

//게임 진행상태
enum GAME
{
	MENU,
	INGAME,
	MANNERS,
	END,
};

Object currentPlayer1;
Object currentPlayer2;

//현재 게임 상태
GAME game = GAME::MENU;

bool OnCheck = false;

int coolTime = 3;

//메뉴 화면 출력
void mainMenu();
//게임 화면 출력
void render();
//게임정보 업데이트
void update();
//게임 방법
void mainManner();
//맵 출력
void printMap();
//입력
void inInput();
//종료화면
void mainEND();
//게임 설정 초기화
void Init();
//폭탄 생성및 체크
void CheckBoob(Object boob,int Length);
//HP 출력
void PrintPlayerHp();
//핵 
void HACK();