#ifndef MASTERKEYS_SOLIDBACKGROUNDADJUSTKEYBOARDEFFECT_H
#define MASTERKEYS_SOLIDBACKGROUNDADJUSTKEYBOARDEFFECT_H

#include "KeyboardEffect.h"

class SolidBackgroundAdjustKeyboardEffect : virtual public KeyboardEffect {
private:
	int brgt = 100;
	uint32_t color;
public:
    void onKey(KeyData *pKeyData, KeyboardLayout *pLayout, KeyboardCanvas *pCanvas, bool pressed) override {
        //
    }

    void onTick(KeyboardLayout *pLayout, KeyboardCanvas *pCanvas) override {
		if ((GetKeyState(VK_LWIN) | GetKeyState(VK_RWIN)) & GetKeyState(VK_F3) & 0x8000)
			brgt += 10;
		if ((GetKeyState(VK_LWIN) | GetKeyState(VK_RWIN)) & GetKeyState(VK_F2) & 0x8000)
			brgt -= 10;

		if (brgt >= 255)
			brgt = 255;
		if (brgt <= 0)
			brgt = 0;
		
		color = color::rgb(brgt, brgt, brgt);
        pCanvas->fill(color);
    }
};

#endif
