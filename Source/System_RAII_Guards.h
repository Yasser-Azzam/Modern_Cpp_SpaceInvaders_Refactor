#pragma once
#include <raylib.h>


class WindowGuard {
public:
    WindowGuard(int width, int height, const char* title) {
        InitWindow(width, height, title);
    }

    ~WindowGuard() {
        CloseWindow();
    }

    WindowGuard(const WindowGuard&) = delete;
    WindowGuard& operator=(const WindowGuard&) = delete;
};