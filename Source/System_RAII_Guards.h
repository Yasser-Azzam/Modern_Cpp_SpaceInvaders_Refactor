#pragma once
#include <raylib.h>


class WindowGuard {
public:
    WindowGuard(int width, int height, const char* title) noexcept
    {
        InitWindow(width, height, title);
    }

    ~WindowGuard() noexcept
    {
        CloseWindow();
    }

    WindowGuard(const WindowGuard&) = delete;
    WindowGuard& operator=(const WindowGuard&) = delete;

    WindowGuard(WindowGuard&&) = delete;
    WindowGuard& operator=(WindowGuard&&) = delete;
};