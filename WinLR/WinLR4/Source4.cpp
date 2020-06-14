#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <tchar.h>
#include <process.h>
#include "commctrl.h"

using namespace std;

#define MAX_LOADSTRING 100
#define PATH L"C:\\Users\\lesh7\\OneDrive\\������� ����\\������\\WinLR1\\WinLR4\\test.txt"

HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND hWnd, // ���������� ������
	UINT, // ���������, ���������� ��
	WPARAM, // ���������
	LPARAM); // ���������, ��� ������������ ���������

TCHAR WinName[] = _T("LR4");

int WINAPI _tWinMain(HINSTANCE This,		 // ���������� �������� ���������� 
	HINSTANCE Prev, 	// � ����������� �������� ������ 0 
	LPTSTR cmd, 		// ��������� ������ 
	int mode) 		// ����� ����������� ����
{
	HWND hWnd;		// ���������� �������� ���� ���������, ��� �������� ���������� � ����� ����, ��������� �� ������������ ������� ������ � ����
	MSG msg; 		// ��������� ��� �������� ��������� 
	WNDCLASS wc; 	// ��������� �������� �� �������������� ����
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// ��� ������ ���� 
	wc.lpfnWndProc = WndProc; 					// ������� ���� 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// ����� ���� 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// ����������� ������ 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// ����������� ������ 
	wc.lpszMenuName = NULL; 					// ��� ���� 
	wc.cbClsExtra = 0; 						// ��� �������������� ������ ������ 
	wc.cbWndExtra = 0; 						// ��� �������������� ������ ���� 
	wc.hbrBackground = CreateSolidBrush(RGB(38, 201, 255));// ���������� ���� ������


	// ����������� ������ ����
	if (!RegisterClass(&wc)) return 0;
	hInst = This; // ��������� ������ ���������� � ���������� ����������
	// �������� ���� 
	hWnd = CreateWindow(WinName,			// ��� ������ ���� 
		_T("Lab4"), 		// ��������� ���� 
		WS_OVERLAPPEDWINDOW, 		// ����� ���� 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 ������� ���� 
		550, 				// width 
		600, 				// Height 
		HWND_DESKTOP, 				// ���������� ������������� ���� 
		NULL, 						// ��� ���� 
		This, 						// ���������� ���������� 
		NULL); 					// �������������� ���������� ��� 

	HMENU hmenu1;
	hmenu1 = CreateMenu();
	HMENU hPopupMenu = CreatePopupMenu();
	AppendMenu(hmenu1, MF_STRING | MF_POPUP, (UINT)hPopupMenu, L"&������ �������");
	{
		AppendMenu(hPopupMenu, MF_STRING, 1000, L"�������");
		AppendMenu(hPopupMenu, MF_STRING, 1001, L"���������");
	}
	HMENU hPopupMenu1 = CreatePopupMenu();
	AppendMenu(hmenu1, MF_STRING | MF_POPUP, (UINT)hPopupMenu1, L"&���������� �������");
	{
		AppendMenu(hPopupMenu1, MF_STRING, 1002, L"�������");
		AppendMenu(hPopupMenu1, MF_STRING, 1003, L"���������");
	}
	AppendMenu(hmenu1, MF_STRING, 0, L"&�����");
	SetMenu(hWnd, hmenu1);
	ShowWindow(hWnd, mode);
	UpdateWindow(hWnd);			// �������� ����

	// ���� ��������� ��������� 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// ������� ���������� ����� ������� ������� 
		DispatchMessage(&msg); 		// �������� ��������� ������� WndProc() 
	}
	return 0;
}

HANDLE hTable;
HANDLE hDiagram;
DWORD WINAPI Table(LPVOID t);
DWORD WINAPI Diagram(LPVOID t);

int a = 0;
BOOL Prov1 = false;
BOOL Prov2 = false;


LPWSTR convertStr(LPCSTR pInStr)//��������������LPCSTR � LPWSTR
{
	int length = strlen(pInStr);
	wchar_t* pwstr = new wchar_t[length];
	int result = MultiByteToWideChar(
		CP_ACP, MB_PRECOMPOSED, pInStr, length,
		pwstr, length
	);
	pwstr[length] = L'\0';
	return LPWSTR(pwstr);
}

//map <int,int> names = { {1,11}, {2,12}, {3,9}, {4,12}, {5,16}, {6,8}, {7,15}, {8,7}, {9,13}, {10,13}, {11,13}, {12,11}, {13,9} };

DWORD WINAPI Table(LPVOID t)
{
	OVERLAPPED olf = { 0 };//������� ������
	LARGE_INTEGER li = { 0 };
	li.QuadPart = 1;
	olf.Offset = li.LowPart;//������� ����� ������� � �����
	olf.OffsetHigh = li.HighPart;//������� �����

	LPSTR buffer = (CHAR*)calloc(300, sizeof(CHAR));
	DWORD iNumread = 0;

	DWORD dwCounter, dwTemp;
	HANDLE hFile = CreateFile(PATH, GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (!ReadFile(hFile, buffer, 300, &iNumread, &olf)) {
		return 1;
	}

	int i = 1;
	int k = 0;

	while (Prov1)
	{
		RECT rect;
		PAINTSTRUCT ps;
		GetClientRect(HWND(t), &rect);
		std::cout << "p" << std::endl;
		LPCWSTR new_buf = convertStr(buffer);
		HDC hdc = GetDC(HWND(t));
		SelectObject(hdc, GetStockObject(DC_PEN));
		SetDCPenColor(hdc, RGB(38, 201, 255));
		SelectObject(hdc, CreateSolidBrush(RGB(38, 201, 255)));
		Rectangle(hdc, 50, 50, 400, 305);
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);
//		TextOut(hdc, 210, 100, new_buf + k, names[i]);
		EndPaint(HWND(t), &ps);
		Sleep(1000);
//		k += names[i];
		++i;
		if (i == 13) {
			i = 1;
			k = 0;
		}
	}

	return 0;
}


DWORD WINAPI Diagram(LPVOID t)
{
	bool left_side = true;

	while (Prov2) {

		RECT rect;
		PAINTSTRUCT ps;
		GetWindowRect(HWND(t), &rect);
		int width = (int)(rect.right - rect.left);
		int height = (int)(rect.bottom - rect.top);
		HDC hdc = GetDC(HWND(t));
		HBRUSH hBrush;
		hBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(38, 201, 255));

		if (left_side) {
			HPEN hPen1;
			hPen1 = CreatePen(PS_SOLID, 5, RGB(rand() % 255, rand() % 255, rand() % 255));
			::MoveToEx(hdc, 250, 400, NULL);
			SelectObject(hdc, hPen1);
			::LineTo(hdc, 250, 450);
			::MoveToEx(hdc, 150, 350, NULL);
			SelectObject(hdc, hPen1);
			::LineTo(hdc, 350, 450);
			Sleep(500);
			SelectObject(hdc, GetStockObject(DC_PEN));
			SetDCPenColor(hdc, RGB(38, 201, 255));
			SelectObject(hdc, CreateSolidBrush(RGB(38, 201, 255)));
			Rectangle(hdc, 110, 470, 360, 340);
			ReleaseDC(HWND(t), hdc);

			::SelectObject(hdc, (HGDIOBJ)hBrush);
			::DeleteObject(hBrush);
			left_side = false;


		}
		else
		{

			HPEN hPen2;
			hPen2 = CreatePen(PS_SOLID, 5, RGB(rand() % 255, rand() % 255, rand() % 255));
			::MoveToEx(hdc, 250, 400, NULL);
			SelectObject(hdc, hPen2);
			::LineTo(hdc, 250, 450);
			::MoveToEx(hdc, 350, 350, NULL);
			SelectObject(hdc, hPen2);
			::LineTo(hdc, 150, 450);
			Sleep(500);
			SelectObject(hdc, GetStockObject(DC_PEN));
			SetDCPenColor(hdc, RGB(38, 201, 255));
			SelectObject(hdc, CreateSolidBrush(RGB(38, 201, 255)));
			Rectangle(hdc, 110, 470, 360, 340);
			ReleaseDC(HWND(t), hdc);
			left_side = true;
		}
	}
	return 0;
}





LRESULT CALLBACK WndProc(HWND hWnd,//���������� ����
	UINT message,//��� ���������
	WPARAM wParam,//���������, ��� �������� ���������� ��� ���������
	LPARAM lParam)//���������, ��� �������� ���������� ��� ���������
{
	switch (message)		 // ���������� ���������
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// ��������� ����� � ����:
		switch (wmId)
		{
		case 1000:
		{
			Prov1 = true;
			hTable = CreateThread(NULL, 0, Table, hWnd, 0, NULL);
			break;
		}
		case 1001:
		{
			Prov2 = true;
			hDiagram = CreateThread(NULL, 0, Diagram, hWnd, 0, NULL);
			break;
		}
		case 1002:
		{
			TerminateThread(hTable, 0);
			_endthread;
			Prov1 = false;
			break;
		}
		case 1003:
		{

			TerminateThread(hDiagram, 0);
			Prov2 = false;
			break;

		}
		case 0:
		{
			DestroyWindow(hWnd);
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break; 			// ���������� ��������� 
	default: 			// ��������� ��������� �� ��������� 
		return DefWindowProc(hWnd, message, wParam, lParam);//���� ��������� ����� �� ��������������
	}

	return 0;
}