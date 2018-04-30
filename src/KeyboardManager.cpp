#include "KeyboardManager.h"
#include "KeyboardLoader.h"
#include "utils/ColorUtils.h"
#include "effects/RainDropsKeyboardEffect.h"

KeyboardManager::KeyboardManager()
        : pLayout(nullptr), pCanvas(nullptr) {

}

KeyboardManager::~KeyboardManager() {
    delete pLayout;
    delete pCanvas;
}

bool KeyboardManager::setup() {

    if (!sdk.discoverDevice()) {
        std::cout << "Could not find a compatible device :(.\n";
        Sleep(1000);
        return false;
    }

    std::string layoutFilename = sdk.getLayoutFilename();
    KeyboardLoader loader(layoutFilename);

    pLayout = new KeyboardLayout();
    loader.load(pLayout);

    pLayout->getKeys(keys);

    if (pLayout->getWidth() == 0 || pLayout->getHeight() == 0) {
        std::cout << "Loaded keyboard layout has invalid size!\n";
        return false;
    }

    pCanvas = new KeyboardCanvas(pLayout->getWidth(), pLayout->getHeight());
    sdk.start();
    return true;
}

void KeyboardManager::sdkCallback(int row, int column, bool pressed) {
    KeyData *pKeydata = pLayout->findKey(row, column);
    if (!pKeydata) { return; }

    for (const auto &effect : effects) {
        effect->onKey(pKeydata, pLayout, pCanvas, pressed);
    }
}

void KeyboardManager::render() {
    int i = 0;
    for (const KeyData *key : keys) {
        auto rect = key->getRect();
        auto sdkId = key->getId();
        auto color = pCanvas->get(rect);
        sdk.setKeyColor(sdkId.y, sdkId.x, color::red(color), color::green(color), color::blue(color));
    }

    sdk.submitColorMatrix();
}

void KeyboardManager::tick() {
    // read SDK global event queue
    _msksdk::event_t event{};

    while (_msksdk::keyEventNext(&event)) {
        sdkCallback(event.row, event.column, event.pressed);
    }

    pCanvas->clear();
    for (const auto &effect : effects) {
        effect->onTick(pLayout, pCanvas);
    }
}

void KeyboardManager::stop() {
    sdk.stop();
}

void KeyboardManager::addEffect(KeyboardEffect *effect) {
    effects.push_back(effect);
}