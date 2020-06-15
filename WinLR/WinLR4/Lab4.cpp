// lab4.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab4.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

int R = 100, G = 100, B = 100;

HBRUSH color_of_window = CreateSolidBrush(RGB(R, G, B)); // Цвет окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB4));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = color_of_window;
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB4);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
HWND hWnd;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   srand(time(0));
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

HANDLE thread_1; // поток чтения из файла
HANDLE thread_2; // поток для диаграммы

bool t1 = true;
bool t2 = true;

std::vector<int> v;
DWORD WINAPI thread1(LPVOID t) {
    InvalidateRect(hWnd, NULL, TRUE);
    std::ifstream openf("DATA.txt");
    int counter = 0;
    size_t i = 0;
    RECT rect;
    GetClientRect(hWnd, &rect);
    HDC hdc = GetDC(hWnd);
    SetTextColor(hdc, RGB(255, 255, 255));
    SetBkColor(hdc, RGB(R, G, B));
    while (!openf.eof())
    {
        while (!openf.eof() && t1 == true) {
            int a;
            openf >> a;
            v.push_back(a);
            counter++;
            if ((counter % 2) == 0)
            {
                break;
            }
        }

            for (i; i < v.size(); i++) {
                WCHAR m[10];
                wsprintf(m, TEXT("%d"), v[i]);
                TextOut(hdc, rect.left + 50, rect.top / 2 + 10 + i * 20, (LPWSTR)m, 3);
            }
        Sleep(2000);
    }
    return 0;
}

int red = 0, g = 0, b = 0;


//if (i == 5)
//{
//    Sleep(12000);
//}

DWORD WINAPI thread2(LPVOID t) {
    HDC hdc = GetDC(hWnd);
    float x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    while (t2) {
        for (size_t i = 0; i < v.size(); i++) {
            red = 255;
            g = 255;
            b = 255;

            HBRUSH brush = CreateSolidBrush(RGB(red, g, b));
            SelectObject(hdc, brush);

            RECT rect;
            GetClientRect(hWnd, &rect);
            Rectangle(hdc, rect.right - 10, 8 + i * 20, rect.right - v[i] - 0, 20 + i * 20);
            //Rectangle(hdc, rect.right-20, 10 + i*20, rect.right-v[i] - 20, 20 + i * 20);

            DeleteObject(brush);
        }
        Sleep(10000);
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_THREAD1ON:
                t1 = true;
                thread_1 = CreateThread(NULL, 0, &thread1, NULL, 0, NULL);
                break;
            case ID_THREAD1OFF:
                v.clear();
                TerminateThread(thread_1, NULL);
                TerminateThread(thread_2, NULL);
                t2 = false;
                t1 = false;
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            case ID_THREAD2ON:
                t2 = true;
                thread_2 = CreateThread(NULL, 0, &thread2, NULL, 0, NULL);
                break;
            case ID_THREAD2OFF:
                TerminateThread(thread_2, NULL);
                t2 = false;
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
