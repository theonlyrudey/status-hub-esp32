//
// Created by Piotr Rudnicki on 07/05/2026.
//

#ifndef AGENTNOTIFICATOR_IDISPLAYBACKEND_H
#define AGENTNOTIFICATOR_IDISPLAYBACKEND_H
#include <cstdint>
#include <variant>
#include <string>

struct DisplayCapabilities {
    uint16_t width;
    uint16_t height;
    bool monochrome;
    bool supportsBitmap;
    bool supportsAnimation;
    uint8_t textLevels; // e.g 1 for matrix, more for OLED
};

struct TextLine { std::string text; };
struct NotificationView { std::string title; std::string body; uint8_t severity; };
struct ProgressView { std::string label; uint8_t percent; };
struct StatusView { std::string left; std::string right; };
struct Bitmap8x8View { const std::uint8_t *bitmap; };

using DisplayScene = std::variant<TextLine, NotificationView, ProgressView, StatusView, Bitmap8x8View>;

class IDisplayBackend {
public:
    virtual ~IDisplayBackend() = default;
    virtual void init() = 0;
    virtual DisplayCapabilities capabilities() const = 0;
    virtual void render(const DisplayScene& scene) = 0;
    virtual void clear() = 0;
};
#endif //AGENTNOTIFICATOR_IDISPLAYBACKEND_H
