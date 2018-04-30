#ifndef MASTERKEYS_KEYBOARDEFFECT_H
#define MASTERKEYS_KEYBOARDEFFECT_H

#include <string>
#include <unordered_set>

#include "../KeyData.h"
#include "../KeyboardCanvas.h"
#include "../KeyboardLayout.h"

class KeyboardEffect {
public:
    virtual void onKey(KeyData *pKeyData, KeyboardLayout *pLayout, KeyboardCanvas *pCanvas, bool pressed) = 0;
    virtual void onTick(KeyboardLayout *pLayout, KeyboardCanvas *pCanvas) = 0;
};


#endif //MASTERKEYS_KEYBOARDEFFECT_H
