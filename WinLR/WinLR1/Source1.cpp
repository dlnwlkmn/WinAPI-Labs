#include <Windows.h>
#include <tchar.h>

#define ID_TIMER1   1
#define ID_TIMER2   2


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void CALLBACK TimerProc(HWND hwnd, UINT Msg, UINT iTimerID,
	DWORD dwTimer)
{
}




TCHAR WinName[] = _T("���� 1 (�����-�����-������)");

int WINAPI _tWinMain(HINSTANCE This,		 // ���������� �������� ���������� 
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
	wc.hbrBackground = CreateSolidBrush(RGB(255, 251, 0));// ���������� ���� ������ 38, 201, 255


	// ����������� ������ ����
	if (!RegisterClass(&wc)) return 0;

	// �������� ���� 
	hWnd = CreateWindow(WinName,			// ��� ������ ���� 
		_T("������ Windows-����������"), 		// ��������� ���� 
		WS_OVERLAPPEDWINDOW, 		// ����� ���� 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 ������� ���� 
		CW_USEDEFAULT, 				// width 
		CW_USEDEFAULT, 				// Height 
		HWND_DESKTOP, 				// ���������� ������������� ���� 
		NULL, 						// ��� ���� 
		This, 						// ���������� ���������� 
		NULL); 					// �������������� ���������� ��� 

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

bool Left = false, Right = true;
int time = 0, counter = 0;
bool timerr = false, drawText = true, drawEllipse = true;
wchar_t text[255];
wchar_t text1[255];

LRESULT CALLBACK WndProc(HWND hWnd,//���������� ����
	UINT message,//��� ���������
	WPARAM wParam,//���������, ��� �������� ���������� ��� ���������
	LPARAM lParam)//���������, ��� �������� ���������� ��� ���������
{
	switch (message)		 // ���������� ���������
	{
	case WM_TIMER:
	{
		counter++;
		timerr = true;
		InvalidateRect(hWnd, nullptr, true);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;// �������� ���������� ��� ����������. ��� ���������� ����� ���� ������������ ��� ������� ���������� ������� ����, ������� ������� ����������.
		HDC hdc = BeginPaint(hWnd, &ps);//���������� �������� ���������� �������, ������������ ��� ���������
		if (drawEllipse == true)
		{
			//������� ��������� ���������� ������ �� ���������������� ������, ������, ������� ��� ������.
			SelectObject(hdc, GetStockObject(DC_PEN));
			//���� ����
			SetDCPenColor(hdc, RGB(41, 255, 201));

			//������� ���������� �����, ������� ����� �������� �������� ���.
			SelectObject(hdc, CreateSolidBrush(RGB(41, 255, 201)));
			Ellipse(hdc, 150, 200, 450, 250);
		}
		if (drawText == true)
		{
			wsprintf(text, TEXT("�������� ������� ��5-44� ��1 WinAPI"));
			SetBkMode(hdc, TRANSPARENT); //����� ���� ��� �������
			SetTextColor(hdc, RGB(0, 0, 255)); //��� ���� ������
			TextOut(hdc, 162, 217, text, 35);

		}

		EndPaint(hWnd, &ps);

		if (counter == 4)
		{
			drawText = false;
			timerr = false;
			//InvalidateRect(hWnd, NULL, false);
		}
		if (counter == 10)
		{
			drawEllipse = false;
			timerr = false;
			//InvalidateRect(hWnd, NULL, false);
		}

		if (Left) {
			Left = false;
		}

		if (Right) {
			Right = false;
		}
		
	}
	break;
	case WM_LBUTTONDOWN:
	{
		SetTimer(hWnd, ID_TIMER1, 1000, nullptr);
		Left = true;
		InvalidateRect(hWnd, NULL, false);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		Right = true;
		drawEllipse = true;
		drawText = true;
		KillTimer(hWnd, ID_TIMER1);
		counter = 0;
		InvalidateRect(hWnd, NULL, false);
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


//// WINAPI1.cpp : ���������� ����� ����� ��� ����������.
////
//
//#include "stdafx.h"
//#include "WINAPI1.h"
//
//#define MAX_LOADSTRING 100
//
//// ���������� ����������:
//HINSTANCE hInst;                                // ������� ���������
//WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
//WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����
//
//// ��������� ���������� �������, ���������� � ���� ������ ����:
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//
//int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//                     _In_opt_ HINSTANCE hPrevInstance,
//                     _In_ LPWSTR    lpCmdLine,
//                     _In_ int       nCmdShow)
//{
//    UNREFERENCED_PARAMETER(hPrevInstance);
//    UNREFERENCED_PARAMETER(lpCmdLine);
//
//    // TODO: ���������� ��� �����.
//
//    // ������������� ���������� �����
//    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//    LoadStringW(hInstance, IDC_WINAPI1, szWindowClass, MAX_LOADSTRING);
//    MyRegisterClass(hInstance);
//
//    // ��������� ������������� ����������:
//    if (!InitInstance (hInstance, nCmdShow))
//    {
//        return FALSE;
//    }
//
//    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI1));
//
//    MSG msg;
//
//    // ���� ��������� ���������:
//    while (GetMessage(&msg, nullptr, 0, 0))
//    {
//        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//        {
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//        }
//    }
//
//    return (int) msg.wParam;
//}
//
//
//
////
////  �������: MyRegisterClass()
////
////  ����: ������������ ����� ����.
////
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//    WNDCLASSEXW wcex;
//
//    wcex.cbSize = sizeof(WNDCLASSEX);
//
//    wcex.style          = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc    = WndProc;
//    wcex.cbClsExtra     = 0;
//    wcex.cbWndExtra     = 0;
//    wcex.hInstance      = hInstance;
//    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI1));
//    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
//    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
//    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPI1);
//    wcex.lpszClassName  = szWindowClass;
//    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//    return RegisterClassExW(&wcex);
//}
//
////
////   �������: InitInstance(HINSTANCE, int)
////
////   ����: ��������� ������ ���������� � ������� ������� ����
////
////   �����������:
////
////        � ���� ������� ������ ���������� ����������� � ���������� ����������, � �����
////        ��������� � ��������� ������� ���� ���������.
////
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//   hInst = hInstance; // ��������� ������ ���������� � ���������� ����������
//
//   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//
//   if (!hWnd)
//   {
//      return FALSE;
//   }
//
//   ShowWindow(hWnd, nCmdShow);
//   UpdateWindow(hWnd);
//
//   return TRUE;
//}
//
////
////  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
////
////  ����: ������������ ��������� � ������� ����.
////
////  WM_COMMAND  - ���������� ���� ����������
////  WM_PAINT    - ��������� �������� ����
////  WM_DESTROY  - ��������� ��������� � ������ � ���������
////
////
//bool Left = false, Right = false;
//int times_cl_l = 0, times_cl_r = 0;
//int x_koord = 0, y_koord = 0;
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    switch (message)
//    {
//    case WM_COMMAND:
//        {
//            int wmId = LOWORD(wParam);
//            // ��������� ����� � ����:
//            switch (wmId)
//            {
//            case IDM_ABOUT:
//                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//                break;
//            case IDM_EXIT:
//                DestroyWindow(hWnd);
//                break;
//            default:
//                return DefWindowProc(hWnd, message, wParam, lParam);
//            }
//        }
//        break;
//
//    case WM_PAINT:
//        {
//            PAINTSTRUCT ps;
//            HDC hdc = BeginPaint(hWnd, &ps);
//			if (Left == false && Right == false) {
//				//������� ��������� ���������� ������ �� ���������������� ������, ������, ������� ��� ������.
//				SelectObject(hdc, GetStockObject(DC_PEN));
//				//���� ����
//				SetDCPenColor(hdc, RGB(38, 201, 255));
//				//������� ���������� �����, ������� ����� �������� �������� ���.
//				SelectObject(hdc, CreateSolidBrush(RGB(255, 251, 0)));
//				Ellipse(hdc, 300, 300, 500, 500);
//			}
//
//
//			if (Left) {
//				SelectObject(hdc, GetStockObject(DC_PEN));
//				SelectObject(hdc, CreateSolidBrush(RGB(38, 201, 255)));
//				if (times_cl_l * 10 + x_koord <= 450) {
//					SetDCPenColor(hdc, RGB(38, 201, 255));
//					Ellipse(hdc, x_koord, y_koord, 80 + x_koord, 80 + y_koord);
//				}
//				Left = false;
//			}
//
//			if (Right) {
//				SelectObject(hdc, GetStockObject(DC_PEN));
//				SelectObject(hdc, CreateSolidBrush(RGB(38, 201, 255)));
//				if (times_cl_l * 10 + x_koord >= 390) {
//					SetDCPenColor(hdc, RGB(38, 201, 255));
//					Ellipse(hdc, x_koord, y_koord, 80 + x_koord, 80 + y_koord);
//				}
//				Right = false;
//			}
//            EndPaint(hWnd, &ps);
//        }
//        break;
//	case WM_LBUTTONDOWN:
//	{
//		Left = true;
//		x_koord = LOWORD(lParam);//������
//		y_koord = HIWORD(lParam);//������
//		if (times_cl_l != 10) {
//			++times_cl_l;
//		}
//		InvalidateRect(hWnd, NULL, false);
//	}
//	break;
//	case WM_RBUTTONDOWN:
//	{
//		Right = true;
//		x_koord = LOWORD(lParam);
//		y_koord = HIWORD(lParam);
//		if (times_cl_r != 10) {
//			++times_cl_r;
//		}
//		InvalidateRect(hWnd, NULL, false);
//	}
//	break;
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
//
//// ���������� ��������� ��� ���� "� ���������".
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}
