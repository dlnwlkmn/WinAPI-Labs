#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <iostream>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

WCHAR WinName[] = _TEXT("MainFrame");
WCHAR WinName2[] = _TEXT("MainFrame2");


int WINAPI wWinMain(HINSTANCE This,		 // ���������� �������� ���������� 
	HINSTANCE Prev, 	// � ����������� �������� ������ 0 
	LPTSTR cmd, 		// ��������� ������ 
	int mode) 		// ����� ����������� ����
{
	HWND hWnd;		// ���������� �������� ���� ��������� 
	MSG msg; 		// ��������� ��� �������� ��������� 
	WNDCLASS wc; 	// ����� ����
	// ����������� ������ ���� 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// ��� ������ ���� 
	wc.lpfnWndProc = WndProc; 					// ������� ���� 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// ����� ���� 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// ����������� ������ 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// ����������� ������ 
	wc.lpszMenuName = NULL; 					// ��� ���� 
	wc.cbClsExtra = 0; 						// ��� �������������� ������ ������ 
	wc.cbWndExtra = 0; 						// ��� �������������� ������ ���� 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// ���������� ���� ����� ������ 



	// ����������� ������ ����
	if (!RegisterClass(&wc)) return 0;

	// �������� ���� 
	hWnd = CreateWindow(WinName,			// ��� ������ ���� 
		_TEXT("���� � 1"), 		// ��������� ���� 
		WS_OVERLAPPEDWINDOW, 		// ����� ���� 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 ������� ���� 
		600, 				// width 
		500, 				// Height 
		HWND_DESKTOP, 				// ���������� ������������� ���� 
		NULL, 						// ��� ���� 
		This, 						// ���������� ���������� 
		NULL); 					// �������������� ���������� ��� 


	//SetWindowLong(, GWL_STYLE, WS_CHILD);
	ShowWindow(hWnd, mode); 				// �������� ����

	// ���� ��������� ��������� 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// ������� ���������� ����� ������� ������� 
		DispatchMessage(&msg); 		// �������� ��������� ������� WndProc() 
	}
	return 0;
}

// ������� ������� ���������� ������������ ��������
// � �������� ��������� �� ������� ��� ������� ����������

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND descriptor;
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		descriptor = FindWindow(WinName2, NULL);
		if (descriptor != NULL)
		{
			MessageBox(hWnd, _TEXT("���� �2 - �������!"), _TEXT("���������"), MB_OK);
			SendMessage(descriptor, WM_USER + 1, WPARAM(hWnd), NULL);
		}
		else
		{
			MessageBox(hWnd, _TEXT("���� �2 - �� ������� => �������"), _TEXT("���������"), MB_OK);
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case WM_RBUTTONDOWN:
	{
		descriptor = FindWindow(WinName2, NULL);
		if (descriptor != NULL)
		{
			MessageBox(hWnd, _TEXT("���� �2 - �������!"), _TEXT("���������"), MB_OK);
			SendMessage(descriptor, WM_USER + 2, WPARAM(hWnd), NULL);
		}
		else
		{
			MessageBox(hWnd, __TEXT("���� �2 - �� ������� => �������"), _TEXT("���������"), MB_OK);
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case WM_DESTROY:
		PostQuitMessage(0);
	default: 			// ��������� ��������� �� ��������� 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}