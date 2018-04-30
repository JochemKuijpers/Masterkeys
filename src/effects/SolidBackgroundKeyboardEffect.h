#ifndef MASTERKEYS_SOLIDBACKGROUNDKEYBOARDEFFECT_H
#define MASTERKEYS_SOLIDBACKGROUNDKEYBOARDEFFECT_H

#include "KeyboardEffect.h"

class SolidBackgroundKeyboardEffect : virtual public KeyboardEffect {
private:
    uint32_t color;
public:

    SolidBackgroundKeyboardEffect(uint32_t color) : color(color) {}

    void onKey(KeyData *pKeyData, KeyboardLayout *pLayout, KeyboardCanvas *pCanvas, bool pressed) override {
        //
    }

    void onTick(KeyboardLayout *pLayout, KeyboardCanvas *pCanvas) override {
        pCanvas->fill(color);
    }
};

#endif //MASTERKEYS_SOLIDBACKGROUNDKEYBOARDEFFECT_H
