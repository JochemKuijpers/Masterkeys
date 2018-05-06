#ifndef MASTERKEYS_UTILS_H
#define MASTERKEYS_UTILS_H

template<typename T, typename U, typename V, typename W>
inline T clamp(U min, V val, W max) {
    if ((T)val < (T)min) { return (T)min; }
    if ((T)val > (T)max) { return (T)max; }
    return (T)val;
};

#endif //MASTERKEYS_UTILS_H
