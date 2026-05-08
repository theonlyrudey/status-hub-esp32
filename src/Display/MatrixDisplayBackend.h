//
// Created by Piotr Rudnicki on 07/05/2026.
//

#pragma once

#include <MD_MAX72xx.h>

#include "IDisplayBackend.h"
#include "MaxBitmapDrawer.h"

class MatrixDisplayBackend : public IDisplayBackend {
public:
    explicit MatrixDisplayBackend(MD_MAX72XX &display);

    void init() override;
    DisplayCapabilities capabilities() const override;
    void render(const DisplayScene &scene) override;
    void clear() override;

private:
    void renderNotification(const NotificationView &notification) const;
    void renderProgress(const ProgressView &progress) const;
    void renderStatus(const StatusView &status) const;
    void renderBitmap(const Bitmap8x8View &bitmapView) const;
    static const std::uint8_t *iconForSeverity(std::uint8_t severity);

    MaxIcons::MaxBitmapDrawer _bitmapDrawer;
    MD_MAX72XX &_display;
};

