//
// Created by Piotr Rudnicki on 12/05/2026.
//

#pragma once

#include <cstdint>

#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include "Display/Interfaces/IDisplayBackend.h"

namespace statushub {

class OledStatusDisplayBackend : public IDisplayBackend {
public:
    OledStatusDisplayBackend(TwoWire& wire, std::uint8_t sdaPin, std::uint8_t sclPin, std::uint8_t address = 0x3C);

    void init() override;
    DisplayCapabilities capabilities() const override;
    void render(const DisplayScene& scene) override;
    void clear() override;
    bool isInitialized() const;

private:
    void renderTextLine(const TextLine& textLine);
    void renderNotification(const NotificationView& notification);
    void renderNotificationBitmap(const NotificationBitmapView& notification);
    void renderNotificationBitmapDetailed(const NotificationBitmapDetailedView& notification);
    void renderProgress(const ProgressView& progress);
    void renderStatus(const StatusView& status);
    void renderBitmap(const Bitmap8x8View& bitmapView);
    void drawBitmap8x8Scaled(const std::uint8_t* bitmap, std::int16_t x, std::int16_t y, std::int16_t scale);
    void present();

private:
    static constexpr std::uint8_t WIDTH = 128;
    static constexpr std::uint8_t HEIGHT = 32;

    TwoWire& _wire;
    std::uint8_t _sdaPin;
    std::uint8_t _sclPin;
    std::uint8_t _address;
    Adafruit_SSD1306 _display;
    bool _initialized{false};
};

} // namespace statushub
