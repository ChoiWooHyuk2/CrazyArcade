#pragma once
#include <Windows.h>
class DoubleBuffer
{
public:
	HANDLE GetBuffer();


	void CreateBuffer(const int &width, const int & height);
	void WriteBuffer(int x, int y, const char * string);
	void FlippingBuffer();
	void ClearBuffer();
	void DestoryBuffer();

private:
	int m_BufferIndex;
	HANDLE m_hBuffer[2];
	bool CloseHandle(HANDLE& handle);

public:
	DoubleBuffer();
	~DoubleBuffer();
};