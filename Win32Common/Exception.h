﻿#pragma once
#include <stdexcept>
#include <cstdint>

namespace Win32 {
    class Exception: public std::runtime_error {
    private:
        uint32_t errorCode;

    public:
        explicit Exception(uint32_t errorCode) noexcept;
        uint32_t GetErrorCode() const noexcept;

        static void ThrowLastError();
        static void ThrowLastError(uint32_t errorCode);
        static void ThrowLastErrorIf(bool expression);
        static void ThrowLastErrorIf(bool expression, uint32_t errorCode);
        static void ThrowLastErrorIfIs(uint32_t errorCode);
        static void ThrowLastErrorIfFailed();
    };
}
