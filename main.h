#pragma once
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include "Input.h" 
#include "DoubleBuffer.h"

//�÷��̾�
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

//���� �������
enum GAME
{
	MENU,
	INGAME,
	MANNERS,
	END,
};

Object currentPlayer1;
Object currentPlayer2;

//���� ���� ����
GAME game = GAME::MENU;

bool OnCheck = false;

int coolTime = 3;

//�޴� ȭ�� ���
void mainMenu();
//���� ȭ�� ���
void render();
//�������� ������Ʈ
void update();
//���� ���
void mainManner();
//�� ���
void printMap();
//�Է�
void inInput();
//����ȭ��
void mainEND();
//���� ���� �ʱ�ȭ
void Init();
//��ź ������ üũ
void CheckBoob(Object boob,int Length);
//HP ���
void PrintPlayerHp();
//�� 
void HACK();