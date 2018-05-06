#ifndef MASTERKEYS_SOLIDBACKGROUNDADJUSTKEYBOARDEFFECT_H
#define MASTERKEYS_SOLIDBACKGROUNDADJUSTKEYBOARDEFFECT_H

#include <algorithm>
#include "KeyboardEffect.h"

class SolidBackgroundAdjustKeyboardEffect : virtual public KeyboardEffect {
private:
    bool fnPressed;
    bool f2Pressed;
    bool f3Pressed;
    int brgt;
    uint32_t color;
public:
    SolidBackgroundAdjustKeyboardEffect() :
            fnPressed(false), f2Pressed(false), f3Pressed(false), brgt(100), color(color::rgb(brgt, brgt, brgt)) {}

    void onKey(KeyData *pKeyData, KeyboardLayout *pLayout, KeyboardCanvas *pCanvas, bool pressed) override {
        if (pKeyData == pLayout->getKey("FN")) { fnPressed = pressed; }
        if (pKeyData == pLayout->getKey("F2")) { f2Pressed = pressed; }
        if (pKeyData == pLayout->getKey("F3")) { f3Pressed = pressed; }
    }

    void onTick(KeyboardLayout *pLayout, KeyboardCanvas *pCanvas) override {
        if (fnPressed && f2Pressed)
            brgt = std::max(brgt - 10, 0);
        if (fnPressed && f3Pressed)
            brgt = std::min(brgt + 10, 255);

        if (fnPressed)
            color = color::rgb(brgt, brgt, brgt);
        pCanvas->fill(color);
    }
};

#endif
