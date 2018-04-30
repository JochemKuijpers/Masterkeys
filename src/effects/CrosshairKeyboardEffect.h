#ifndef MASTERKEYS_CROSSHAIRKEYBOARDEFFECT_H
#define MASTERKEYS_CROSSHAIRKEYBOARDEFFECT_H

#include "KeyboardEffect.h"
#include "../utils/ColorUtils.h"

class CrosshairKeyboardEffect : virtual public KeyboardEffect {
    std::vector<KeyData*> pressedKeys;
    std::vector<std::pair<int, KeyData*>> releasedKeys;
    float strenght;
    int ttl;

    void drawCross(KeyboardCanvas *pCanvas, int x1, int y1, int x2, int y2, uint32_t color) {
        Rect<int> line1(0, y1, 255, y2);
        Rect<int> line2(x1 - 1, 0, x2 + 1, 255);
        pCanvas->add(line1, color);
        pCanvas->add(line2, color);
    }

public:
    CrosshairKeyboardEffect(float strenght, int ttl) : strenght(strenght), ttl(ttl) {}

    void onKey(KeyData *pKeyData, KeyboardLayout *pLayout, KeyboardCanvas *pCanvas, bool pressed) override {
        if (pressed) {
            pressedKeys.push_back(pKeyData);
        } else {
            releasedKeys.emplace_back(0, pKeyData);

            auto it = std::find(pressedKeys.begin(), pressedKeys.end(), pKeyData);
            if (it != pressedKeys.end()) {
                pressedKeys.erase(it);
            }
        }
    }

    void onTick(KeyboardLayout *pLayout, KeyboardCanvas *pCanvas) override {
        // currently pressed keys
        for (const auto &pKeyData : pressedKeys) {
            auto rect = pKeyData->getRect();
            drawCross(pCanvas, rect.x1, rect.y1, rect.x2, rect.y2,
                      color::blend(color::BLACK, color::WHITE, strenght));
        }

        // released (fade out) keys
        auto it = releasedKeys.begin();
        while (it < releasedKeys.end()) {
            auto &pair = *it;
            auto &ticks = pair.first;
            auto rect = pair.second->getRect();
            drawCross(pCanvas, rect.x1, rect.y1, rect.x2, rect.y2,
                                 color::blend(color::BLACK, color::WHITE, (1.0f - ((float)ticks / ttl)) * strenght));
            ticks += 1;

            if (ticks >= ttl) it = releasedKeys.erase(it);
            else it++;
        }
    }
};

#endif //MASTERKEYS_CROSSHAIRKEYBOARDEFFECT_H
