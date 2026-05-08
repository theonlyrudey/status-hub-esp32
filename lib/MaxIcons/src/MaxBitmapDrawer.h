//
// Created by Piotr Rudnicki on 20/04/2026.
//

#pragma once

#include <memory>

class MD_MAX72XX;

namespace MaxIcons {
    class MaxBitmapDrawer {
    public:
        explicit MaxBitmapDrawer(MD_MAX72XX &display);
        void drawBitmap8x8(const std::uint8_t bitmap[8]) const;

    private:
        MD_MAX72XX &_display;
    };


} // MaxIcons

