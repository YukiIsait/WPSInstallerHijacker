#pragma once
#include <string>

namespace Win32 {
    namespace ProcessUtil {
        std::wstring GetEnvironment(std::wstring_view name);
        void SetEnvironment(std::wstring_view name, std::wstring_view value);
        void LaunchProcess(std::wstring_view path, std::wstring_view args);
    }
}
