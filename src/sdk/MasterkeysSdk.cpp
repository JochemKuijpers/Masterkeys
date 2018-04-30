#include <iostream>
#include <memory>

#include "MasterkeysSdk.h"

std::queue<std::unique_ptr<_msksdk::event_t>> keyEventQueue;
std::mutex keyEventQueueMutex;

void CALLBACK _msksdk::keyCallBack(int iRow, int iColumn, bool iPressed) {
    std::unique_ptr<event_t> p (new event_t{iRow, iColumn, iPressed});

    // acquire a lock over the queue before pushing
    std::lock_guard<std::mutex> lock(keyEventQueueMutex);
    keyEventQueue.push(std::move(p));
}

bool _msksdk::keyEventNext(event_t *event) {
    if (keyEventQueue.empty()) {
        return false;
    }

    // acquire a lock over the queue before popping
    std::lock_guard<std::mutex> lock(keyEventQueueMutex);
    std::unique_ptr<event_t> p = std::move(keyEventQueue.front());
    keyEventQueue.pop();

    // copy queue contents to output event
    *event = *p;
    return true;
}

MasterkeysSdk::MasterkeysSdk() :
    device(DEV_DEFAULT), layout(LAYOUT_UNINIT) {
    for (auto y = 0; y < MAX_LED_ROW ; ++y) {
        for (auto x = 0; x <= MAX_LED_COLUMN; ++x) {
            colorMatrix.KeyColor[y][x] = {0, 0, 0};
        }
    }
}

bool MasterkeysSdk::discoverDevice() {
    for (const auto& pair : DEVICES) {
        const auto deviceIndex = static_cast<const DEVICE_INDEX>((pair.first & 0xFFFF0000) >> 16);
        const auto layoutId = static_cast<const LAYOUT_KEYBOARD>(pair.first & 0x0000FFFF);

        if (IsDevicePlug(deviceIndex)) {
            if (GetDeviceLayout(deviceIndex) == layoutId) {
                device = deviceIndex;
                layout = layoutId;
                return true;
            }
        }
    }
    return false;
}

std::string MasterkeysSdk::getLayoutFilename() {
    const uint32_t id = deviceId(device, layout);
    auto iter = DEVICES.find(id);
    if (iter == DEVICES.end()) {
        return nullptr;
    }
    return iter->second;
}

void MasterkeysSdk::start() {
    if (device == DEV_DEFAULT) {
        throw std::runtime_error("SDK not yet initialized");
    }
    EnableLedControl(true, device);
    SetKeyCallBack(_msksdk::keyCallBack, device);
    EnableKeyInterrupt(true, device);
    RefreshLed(true);
    std::cout << "Callback set for device " << device << "\n";
}

void MasterkeysSdk::stop() {
    if (device == DEV_DEFAULT) {
        throw std::runtime_error("SDK not yet initialized");
    }
    SetKeyCallBack(nullptr, device);
    EnableLedControl(false, device);
}

void MasterkeysSdk::setKeyColor(int row, int column, uint8_t r, uint8_t g, uint8_t b) {
    colorMatrix.KeyColor[row][column].r = r;
    colorMatrix.KeyColor[row][column].g = g;
    colorMatrix.KeyColor[row][column].b = b;
}

void MasterkeysSdk::submitColorMatrix() {
    SetAllLedColor(colorMatrix, device);
    RefreshLed(false);
}
