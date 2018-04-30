#ifndef MASTERKEYS_KEYBOARD_H
#define MASTERKEYS_KEYBOARD_H

#include <cstdint>
#include <unordered_map>
#include <iostream>
#include <SDKDLL.h>
#include <vector>
#include <functional>
#include <chrono>

#include "KeyData.h"
#include "KeyboardCanvas.h"

class KeyboardLayout {
private:
    uint8_t width, height;
    std::unordered_map<std::string, KeyData> keyData;
    std::unordered_map<std::string, std::string> aliases;
public:

    KeyboardLayout();

    ~KeyboardLayout();

    KeyData *getKey(std::string keyName);

    void addAlias(std::string key, std::string alias);

    void addKey(std::string key, KeyData data);

    void setSize(uint8_t w, uint8_t h);

    uint8_t getWidth() const;

    uint8_t getHeight() const;

    KeyData *findKey(int row, int column);

    void getKeys(std::vector<KeyData*> &keys);
};


#endif //MASTERKEYS_KEYBOARD_H
