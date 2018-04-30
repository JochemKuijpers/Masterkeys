#ifndef MASTERKEYS_STRINGUTILS_H
#define MASTERKEYS_STRINGUTILS_H

#include <string>

template<typename OutputIterator>
void tokenize(const std::string& str, const std::string& delim, OutputIterator outputIterator) {
    size_t pos = 0, prevPos = 0;
    while (true) {
        pos = str.find(delim, prevPos);

        if (pos == std::string::npos) {
            *(outputIterator++) = str.substr(prevPos);
            break;
        } else {
            *(outputIterator++) = str.substr(prevPos, pos - prevPos);
            prevPos = pos + delim.length();
        }
    }
}

#endif //MASTERKEYS_STRINGUTILS_H
