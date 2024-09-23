#pragma once

namespace Win32 {
    class Handle {
    private:
        void* handle;

    public:
        Handle() noexcept;
        Handle(void* handle) noexcept;
        virtual ~Handle() noexcept;

        Handle& operator=(void* newHandle) noexcept;
        operator void*() const noexcept;
    };
}
