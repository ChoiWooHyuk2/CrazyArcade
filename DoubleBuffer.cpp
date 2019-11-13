#include "DoubleBuffer.h"




bool DoubleBuffer::CloseHandle(HANDLE & handle)
{
	if (INVALID_HANDLE_VALUE != handle)
	{
		__try
		{//CloseHandle 과 다른애임 이름은 같지만.
			return { 0 != ::CloseHandle(handle) };
		}
		__finally
		{
			handle = INVALID_HANDLE_VALUE;
		}
	}
}

DoubleBuffer::DoubleBuffer()
{
	m_BufferIndex = 0;
}


DoubleBuffer::~DoubleBuffer()
{
}

HANDLE DoubleBuffer::GetBuffer()
{
	return m_hBuffer[m_BufferIndex];
}

void DoubleBuffer::CreateBuffer(const int & width, const int & height)
{
	CONSOLE_CURSOR_INFO cci; //콘솔창 커서 정보
	COORD size = { width, height }; // 버퍼 크기를 저장하는 구조체 
	SMALL_RECT rect; // 창 크기를 저장하는 구조체

	rect.Left = 0;
	rect.Top = 0;
	rect.Right = width - 1;
	rect.Bottom = height - 1;

	//0 번 버퍼생성                            //접근권환 읽기, 쓰기 가능 ,공유설정,보안속성   ,버퍼타입설정 
	m_hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	SetConsoleScreenBufferSize(m_hBuffer[0], size); // 버퍼크기 설정
	SetConsoleWindowInfo(m_hBuffer[0], TRUE, &rect); //창 크기 설정
	//1 번 버퍼 생성
	m_hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	SetConsoleScreenBufferSize(m_hBuffer[1], size); // 버퍼크기 설정
	SetConsoleWindowInfo(m_hBuffer[1], TRUE, &rect); //  창 크기 설정

	cci.dwSize = 1;
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(m_hBuffer[0], &cci); //깜빡이는 커서삭제
	SetConsoleCursorInfo(m_hBuffer[1], &cci);
}

void DoubleBuffer::WriteBuffer(int x, int y, const char * string)
{
	DWORD dw;    //자표값을 가짐
	COORD CursorPosition = { x, y }; // 자표위치

	//버퍼내에서 좌표 이동
	SetConsoleCursorPosition(m_hBuffer[m_BufferIndex], CursorPosition);
	WriteFile(m_hBuffer[m_BufferIndex], string, strlen(string), &dw, NULL);

}

void DoubleBuffer::FlippingBuffer()
{ 
	//버퍼 활성화 / 화면의 출력
	SetConsoleActiveScreenBuffer(m_hBuffer[m_BufferIndex]);
	//다음 버퍼 선택
	m_BufferIndex = !m_BufferIndex;
}

void DoubleBuffer::ClearBuffer()
{
	COORD coord = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(m_hBuffer[m_BufferIndex], ' ', 1280 * 720, coord, &dw);
}

void DoubleBuffer::DestoryBuffer()
{
	CloseHandle(m_hBuffer[0]);
	CloseHandle(m_hBuffer[1]);
}