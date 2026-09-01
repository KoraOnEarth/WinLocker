#pragma once

#include <windows.h>

/**
 * Structure to store window handlers and other useful stuff
 */
struct WindowData
{
    HWND hwnd = nullptr;
    HWND hLockText = nullptr;
    HWND hEdit = nullptr;
    HWND hUnlockBtn = nullptr;

    const int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    const int screenHeight = GetSystemMetrics(SM_CYSCREEN);
};