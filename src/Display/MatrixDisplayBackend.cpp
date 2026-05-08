//
// Created by Piotr Rudnicki on 07/05/2026.
//

#include "MatrixDisplayBackend.h"

#include <type_traits>

#include "Icons.h"

MatrixDisplayBackend::MatrixDisplayBackend(MD_MAX72XX &display)
    : _bitmapDrawer(display), _display(display) {}

void MatrixDisplayBackend::init() {
    _display.begin();
    _display.control(MD_MAX72XX::INTENSITY, 3);
    _display.clear();
}

DisplayCapabilities MatrixDisplayBackend::capabilities() const {
    return DisplayCapabilities{
        8,
        8,
        true,
        true,
        true,
        1
    };
}

void MatrixDisplayBackend::render(const DisplayScene &scene) {
    std::visit([this](const auto &view) {
        using T = std::decay_t<decltype(view)>;

        if constexpr (std::is_same_v<T, NotificationView>) {
            renderNotification(view);
        } else if constexpr (std::is_same_v<T, ProgressView>) {
            renderProgress(view);
        } else if constexpr (std::is_same_v<T, StatusView>) {
            renderStatus(view);
        } else if constexpr (std::is_same_v<T, Bitmap8x8View>) {
            renderBitmap(view);
        } else {
            renderNotification(NotificationView{"text", view.text, 1});
        }
    }, scene);
}

void MatrixDisplayBackend::clear() {
    _display.clear();
    _display.update();
}

void MatrixDisplayBackend::renderNotification(const NotificationView &notification) const {
    _bitmapDrawer.drawBitmap8x8(iconForSeverity(notification.severity));
}

void MatrixDisplayBackend::renderProgress(const ProgressView &progress) const {
    const std::uint8_t clampedPercent = progress.percent > 100 ? 100 : progress.percent;
    const std::uint8_t columnsToLight = static_cast<std::uint8_t>((clampedPercent * 8U + 99U) / 100U);

    _display.clear();
    for (std::uint8_t column = 0; column < 8; ++column) {
        _display.setColumn(column, column < columnsToLight ? 0xFF : 0x00);
    }
    _display.update();
}

void MatrixDisplayBackend::renderStatus(const StatusView &status) const {
    if (status.left == "idle") {
        _bitmapDrawer.drawBitmap8x8(Icons::Idle);
    } else if (status.left == "working") {
        _bitmapDrawer.drawBitmap8x8(Icons::Working_0);
    } else if (status.left == "finished") {
        _bitmapDrawer.drawBitmap8x8(Icons::Finished);
    } else if (status.left == "error") {
        _bitmapDrawer.drawBitmap8x8(Icons::Error);
    } else {
        _bitmapDrawer.drawBitmap8x8(Icons::Working_0);
    }
}

void MatrixDisplayBackend::renderBitmap(const Bitmap8x8View &bitmapView) const {
    if (bitmapView.bitmap == nullptr) {
        _display.clear();
        _display.update();
        return;
    }

    _bitmapDrawer.drawBitmap8x8(bitmapView.bitmap);
}

const std::uint8_t *MatrixDisplayBackend::iconForSeverity(const std::uint8_t severity) {
    switch (severity) {
        case 0:
            return Icons::Idle;
        case 1:
            return Icons::Working_0;
        case 2:
            return Icons::Finished;
        default:
            return Icons::Error;
    }
}
