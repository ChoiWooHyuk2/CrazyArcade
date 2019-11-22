#include "main.h"
Input input;
DoubleBuffer doubleBuffer;
void mainManner()
{
	char Buffer1[40];
	sprintf_s(Buffer1, sizeof(Buffer1), "현재 폭탄 쿨타임 : %d", coolTime);
	char Buffer2[40];
	sprintf_s(Buffer2, sizeof(Buffer2), "플레이어 1 의 폭탄길이  : %d", Player1.BoobLength);
	char Buffer3[40];
	sprintf_s(Buffer3, sizeof(Buffer3), "플레이어 2 의 폭탄길이  : %d", Player2.BoobLength);


	doubleBuffer.WriteBuffer(10, 6, "게임방법        뒤로가기 : ESC");
	doubleBuffer.WriteBuffer(10, 12, "플레이어 1 조작키");
	doubleBuffer.WriteBuffer(10, 14, "위: W   아래 : S   왼쪽 : A   오른쪽 : D   폭탄설치 : F");
	doubleBuffer.WriteBuffer(10, 20, "플레이어 2 조작키");
	doubleBuffer.WriteBuffer(10, 22, "위: ↑   아래 : ↓   왼쪽 : ←   오른쪽 : →   폭탄설치 : K");
	doubleBuffer.WriteBuffer(90, 12, "핵으로 테스트 하기");
	doubleBuffer.WriteBuffer(90, 14, "O : 쿨타임 감소   P : 쿨타임 증가   M : 폭탄길이 증가   H : 체력증가");
	doubleBuffer.WriteBuffer(90, 16, Buffer1);
	doubleBuffer.WriteBuffer(90, 18, Buffer2);
	doubleBuffer.WriteBuffer(90, 20, Buffer3);
		if (input.GetKeyDown(VK_ESCAPE))
		{
			PlaySound(L"fight.wav", NULL, SND_ASYNC | SND_LOOP | SND_NOSTOP);
			game = GAME::MENU;
		}
		else if (input.GetKeyDown(VK_ESCAPE))
			exit(0);
		//핵
		HACK();
}

void printMap()
{//y
	for (int y = 0; y < 20; y++)
	{//x
		for (int x = 0; x < 30; x++)
		{
			if (x % 2 == 0) {
				if (Map[x][y].block == true)
				{
					if (Map[x][y].Hp <= 0)
						Map[x][y].block = false;
					if(Map[x][y].Hp == 3)
					doubleBuffer.WriteBuffer(x, y, "▣");
					else if (Map[x][y].Hp == 2)
						doubleBuffer.WriteBuffer(x, y, "■");
					else if (Map[x][y].Hp == 1)
						doubleBuffer.WriteBuffer(x, y, "□");
					else if (Map[x][y].Hp <= 4000 && Map[x][y].Hp >= 4)
						doubleBuffer.WriteBuffer(x, y, "▣");
				}
			}
		}
	}
}


void inInput()
{
		if(Map[Player1.x - 2][Player1.y].block != true)
		if (input.GetKeyDown('A'))
		{
			Player1.x -= 2;
		}
		if (Map[Player1.x + 2][Player1.y].block != true)
		if (input.GetKeyDown('D'))
		{
			Player1.x += 2;
		}
		if (Map[Player1.x][Player1.y - 1].block != true)
		if (input.GetKeyDown('W'))
		{
			Player1.y -= 1;
		}
		if (Map[Player1.x][Player1.y + 1].block != true)
		if (input.GetKeyDown('S'))
		{
			Player1.y += 1;
		}
		if (Map[Player2.x - 2][Player2.y].block != true)
		if (input.GetKeyDown(VK_LEFT))
		{
			Player2.x -= 2;
		}
		if (Map[Player2.x + 2][Player2.y].block != true)
		if (input.GetKeyDown(VK_RIGHT))
		{
			Player2.x += 2;
		}
		if (Map[Player2.x][Player2.y + 1].block != true)
		if (input.GetKeyDown(VK_DOWN))
		{
			Player2.y += 1;
		}
		if (Map[Player2.x][Player2.y - 1].block != true)
		if (input.GetKeyDown(VK_UP))
		{
			Player2.y -= 1;
		}
}

void mainEND()
{
	doubleBuffer.WriteBuffer(10, 10, "게임엔드");
	doubleBuffer.WriteBuffer(10, 12, "메인가기 SPACE");

	if (Player1.Hp <= 0 && Player2.Hp > 0)
	{
		doubleBuffer.WriteBuffer(10, 14, "플레이어2 승리");
	}
	else if (Player2.Hp <= 0 && Player1.Hp > 0)
	{
		doubleBuffer.WriteBuffer(10, 14, "플레이어1 승리");
	}
	if (input.GetKeyDown(VK_SPACE))
	{
		Init();
		PlaySound(L"fight.wav", NULL, SND_ASYNC | SND_LOOP | SND_NOSTOP);
		game = GAME::MENU;
	}
}

void Init()
{
	Player1.x = 2; 
	Player1.y = 1;
	Player2.x = 26;
	Player2.y = 18;
	Player1.Hp = 10;
	Player2.Hp = 10;
	Player1.BoobLength = 4;
	Player2.BoobLength = 4;
	Player1.player = Player::Playercheck1;
	Player2.player = Player::Playercheck2;
	//y
	for (int y = 0; y < 20; y++)
	{//x
		for (int x = 0; x < 30; x++)
		{
			Map[x][y].x = x;
			Map[x][y].y = y;
			Map[x][y].Hp = 3;
			if (x == 0 || y == 19 || y == 0 || x == 28)
			{
				if(x%2 == 0)
					Map[x][y].Hp = 4000;
				Map[x][y].block = true;
			}
			else
			{
				Map[x][y].block = false;
			}
		}
	}
	Writeboob1 = false;
	Writeboob2 = false;

	Player1coolTime = 1700000000;
	Player2coolTime = 1700000000;

	Map[4][5].block = true;
	Map[6][5].block = true;
	Map[8][5].block = true;
	Map[10][5].block = true;
	Map[12][5].block = true;
	Map[14][5].block = true;
	Map[16][5].block = true;
	Map[18][5].block = true;
	Map[20][5].block = true;
	Map[22][5].block = true;
	Map[24][5].block = true;

	Map[4][8].block = true;
	Map[4][9].block = true;
	Map[4][10].block = true;
	Map[4][11].block = true;
	Map[10][8].block = true;
	Map[10][9].block = true;
	Map[10][10].block = true;
	Map[10][11].block = true;
	Map[18][8].block = true;
	Map[18][9].block = true;
	Map[18][10].block = true;
	Map[18][11].block = true;
	Map[24][8].block = true;
	Map[24][9].block = true;
	Map[24][10].block = true;
	Map[24][11].block = true;


	Map[4][14].block = true;
	Map[6][14].block = true;
	Map[8][14].block = true;
	Map[10][14].block = true;
	Map[12][14].block = true;
	Map[14][14].block = true;
	Map[16][14].block = true;
	Map[18][14].block = true;
	Map[20][14].block = true;
	Map[22][14].block = true;
	Map[24][14].block = true;

	game = MENU;
}



void CheckBoob(Object boob, int Length)
{
	for (int i = 0; i < Length; i++) {
		if (Map[boob.x + i * 2][boob.y].block == true) {
			Map[boob.x + i * 2][boob.y].Hp -= 1;
			break;
		}
		if (Player1.player == boob.player) {
			if (Player2.x == boob.x + i * 2 && Player2.y == boob.y) {
				Player2.Hp -= 1;
				break;
			}
		}
		if (Player2.player == boob.player) {
			if (Player1.x == boob.x + i * 2 && Player1.y == boob.y) {
				Player1.Hp -= 1;
				break;
			}
		}
			doubleBuffer.WriteBuffer(boob.x + i * 2,boob.y,"■");
		
	}

	for (int i = 0; i < Length; i++) {
		if (Map[boob.x - i * 2][boob.y].block == true) {
			Map[boob.x - i * 2][boob.y].Hp -= 1;
			break;
		}
		if (Player1.player == boob.player) {
			if (Player2.x == boob.x - i * 2 && Player2.y == boob.y) {
				Player2.Hp -= 1;
				break;
			}
		}
		if (Player2.player == boob.player) {
			if (Player1.x == boob.x - i * 2 && Player1.y == boob.y) {
				Player1.Hp -= 1;
				break;
			}
			
		}
			doubleBuffer.WriteBuffer(boob.x - i * 2, boob.y, "■");
		
	}

	for (int i = 0; i < Length; i++) {
		if (Map[boob.x][boob.y + i].block == true) {
			Map[boob.x][boob.y + i].Hp -= 1;
			break;
		}
		if (Player1.player == boob.player) {
			if (Player2.x == boob.x && Player2.y + i == boob.y) {
				Player2.Hp -= 1;
				break;
			}
		}
		if (Player2.player == boob.player) {
			if (Player1.x == boob.x && Player1.y + i == boob.y) {
				Player1.Hp -= 1;
				break;
			}
		}
			doubleBuffer.WriteBuffer(boob.x, boob.y + i, "■");
	}

	for (int i = 0; i < Length; i++) {
		if (Map[boob.x][boob.y - i].block == true) {
			Map[boob.x][boob.y - i].Hp -= 1;
			break;
		}
		if (Player1.player == boob.player) {
			if (Player2.x == boob.x && Player2.y - i == boob.y) {
				Player2.Hp -= 1;
				break;
			}
		}
		if (Player2.player == boob.player) {
			if (Player1.x == boob.x && Player1.y - i == boob.y) {
				Player1.Hp -= 1;
				break;
			}
		}
			doubleBuffer.WriteBuffer(boob.x, boob.y - i, "■");
	}
}

void PrintPlayerHp()
{
	char Buffer1[20];
	char Buffer2[20];
	sprintf_s(Buffer1, sizeof(Buffer1), "Player1 HP :%d", Player1.Hp);
	sprintf_s(Buffer2, sizeof(Buffer2), "Player2 HP :%d", Player2.Hp);
	doubleBuffer.WriteBuffer(40,10,Buffer1);
	doubleBuffer.WriteBuffer(40, 12, Buffer2);
}

void HACK()
{
	//핵
	if (input.GetKeyDown('H'))
	{
		Player1.Hp += 1;
		Player2.Hp += 1;
	}

	if (input.GetKeyDown('M'))
	{
		Player1.BoobLength += 1;
		Player2.BoobLength += 1;
	}
	if (input.GetKeyDown('O'))
	{
		coolTime -= 1;
	}
	if (input.GetKeyDown('P'))
	{
		coolTime += 1;
	}
}


void mainMenu()
{
	if (sound) {
		PlaySound(L"fight.wav", NULL, SND_ASYNC | SND_LOOP | SND_NOSTOP);
		sound = false;
	}
	doubleBuffer.WriteBuffer(3, 2, "  /$$$$$$                                                /$$$$$$                                      /$$          ");
	doubleBuffer.WriteBuffer(3, 3, " /$$__  $$                                              /$$__  $$                                    | $$          ");
	doubleBuffer.WriteBuffer(3, 4, "| $$  \__/  /$$$$$$  /$$$$$$  /$$$$$$$$  /$$   /$$      | $$  \ $$  /$$$$$$   /$$$$$$$  /$$$$$$    /$$$$$$$ /$$$$$$ ");
	doubleBuffer.WriteBuffer(3, 5, "| $$       /$$__  $$|____  $$|____ /$$/| $$  | $$      | $$$$$$$$ /$$__  $$ /$$_____/ |____  $$ /$$__  $$ /$$__  $$");
	doubleBuffer.WriteBuffer(3, 6, "| $$      | $$  \__/  /$$$$$$$   /$$$$/ | $$  | $$      | $$__  $$| $$  \__/| $$         /$$$$$$$| $$  | $$| $$$$$$$$");
	doubleBuffer.WriteBuffer(3, 7, "| $$    $$| $$      /$$__  $$  /$$__/  | $$  | $$      | $$  | $$| $$      | $$       /$$__  $$| $$  | $$| $$_____/");
	doubleBuffer.WriteBuffer(3, 8, "|  $$$$$$/| $$     |  $$$$$$$ /$$$$$$$$|  $$$$$$$      | $$  | $$| $$       | $$$$$$$|  $$$$$$$|  $$$$$$$|  $$$$$$$");
	doubleBuffer.WriteBuffer(3, 9, " \______/ |__/      \_______/|________/    \____  $$      |__/  |__/|__/       \_______/ \_______/ \_______/ \_______/");
	doubleBuffer.WriteBuffer(3, 10, "                                        /$$  | $$                                                                  ");
	doubleBuffer.WriteBuffer(3, 11, "                                       |  $$$$$$/                                                                  ");
	doubleBuffer.WriteBuffer(3, 12, "                                        \______/                                                                   ");


	doubleBuffer.WriteBuffer(50, 17, "게임시작 : SPACE");
	doubleBuffer.WriteBuffer(50, 19, "게임방법 : TAB");
	doubleBuffer.WriteBuffer(50, 21, "게임종료 : ESC");
	if (_kbhit())
	{
		if (input.GetKeyDown(VK_SPACE))
		{
			PlaySound(L"round_end.wav", NULL, SND_ASYNC);
			game = GAME::INGAME;
		}
		else if (input.GetKeyDown(VK_TAB))
			game = GAME::MANNERS;
		else if (input.GetKeyDown(VK_ESCAPE))
			exit(0);
	}
}

void render()
{
	printMap();
	if(Player1.Hp > 0)
	doubleBuffer.WriteBuffer(Player1.x, Player1.y, "★");

	if (Player2.Hp > 0)
	doubleBuffer.WriteBuffer(Player2.x, Player2.y, "☆");
}

void update()
{
	
	PrintPlayerHp();
	currentTime = time(0);

	if (input.GetKeyDown(VK_ESCAPE))
		exit(-1);
	//player2
	if (input.GetKeyDown('K') && Player2.Hp > 0 && Player2coolTime == 1700000000)
	{	
		currentPlayer2 = Player2;
		Player2coolTime = time(0);
		Writeboob2 = true;
	}
	//player1
	if (input.GetKeyDown('F') && Player2.Hp > 0 && Player1coolTime == 1700000000)
	{
		currentPlayer1 = Player1;
		Player1coolTime = time(0);
		Writeboob1 = true;
	}
	

	if (Writeboob1)
	{
		doubleBuffer.WriteBuffer(currentPlayer1.x,currentPlayer1.y,"#");
	}

	if (Writeboob2)
	{
		doubleBuffer.WriteBuffer(currentPlayer2.x, currentPlayer2.y, "#");
	}

	//폭탄소환 player2
	if (currentTime - Player2coolTime >= coolTime)
	{
		PlaySound(L"boom1.wav", NULL, SND_ASYNC );
		Writeboob2 = false;
		CheckBoob(currentPlayer2, currentPlayer2.BoobLength);
		Player2coolTime = 1700000000;
	}
	//폭탄소환 player1
	if (currentTime - Player1coolTime >= coolTime)
	{
		PlaySound(L"boom1.wav", NULL, SND_ASYNC );
		Writeboob1 = false;
		CheckBoob(currentPlayer1, currentPlayer1.BoobLength);
		Player1coolTime = 1700000000;
	}

	if (Player1.Hp <= 0 || Player2.Hp <= 0) {
		game = GAME::END;
		PlaySound(L"death.wav", NULL, SND_ASYNC);
	}
	HACK();
}

int main()
{

	Init();

	
	doubleBuffer.CreateBuffer(1280,720);
	while (true)
	{
		input.UpdateKeyState();
		doubleBuffer.ClearBuffer();
		switch (game)
		{
		case MENU:
			mainMenu();
			break;
		case INGAME:
			inInput();
			update();
			render();
			break;
		case MANNERS:
			mainManner();
			break;
		case END:
			mainEND();
			break;
		}
		Sleep(1000/60);
		doubleBuffer.FlippingBuffer();
	}
	doubleBuffer.DestoryBuffer();
}