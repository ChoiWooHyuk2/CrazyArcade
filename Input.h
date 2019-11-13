#pragma once
#include <Windows.h>
#include <WinUser.h>
class Input
{
	
public:
	Input();
	~Input();

private:
	int mouseX;
	int mouseY;

public:
	int GetMouseX();
	int GetMouseY();

public:
	bool lkey[256], rkey[256];
	void UpdateKeyState();

public:
	int GetMyKeyState(int vk);
	bool GetKeyDown(int vk);
	bool GetKeyPressed(int vk);
	bool GetKeyUp(int vk);
};