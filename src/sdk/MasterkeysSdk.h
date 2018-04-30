#ifndef MASTERKEYS_MASTERKEYSSDK_H
#define MASTERKEYS_MASTERKEYSSDK_H

#include <unordered_map>
#include <string>
#include <queue>
#include <mutex>
#include "SDKDLL.h"

namespace _msksdk {
    struct event_t {
        int row;
        int column;
        bool pressed;
    };

    void CALLBACK keyCallBack(int iRow, int iColumn, bool iPressed);
    bool keyEventNext(event_t *event);
}

class MasterkeysSdk {
private:
    DEVICE_INDEX device;
    LAYOUT_KEYBOARD layout;

    COLOR_MATRIX colorMatrix;

    static inline uint32_t deviceId(DEVICE_INDEX device, LAYOUT_KEYBOARD layout) {
        return (device << 16) | layout;
    }

    const std::unordered_map<uint32_t, std::string> DEVICES = {
            std::make_pair(deviceId(DEV_MKeys_L,        LAYOUT_US), "masterkeys_pro_us_l.layout"),
            std::make_pair(deviceId(DEV_MKeys_L_White,  LAYOUT_US), "masterkeys_pro_us_l.layout"),
            std::make_pair(deviceId(DEV_MKeys_M,        LAYOUT_US), "masterkeys_pro_us_m.layout"),
            std::make_pair(deviceId(DEV_MKeys_M_White,  LAYOUT_US), "masterkeys_pro_us_m.layout"),
            std::make_pair(deviceId(DEV_MKeys_S,        LAYOUT_US), "masterkeys_pro_us_s.layout"),
            std::make_pair(deviceId(DEV_MKeys_S_White,  LAYOUT_US), "masterkeys_pro_us_s.layout")
    };

public:
    MasterkeysSdk();
    bool discoverDevice();
    std::string getLayoutFilename();
    void start();
    void stop();
    void setKeyColor(int row, int column, uint8_t r, uint8_t g, uint8_t b);
    void submitColorMatrix();
};


#endif //MASTERKEYS_MASTERKEYSSDK_H
