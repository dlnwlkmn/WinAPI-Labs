// dz.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "dz.h"
#include <math.h>
#include "../../../../../../../Program Files (x86)/Windows Kits/8.0/Include/um/WinUser.h"
#include <string>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

int param = _tstoi(_T("3"));

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
    LoadStringW(hInstance, IDC_DZ, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DZ));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DZ));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DZ);
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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, 1000, 750, nullptr, nullptr, hInstance, nullptr);

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

int StrToInt(char* s)
{
    int temp = 0; // число
    int i = 0;
    int sign = 0; // знак числа 0- положительное, 1 - отрицательное
    if (s[i] == '-')
    {
        sign = 1;
        i++;
    }
    while (s[i] >= 0x30 && s[i] <= 0x39)
    {
        temp = temp + (s[i] & 0x0F);
        temp = temp * 10;
        i++;
    }
    temp = temp / 10;
    if (sign == 1)
        temp = -temp;
    return(temp);
}

char* IntToStr(int n)
{
    char s[40], t, * temp;
    int i, k;
    int sign = 0;
    i = 0;
    k = n;
    if (k < 0)
    {
        sign = 1;
        k = -k;
    }
    do {
        t = k % 10;
        k = k / 10;
        s[i] = t | 0x30;
        i++;
    } while (k > 0);
    if (sign == 1)
    {
        s[i] = '-';
        i++;
    }
    temp = new char[i];
    k = 0;
    i--;
    while (i >= 0) {
        temp[k] = s[i];
        i--; k++;
    }
    temp[k] = '\0';
    return(temp);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //HINSTANCE hInst;
    static HWND hEdt1; // дескрипторы полей редактирования
    static bool build = true;
    char tmpparam;
    TCHAR tempparam[10];
    switch (message)
    {
    case WM_CREATE:
    {
        //hInst = ((LPCREATESTRUCT)lParam)->hInstance; // дескриптор приложения
        hEdt1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", NULL, WS_CHILD | WS_VISIBLE | ES_RIGHT,
            10, 10, 40, 20, hWnd, (HMENU)10000, hInst, NULL);
        ShowWindow(hEdt1, SW_SHOWNORMAL);
        SetWindowText(hEdt1, (LPCWSTR)IntToStr(param));
    }
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
            case IDM_BUILD:
            {
                build = true;
                GetWindowText(hEdt1, tempparam, 1);
                param = _tstoi(tempparam);
                    //StrToInt(tempparam); // считываем число из первого поля
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
            case IDM_UNBUILD:
            {
                build = false;
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
    {

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            MoveToEx(hdc, 0, 400, NULL);

            LineTo(hdc, 0, 350);
            LineTo(hdc, 10000, 350);

            MoveToEx(hdc, 600, 0, NULL);

            LineTo(hdc, 600, 0);
            LineTo(hdc, 600, 10000);

            RECT rect;
            GetClientRect(hWnd, &rect);
            TextOut(hdc, 610, 0, _T("90"), 2);
            TextOut(hdc, 20, 360, _T("180"), 3);
            TextOut(hdc, 610, rect.bottom - 40, _T("270"), 3);
            TextOut(hdc, rect.right - 100, 360, _T("0 / 360"), 8);

            /*float  r = 7;

            for (size_t i = 1; i <= 78; i += 7) {
                WCHAR Coord[5];
                wsprintf(Coord, TEXT("-%d"), i);
                TextOut(hdc, 620, 400 + r*i, Coord, 3);
                TextOut(hdc, 600 - r * i, 410, Coord, 3);
                wsprintf(Coord, TEXT("%d"), i);
                TextOut(hdc, 600 + r * i, 410, Coord, 3);
                TextOut(hdc, 620, 400 - r * i, Coord, 3);
            } */
            if (build == true)
            {
                for (float a = 0; a < 360; a += 0.1) {
                    float radius = param * cos(2 * a);
                    float y = radius * sin(a);
                    float x = radius * cos(a);
                    if (a == 0)
                        MoveToEx(hdc, 100 * x + 600, 100 * y + 350, NULL);
                    else
                        LineTo(hdc, 100 * x + 600, 100 * y + 350);
                }
            }

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
