
#ifndef MASTERKEYS_LOCKKEYSKEYBOARDEFFECT_H
#define MASTERKEYS_LOCKKEYSKEYBOARDEFFECT_H

#include <chrono>
#include <windows.h>

#include "KeyboardEffect.h"
#include "../utils/ColorUtils.h"

class LockKeysKeyboardEffect : virtual public KeyboardEffect {
private:
    bool invertScroll = false;
    std::chrono::steady_clock::time_point scrollPress = std::chrono::steady_clock::now();
public:
    void onKey(KeyData *pKeyData, KeyboardLayout *pLayout, KeyboardCanvas *pCanvas, bool pressed) override {
        if (!pressed) return;

        // check if scroll lock was pressed twice within 0.25 second
        // if so, invert the display
        if (pLayout->getKey("SCROLLLOCK") == pKeyData) {
            if (std::chrono::duration_cast<std::chrono::milliseconds>
                    (std::chrono::steady_clock::now() - scrollPress).count() < 250) {
                invertScroll = !invertScroll;
            }
            scrollPress = std::chrono::steady_clock::now();
        }
    }

    void onTick(KeyboardLayout *pLayout, KeyboardCanvas *pCanvas) override {
        if (GetKeyState(VK_CAPITAL) & 0x0001)
            pCanvas->set(pLayout->getKey("CAPSLOCK")->getRect(), color::WHITE);
        else
            pCanvas->set(pLayout->getKey("CAPSLOCK")->getRect(), color::BLACK);

        if ((GetKeyState(VK_SCROLL) & 0x0001) ^ invertScroll)
            pCanvas->set(pLayout->getKey("SCROLLLOCK")->getRect(), color::WHITE);
        else
            pCanvas->set(pLayout->getKey("SCROLLLOCK")->getRect(), color::BLACK);

        if (GetKeyState(VK_NUMLOCK) & 0x0001)
            pCanvas->set(pLayout->getKey("NUMLOCK")->getRect(), color::WHITE);
        else
            pCanvas->set(pLayout->getKey("NUMLOCK")->getRect(), color::BLACK);
    }
};

#endif //MASTERKEYS_LOCKKEYSKEYBOARDEFFECT_H
