#ifndef MASTERKEYS_KEYBOARDMANAGER_H
#define MASTERKEYS_KEYBOARDMANAGER_H

#include <memory>

#include "sdk/MasterkeysSdk.h"
#include "KeyboardLayout.h"
#include "KeyboardCanvas.h"
#include "effects/KeyboardEffect.h"
#include "effects/RainDropsKeyboardEffect.h"

class KeyboardManager {
private:
    MasterkeysSdk sdk;
    KeyboardLayout *pLayout;
    KeyboardCanvas *pCanvas;
    std::vector<KeyData*> keys;
    std::vector<KeyboardEffect*> effects;

public:
    KeyboardManager();

    ~KeyboardManager();

    bool setup();

    void render();

    void tick();

    void stop();

    void sdkCallback(int row, int column, bool pressed);

    void addEffect(KeyboardEffect *effect);
};


#endif //MASTERKEYS_KEYBOARDMANAGER_H
