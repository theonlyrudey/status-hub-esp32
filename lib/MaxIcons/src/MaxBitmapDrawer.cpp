//
// Created by Piotr Rudnicki on 20/04/2026.
//

#include "MaxBitmapDrawer.h"
#include <MD_MAX72xx.h>

namespace MaxIcons {
    MaxBitmapDrawer::MaxBitmapDrawer(MD_MAX72XX &display) : _display(display) {}

    void MaxBitmapDrawer::drawBitmap8x8(const std::uint8_t bitmap[8]) const
    {
        _display.clear();

        for (std::uint8_t sourceY = 0; sourceY < 8; sourceY++)
        {
            for (std::uint8_t sourceX = 0; sourceX < 8; sourceX++)
            {
                const bool on = (bitmap[sourceY] & (1 << (7 - sourceX))) != 0;

                const std::uint8_t displayX = sourceX;
                const std::uint8_t displayY = 7 - sourceY;

                _display.setPoint(displayY, displayX, on);
            }
        }

        _display.update();
    }
} // MaxIcons
