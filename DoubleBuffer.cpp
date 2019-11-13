#include "DoubleBuffer.h"




bool DoubleBuffer::CloseHandle(HANDLE & handle)
{
	if (INVALID_HANDLE_VALUE != handle)
	{
		__try
		{//CloseHandle �� �ٸ����� �̸��� ������.
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
	CONSOLE_CURSOR_INFO cci; //�ܼ�â Ŀ�� ����
	COORD size = { width, height }; // ���� ũ�⸦ �����ϴ� ����ü 
	SMALL_RECT rect; // â ũ�⸦ �����ϴ� ����ü

	rect.Left = 0;
	rect.Top = 0;
	rect.Right = width - 1;
	rect.Bottom = height - 1;

	//0 �� ���ۻ���                            //���ٱ�ȯ �б�, ���� ���� ,��������,���ȼӼ�   ,����Ÿ�Լ��� 
	m_hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	SetConsoleScreenBufferSize(m_hBuffer[0], size); // ����ũ�� ����
	SetConsoleWindowInfo(m_hBuffer[0], TRUE, &rect); //â ũ�� ����
	//1 �� ���� ����
	m_hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	SetConsoleScreenBufferSize(m_hBuffer[1], size); // ����ũ�� ����
	SetConsoleWindowInfo(m_hBuffer[1], TRUE, &rect); //  â ũ�� ����

	cci.dwSize = 1;
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(m_hBuffer[0], &cci); //�����̴� Ŀ������
	SetConsoleCursorInfo(m_hBuffer[1], &cci);
}

void DoubleBuffer::WriteBuffer(int x, int y, const char * string)
{
	DWORD dw;    //��ǥ���� ����
	COORD CursorPosition = { x, y }; // ��ǥ��ġ

	//���۳����� ��ǥ �̵�
	SetConsoleCursorPosition(m_hBuffer[m_BufferIndex], CursorPosition);
	WriteFile(m_hBuffer[m_BufferIndex], string, strlen(string), &dw, NULL);

}

void DoubleBuffer::FlippingBuffer()
{ 
	//���� Ȱ��ȭ / ȭ���� ���
	SetConsoleActiveScreenBuffer(m_hBuffer[m_BufferIndex]);
	//���� ���� ����
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