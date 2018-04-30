#ifndef MASTERKEYS_RAINDROPSKEYBOARDEFFECT_H
#define MASTERKEYS_RAINDROPSKEYBOARDEFFECT_H

#include "KeyboardEffect.h"
#include "../utils/ColorUtils.h"

class RainDropsKeyboardEffect : virtual public KeyboardEffect {
private:
    const float MAX_RADIUS = 40.0f;
    float strength;
    int radiusIncPerTick;
    std::vector<Circle<int>> drops;

public:
    RainDropsKeyboardEffect(float strength, int radiusIncPerTick)
            : strength(strength), radiusIncPerTick(radiusIncPerTick) {}

    void onKey(KeyData *pKeyData, KeyboardLayout *pLayout, KeyboardCanvas *pCanvas, bool pressed) {
        if (!pressed) return;

        auto cx = (pKeyData->getRect().x1 + pKeyData->getRect().x2) / 2;
        auto cy = (pKeyData->getRect().y1 + pKeyData->getRect().y2) / 2;
        drops.emplace_back(cx, cy, 1);
    }

    void onTick(KeyboardLayout *pLayout, KeyboardCanvas *pCanvas) {
        auto it = drops.begin();
        while (it < drops.end()) {
            auto &drop = *it;

            pCanvas->add(drop, color::blend(color::BLACK, color::WHITE, (1.0f - drop.r / MAX_RADIUS) * strength));
            drop.r += radiusIncPerTick;

            if (drop.r > MAX_RADIUS) it = drops.erase(it);
            else it++;
        };
    }
};

#endif //MASTERKEYS_RAINDROPSKEYBOARDEFFECT_H
