//
// Created by Piotr Rudnicki on 07/05/2026.
//

#pragma once
#include <cstdint>
#include <string>

class IDisplay {
public:
    virtual ~IDisplay() = default;
    virtual void showNotification(std::string title, std::string body, std::uint8_t severity) = 0;
    virtual void showProgress(std::string label, std::uint8_t percent) = 0;
    virtual void showStatus(std::string left, std::string right) = 0;
};
