#include <stdexcept>
#include <fstream>
#include <utility>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "KeyboardLoader.h"
#include "utils/StringUtils.h"
#include "KeyData.h"
#include "utils/Utils.h"

KeyboardLoader::KeyboardLoader(std::string filename)
        : KeyboardLoader(filename, 0, 0, nullptr) {
    pFnameStack = new std::vector<std::string>();
}

KeyboardLoader::KeyboardLoader(std::string filename, unsigned int xOffset, unsigned int yOffset,
                               std::vector<std::string> *pFnameStack)
        : filename(std::move(filename)), file(), lineNumber(0), xOffset(xOffset), yOffset(yOffset), pFnameStack(pFnameStack) {
}


void KeyboardLoader::load(KeyboardLayout *pLayout) {
    std::cout << "Loading layout from " << filename << " ...\n";
    file.open("data/" + filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }

    std::string line;
    std::vector<std::string> tokens;

    while (std::getline(file, line)) {
        lineNumber++;

        if (!line.empty() && line[line.size() - 1] == '\r') {
            line.erase(line.size() - 1);
        }

        if (line.empty()) { continue; }

        tokens.clear();
        tokenize(line, " ", std::back_inserter(tokens));

        if (tokens.empty()) { continue; }
        if (tokens[0] == "//" || (tokens[0].empty() && tokens.size() == 1)) { continue; }

        if (tokens[0] == "//")      { continue; }
        if (tokens[0] == "size")    { parseSize(tokens, pLayout);     continue; }
        if (tokens[0] == "import")  { parseImport(tokens, pLayout);   continue; }
        if (tokens[0] == "key")     { parseKey(tokens, pLayout);      continue; }
        if (tokens[0] == "id")      { parseId(tokens, pLayout);       continue; }
        if (tokens[0] == "alias")   { parseAlias(tokens, pLayout);    continue; }

        std::stringstream ss;
        ss << "Error interpreting line " << lineNumber << " of '" << filename << "':\n"
           << "Unknown command '" << tokens[0] << "' with " << tokens.size() << " parameters.\n";
        throw std::runtime_error(ss.str());
    }
}

void KeyboardLoader::parseSize(std::vector<std::string>& tokens, KeyboardLayout *pLayout) {
    if (tokens.size() != 3) {
        std::stringstream ss;
        ss << "Error on line " << lineNumber << " of '" << filename << "':\n"
           << "Invalid number of parameters for command.\n";
        throw std::runtime_error(ss.str());
    }

    pLayout->setSize(
            clamp<uint8_t>(0, std::stoi(tokens[1]), 255),
            clamp<uint8_t>(0, std::stoi(tokens[2]), 255)
    );
}

void KeyboardLoader::parseKey(std::vector<std::string> tokens, KeyboardLayout *pLayout) {
    if (tokens.size() != 6) {
        std::stringstream ss;
        ss << "Error on line " << lineNumber << " of '" << filename << "':\n"
           << "Invalid number of parameters for command.\n";
        throw std::runtime_error(ss.str());
    }

    KeyData keyData;

    uint8_t x1, y1, x2, y2;
    x1 = clamp<uint8_t>(0, std::stoi(tokens[2]) + xOffset, 255);
    x2 = x1 + clamp<uint8_t>(0, std::stoi(tokens[4]), 255);
    y1 = clamp<uint8_t>(0, std::stoi(tokens[3]) + yOffset, 255);
    y2 = y1 + clamp<uint8_t>(0, std::stoi(tokens[5]), 255);
    keyData.setRect({x1, y1, x2, y2});

    pLayout->addKey(tokens[1], keyData);
}

void KeyboardLoader::parseImport(std::vector<std::string> tokens, KeyboardLayout *pLayout) {
    if (tokens.size() != 2 && tokens.size() != 4) {
        std::stringstream ss;
        ss << "Error on line " << lineNumber << " of '" << filename << "':\n"
           << "Invalid number of parameters for command.\n";
        throw std::runtime_error(ss.str());
    }
    unsigned int newXOffset = xOffset, newYOffset = yOffset;
    if (std::find(pFnameStack->begin(), pFnameStack->end(), tokens[1]) != pFnameStack->end()) return;

    pFnameStack->push_back(tokens[1]);

    if (tokens.size() == 4) {
        newXOffset = clamp<unsigned int>(0, xOffset + std::stoi(tokens[2]), 255);
        newYOffset = clamp<unsigned int>(0, yOffset + std::stoi(tokens[3]), 255);
    }

    KeyboardLoader loader(tokens[1], newXOffset, newYOffset, pFnameStack);
    loader.load(pLayout);

    pFnameStack->pop_back();
}

void KeyboardLoader::parseId(std::vector<std::string> &tokens, KeyboardLayout *pLayout) {
    if (tokens.size() != 4) {
        std::stringstream ss;
        ss << "Error on line " << lineNumber << " of '" << filename << "':\n"
           << "Invalid number of parameters for command.\n";
        throw std::runtime_error(ss.str());
    }
    auto keyData = pLayout->getKey(tokens[1]);
    if (keyData == nullptr) {
        std::stringstream ss;
        ss << "Error on line " << lineNumber << " of '" << filename << "':\n"
           << "Unknown key name.\n";
        throw std::runtime_error(ss.str());
    }

    keyData->setId({
        clamp<uint8_t>(0, std::stoi(tokens[2]), 255),
        clamp<uint8_t>(0, std::stoi(tokens[3]), 255)
    });
}

void KeyboardLoader::parseAlias(std::vector<std::string>& tokens, KeyboardLayout* pLayout) {
    if (tokens.size() < 3) {
        std::stringstream ss;
        ss << "Error on line " << lineNumber << " of '" << filename << "':\n"
           << "Invalid number of parameters for command.\n";
        throw std::runtime_error(ss.str());
    }
    if (pLayout->getKey(tokens[1]) == nullptr) {
        std::stringstream ss;
        ss << "Error on line " << lineNumber << " of '" << filename << "':\n"
           << "Can't set alias for unknown key name.\n";
        throw std::runtime_error(ss.str());
    }

    // create a mapping from every alias to the key
    for (int i = 2; i < tokens.size(); ++i) {
        if (pLayout->getKey(tokens[i]) != nullptr) {
            std::stringstream ss;
            ss << "Error on line " << lineNumber << " of '" << filename << "':\n"
               << "'" << tokens[i] << "' already known.\n";
            throw std::runtime_error(ss.str());
        }

        pLayout->addAlias(tokens[1], tokens[i]);
    }
}
