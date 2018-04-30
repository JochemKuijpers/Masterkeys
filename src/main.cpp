#include <iostream>
#include <chrono>
#include <windows.h>
#include <ShObjIdl.h>

#include "KeyboardManager.h"
#include "effects/RainDropsKeyboardEffect.h"
#include "effects/LockKeysKeyboardEffect.h"
#include "effects/SolidBackgroundKeyboardEffect.h"
#include "effects/CrosshairKeyboardEffect.h"

bool running = false;

bool setup();
bool consoleEventHandler(DWORD event);

// specify effects here:
// effects are layered in the order they are added, so the first effect draws
// the background and the last gets to draw over everyone else..
// note: the white LED keyboards only use the RED channel for color.
void configureEffects(KeyboardManager &manager) {
    // draws a specified background color every frame
    manager.addEffect(new SolidBackgroundKeyboardEffect(color::rgb(48, 48, 48)));

    // sets capslock, numlock and scroll lock lights enabled or disabled based on the lock state
    // scroll lock can be inverted by double-pressing it
    manager.addEffect(new LockKeysKeyboardEffect());

    // on key press/hold crosshair style (strength, fadeOutTime)
    manager.addEffect(new CrosshairKeyboardEffect(0.33f, 3));

    // on key-press raindrop effect (strength, speed)
    manager.addEffect(new RainDropsKeyboardEffect(0.33f, 2));
}

// code below does not need to be touched..
int main() {
    if (!setup()) {
        std::cout << "Initialization failed!\n";
        return 1;
    }

    KeyboardManager manager;
    manager.setup();

    configureEffects(manager);

    running = true;
    while (running) {
        manager.tick();
        manager.render();
        Sleep(33);
    }
    manager.stop();

    std::cout << "Stopped.\n";
    return 0;
}

bool setup() {
    // set console window title and close handler
    SetConsoleTitle("Masterkeys");
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)consoleEventHandler, true);

    // move window to lower left corner
    HWND window = GetConsoleWindow();
    RECT desktop;
    auto hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
     SetWindowPos(window, nullptr, -8, desktop.bottom - 72, 280, 32, 0);

    // hide window from taskbar
    ITaskbarList *pTaskList = nullptr;
    HRESULT initRet = CoInitialize(nullptr);
    HRESULT createRet = CoCreateInstance(
            CLSID_TaskbarList, nullptr, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (LPVOID*)&pTaskList
    );
    if(initRet != S_OK || createRet != S_OK) {
        return false;
    }
    pTaskList->DeleteTab(GetConsoleWindow());
    pTaskList->Release();
    CoUninitialize();
    return true;
}

bool consoleEventHandler(DWORD event) {
    if (event == CTRL_CLOSE_EVENT) {
        std::cout << "Shutting down shortly..\n";
        running = false;
        Sleep(100);
        return true;
    }
    return false;
}