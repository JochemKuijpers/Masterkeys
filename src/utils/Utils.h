#ifndef MASTERKEYS_UTILS_H
#define MASTERKEYS_UTILS_H

template<typename T, typename U, typename V, typename W>
inline T clamp(U min, V val, W max) {
    if (val < min) { return (T) min; }
    if (val > max) { return (T) max; }
    return (T)val;
};

#endif //MASTERKEYS_UTILS_H
