#ifndef MASTERKEYS_WAVEESIMULATIONKEYBOARDEFFECT_H
#define MASTERKEYS_WAVEESIMULATIONKEYBOARDEFFECT_H

#include "KeyboardEffect.h"
#include "../utils/ColorUtils.h"

class WaveSimulationKeyboardEffect : virtual public KeyboardEffect {
private:
    int width, height;
    float *prev, *curr, *next;

    std::vector<KeyData*> downKeys;

    void setup() {
        delete prev, curr, next;

        prev = new float[height * width];
        curr = new float[height * width];
        next = new float[height * width];

        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                prev[j * width + i] = .0f;
                curr[j * width + i] = .0f;
                next[j * width + i] = .0f;
            }
        }
    }

    void step() {
        float Lij;
        float alpha = 0.05f; // wave propagation constant
        float dampening = 0.99f;
        int location;
        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                // array location of the current 'pixel'
                location = j * width + i;

                Lij = 0;
                if (i > 0)          { Lij += curr[location - 1]     - curr[location]; }
                if (i < width-1)    { Lij += curr[location + 1]     - curr[location]; }
                if (j > 0)          { Lij += curr[location - width] - curr[location]; }
                if (j < height-1)   { Lij += curr[location + width] - curr[location]; }

                next[location] = (2 * curr[location] - prev[location] + alpha * Lij) * dampening;
            }
        }

        // cycle frames
        float *temp;
        temp = prev;
        prev = curr;
        curr = next;
        next = temp;
    }

public:
    WaveSimulationKeyboardEffect() : width(0), height(0), prev(nullptr), curr(nullptr), next(nullptr) {}

    ~WaveSimulationKeyboardEffect() {
        delete prev, curr, next;
    }

    void onKey(KeyData *pKeyData, KeyboardLayout *pLayout, KeyboardCanvas *pCanvas, bool pressed) override {
        if (width == 0) {
            width = pCanvas->getWidth() / 2;
            height = pCanvas->getHeight() / 2;
            setup();
        }

        if (pressed) {
            downKeys.push_back(pKeyData);
        } else {
            downKeys.erase(std::find(downKeys.begin(), downKeys.end(), pKeyData));
        }
    }

    void onTick(KeyboardLayout *pLayout, KeyboardCanvas *pCanvas) override {
        if (width == 0) {
            width = pCanvas->getWidth() / 4;
            height = pCanvas->getHeight() / 4;
            setup();
        }

        for (int t = 0; t < 4; ++t) {
            for (auto const &pKeyData : downKeys) {
                auto rect = pKeyData->getRect();
                for (int j = rect.y1 / 4; j < rect.y2 / 4; ++j) {
                    for (int i = rect.x1 / 4; i < rect.x2 / 4; ++i) {
                        curr[j * width + i] = 1.0f;
                    }
                }
            }
            step();
        }

        for (int j = 0; j < height; j += 1) {
            for (int i = 0; i < width; i += 1) {
                Rect<int> rect(i*4, j*4, i*4+4, j*4+4);
                if (next[j * width + i] > 0) {
                    pCanvas->add(rect, color::blend(color::BLACK, color::WHITE, next[j * width + i]));
                } else {
                    pCanvas->subtract(rect, color::blend(color::BLACK, color::WHITE, -next[j * width + i]));
                }
            }
        }
    }
};

#endif //MASTERKEYS_WAVEESIMULATIONKEYBOARDEFFECT_H
