#ifndef MASTERKEYS_KEYBOARDLOADER_H
#define MASTERKEYS_KEYBOARDLOADER_H

#include <fstream>
#include <string>
#include <vector>
#include "KeyboardLayout.h"

class KeyboardLoader {
    std::string filename;
    std::ifstream file;
    unsigned int lineNumber;

    unsigned int xOffset;
    unsigned int yOffset;
    std::vector<std::string> *pFnameStack;

    void parseSize(std::vector<std::string> &tokens, KeyboardLayout *pLayout);

    void parseImport(std::vector<std::string> tokens, KeyboardLayout *pLayout);

    void parseKey(std::vector<std::string> tokens, KeyboardLayout *pLayout);

    void parseId(std::vector<std::string> &tokens, KeyboardLayout *pLayout);

    void parseAlias(std::vector<std::string> &tokens, KeyboardLayout *pLayout);

    KeyboardLoader(std::string filename, unsigned int xOffset, unsigned int yOffset,
                   std::vector<std::string> *pFnameStack);

public:

    KeyboardLoader(std::string filename);

    void load(KeyboardLayout *pLayout);
};


#endif //MASTERKEYS_KEYBOARDLOADER_H
