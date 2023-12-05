#include <Windows.h>
#include <iostream>
#include"pvz.h"
#define IDB_ONE     3301
#define IDB_TWO     3302  
#define IDB_THREE   3303  
#define IDB_FOUR    3304 
bool visited = false ;
pvz p;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_SIZE: 
        if (wParam == SIZE_MAXIMIZED)
        {
            ShowWindow(hWnd, SW_RESTORE);
        }
        else if (wParam == SIZE_MINIMIZED)
        {
            ShowWindow(hWnd, SW_SHOWMINIMIZED);
        }
        break;
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDB_ONE:
            if (visited == false)
            {
                p.AotuCollect();
                MessageBox(hWnd, L"�Զ��ռ����⿪", L"��ʾ", MB_OK | MB_ICONINFORMATION);
                visited = true;
            }
            else
            {
                p.DownAotuCollect();
                MessageBox(hWnd, L"�Զ��ռ������", L"��ʾ", MB_OK | MB_ICONINFORMATION);
                visited = false;
            }
            break;
        case IDB_TWO:
            p.Kill_Common();
            MessageBox(hWnd, L"��ͨ��ʬһ����ɱ��", L"��ʾ", MB_OK | MB_ICONINFORMATION);
            break;
        case IDB_THREE:
            p.Kill_Second();
            MessageBox(hWnd, L"ñ�ӽ�ʬһ����ɱ��", L"��ʾ", MB_OK | MB_ICONINFORMATION);
            break;
        case IDB_FOUR:
            p.Editsun();
            MessageBox(hWnd, L"����1000����", L"��ʾ", MB_OK | MB_ICONINFORMATION);
            break;
        default:
            break;
        }
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    
    const wchar_t* className = L"MyWindowClass";
    const wchar_t* windowTitle = L"ֲ���ս��ʬ�޸���";
    const int windowWidth = 300;
    const int windowHeight = 300;

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = className;
    RegisterClass(&wc);

    HWND hWnd = CreateWindow(className, windowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);
    if (!hWnd)
    {
        std::cerr << "Failed to create window" << std::endl;
        return 1;
    }
    //����������ť  
    CreateWindow(L"Button", L"�Զ��ռ�����", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        75, 10, 150, 30, hWnd, (HMENU)IDB_ONE, hInstance, NULL);
    CreateWindow(L"Button", L"��ͨ��ʬһ����ɱ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        75, 80, 150, 30, hWnd, (HMENU)IDB_TWO, hInstance, NULL);
    CreateWindow(L"Button", L"ñ�ӽ�ʬһ����ɱ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        75, 150, 150, 30, hWnd, (HMENU)IDB_THREE, hInstance, NULL);
    CreateWindow(L"Button", L"����1000����", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        75, 220, 150, 30, hWnd, (HMENU)IDB_FOUR, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    if (!p.InithWnd())
    {
        MessageBox(hWnd, L"ֲ���ս��ʬδ��", L"��ʾ", MB_OK | MB_ICONINFORMATION);
        SendMessage(hWnd, WM_DESTROY, NULL, NULL);
    }
    MSG msg = {};

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
