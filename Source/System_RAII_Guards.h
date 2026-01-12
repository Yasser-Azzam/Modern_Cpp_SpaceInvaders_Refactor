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


class AudioDeviceGuard {
public:
    AudioDeviceGuard() {
        InitAudioDevice();
    }

    ~AudioDeviceGuard() {
        CloseAudioDevice();
    }

    AudioDeviceGuard(const AudioDeviceGuard&) = delete;
    AudioDeviceGuard& operator=(const AudioDeviceGuard&) = delete;
};