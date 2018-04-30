#include "KeyboardLayout.h"

KeyboardLayout::KeyboardLayout()
    : width(0), height(0), keyData(), aliases()
{}

KeyboardLayout::~KeyboardLayout()
{}

KeyData* KeyboardLayout::getKey(std::string keyName) {
    // check for aliases
    auto aliasIter = aliases.find(keyName);
    while (aliasIter != aliases.end()) {
        keyName = aliasIter->second;
        aliasIter = aliases.find(keyName);
    }

    auto iter = keyData.find(keyName);
    if (iter == keyData.end()) {
        return nullptr;
    }
    return &(iter->second);
}

void KeyboardLayout::addAlias(std::string key, std::string alias) {
    aliases.insert(std::make_pair(alias, key));
}

void KeyboardLayout::addKey(std::string key, KeyData data) {
    keyData.insert(std::make_pair(key, data));
}

void KeyboardLayout::setSize(uint8_t w, uint8_t h) {
    width = w;
    height = h;
}

uint8_t KeyboardLayout::getWidth() const {
    return width;
}

uint8_t KeyboardLayout::getHeight() const {
    return height;
}

KeyData* KeyboardLayout::findKey(int row, int column) {
    for (auto &pair : keyData) {
        if (pair.second.getId().x == column && pair.second.getId().y == row) {
            return &(pair.second);
        }
    }
    return nullptr;
}

void KeyboardLayout::getKeys(std::vector<KeyData *> &keys) {
    keys.clear();
    for (auto &pair : keyData) {
        keys.push_back(&(pair.second));
    }
}

