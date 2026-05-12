//
// Created by Piotr Rudnicki on 20/04/2026.
//

#pragma once
namespace statushub {

enum class Status {
    Invalid = -1,
    Idle,
    Working,
    Finished,
    Error
};

} // namespace statushub
