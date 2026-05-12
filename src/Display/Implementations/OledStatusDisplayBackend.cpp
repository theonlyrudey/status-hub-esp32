//
// Created by Piotr Rudnicki on 12/05/2026.
//

#include "Display/Implementations/OledStatusDisplayBackend.h"

using namespace statushub;

#include <algorithm>
#include <type_traits>

OledStatusDisplayBackend::OledStatusDisplayBackend(
    TwoWire& wire,
    const std::uint8_t sdaPin,
    const std::uint8_t sclPin,
    const std::uint8_t address)
    : _wire(wire),
      _sdaPin(sdaPin),
      _sclPin(sclPin),
      _address(address),
      _display(WIDTH, HEIGHT, &_wire, -1) {}

void OledStatusDisplayBackend::init() {
    _wire.begin(_sdaPin, _sclPin);
    _initialized = _display.begin(SSD1306_SWITCHCAPVCC, _address);
    if (!_initialized) {
        return;
    }

    _display.clearDisplay();
    _display.setTextColor(SSD1306_WHITE);
    _display.setTextWrap(false);
    present();
}

DisplayCapabilities OledStatusDisplayBackend::capabilities() const {
    return DisplayCapabilities{
        WIDTH,
        HEIGHT,
        true,
        true,
        true,
        2
    };
}

void OledStatusDisplayBackend::render(const DisplayScene& scene) {
    if (!_initialized) {
        return;
    }

    std::visit([this](const auto& view) {
        using T = std::decay_t<decltype(view)>;

        if constexpr (std::is_same_v<T, TextLine>) {
            renderTextLine(view);
        } else if constexpr (std::is_same_v<T, NotificationView>) {
            renderNotification(view);
        } else if constexpr (std::is_same_v<T, NotificationBitmapView>) {
            renderNotificationBitmap(view);
        } else if constexpr (std::is_same_v<T, NotificationBitmapDetailedView>) {
            renderNotificationBitmapDetailed(view);
        } else if constexpr (std::is_same_v<T, ProgressView>) {
            renderProgress(view);
        } else if constexpr (std::is_same_v<T, StatusView>) {
            renderStatus(view);
        } else if constexpr (std::is_same_v<T, Bitmap8x8View>) {
            renderBitmap(view);
        }
    }, scene);
}

void OledStatusDisplayBackend::clear() {
    if (!_initialized) {
        return;
    }

    _display.clearDisplay();
    present();
}

bool OledStatusDisplayBackend::isInitialized() const {
    return _initialized;
}

void OledStatusDisplayBackend::renderTextLine(const TextLine& textLine) {
    _display.clearDisplay();
    _display.setTextSize(2);
    _display.setCursor(0, 8);
    _display.print(textLine.text.c_str());
    present();
}

void OledStatusDisplayBackend::renderNotification(const NotificationView& notification) {
    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setCursor(0, 0);
    _display.print(notification.title.c_str());
    _display.setCursor(0, 16);
    _display.print(notification.body.c_str());
    present();
}

void OledStatusDisplayBackend::renderNotificationBitmap(const NotificationBitmapView& notification) {
    _display.clearDisplay();

    constexpr std::int16_t bitmapX = 2;
    constexpr std::int16_t bitmapY = 4;
    constexpr std::int16_t bitmapScale = 3;
    constexpr std::int16_t textX = 30;

    drawBitmap8x8Scaled(notification.bitmap, bitmapX, bitmapY, bitmapScale);
    _display.setTextSize(1);
    _display.setCursor(textX, 0);
    _display.print(notification.body.c_str());
    present();
}

void OledStatusDisplayBackend::renderNotificationBitmapDetailed(const NotificationBitmapDetailedView& notification) {
    _display.clearDisplay();

    constexpr std::int16_t bitmapX = 2;
    constexpr std::int16_t bitmapY = 4;
    constexpr std::int16_t bitmapScale = 3;
    constexpr std::int16_t textX = 30;

    drawBitmap8x8Scaled(notification.bitmap, bitmapX, bitmapY, bitmapScale);
    _display.setTextSize(1);
    _display.setCursor(textX, 0);
    _display.print(notification.title.c_str());
    _display.setCursor(textX, 16);
    _display.print(notification.body.c_str());
    present();
}

void OledStatusDisplayBackend::renderProgress(const ProgressView& progress) {
    const std::uint8_t clampedPercent = std::min<std::uint8_t>(progress.percent, 100);
    const std::int16_t barX = 0;
    const std::int16_t barY = 20;
    const std::int16_t barW = 127;
    const std::int16_t barH = 11;
    const std::int16_t fillW = static_cast<std::int16_t>((static_cast<std::uint32_t>(barW - 2) * clampedPercent) / 100U);

    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setCursor(0, 0);
    _display.print(progress.label.c_str());
    _display.drawRect(barX, barY, barW, barH, SSD1306_WHITE);
    _display.fillRect(barX + 1, barY + 1, fillW, barH - 2, SSD1306_WHITE);
    present();
}

void OledStatusDisplayBackend::renderStatus(const StatusView& status) {
    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setCursor(0, 0);
    _display.print(status.left.c_str());
    _display.setCursor(0, 16);
    _display.print(status.right.c_str());
    present();
}

void OledStatusDisplayBackend::renderBitmap(const Bitmap8x8View& bitmapView) {
    _display.clearDisplay();
    if (bitmapView.bitmap == nullptr) {
        present();
        return;
    }

    constexpr std::int16_t SCALE = 3;
    constexpr std::int16_t BITMAP_SIZE = 8;
    const std::int16_t xOffset = static_cast<std::int16_t>((WIDTH - (BITMAP_SIZE * SCALE)) / 2);
    const std::int16_t yOffset = static_cast<std::int16_t>((HEIGHT - (BITMAP_SIZE * SCALE)) / 2);

    drawBitmap8x8Scaled(bitmapView.bitmap, xOffset, yOffset, SCALE);

    present();
}

void OledStatusDisplayBackend::drawBitmap8x8Scaled(const std::uint8_t* bitmap,
                                                       const std::int16_t x,
                                                       const std::int16_t y,
                                                       const std::int16_t scale) {
    if (bitmap == nullptr || scale <= 0) {
        return;
    }

    constexpr std::int16_t BITMAP_SIZE = 8;
    for (std::int16_t rowIndex = 0; rowIndex < BITMAP_SIZE; ++rowIndex) {
        const std::uint8_t row = bitmap[rowIndex];
        for (std::int16_t colIndex = 0; colIndex < BITMAP_SIZE; ++colIndex) {
            const bool pixelOn = (row & static_cast<std::uint8_t>(1u << (7 - colIndex))) != 0;
            if (!pixelOn) {
                continue;
            }

            _display.fillRect(x + (colIndex * scale), y + (rowIndex * scale), scale, scale, SSD1306_WHITE);
        }
    }
}

void OledStatusDisplayBackend::present() {
    _display.display();
}
