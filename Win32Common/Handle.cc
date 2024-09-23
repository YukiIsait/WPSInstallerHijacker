#include "Handle.h"
#include <Windows.h>

namespace Win32 {
    Handle::Handle() noexcept: handle(nullptr) {}

    Handle::Handle(void* handle) noexcept: handle(handle) {}

    Handle::~Handle() noexcept {
        if (handle != nullptr) {
            ::CloseHandle(handle);
            handle = nullptr;
        }
    }

    Handle& Handle::operator=(void* newHandle) noexcept {
        if (handle != nullptr) {
            ::CloseHandle(handle);
        }
        handle = newHandle;
        return *this;
    }

    Handle::operator void*() const noexcept {
        return handle;
    }
}
