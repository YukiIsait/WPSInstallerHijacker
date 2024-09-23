#pragma once
#include <string>

namespace Win32 {
    namespace PathUtil {
        std::wstring GetParent(std::wstring_view path);
        std::wstring GetFullPath(std::wstring_view path);
        size_t FindExtension(std::wstring_view path);
        std::wstring Combine(std::wstring_view pathIn, std::wstring_view pathMore);
        std::wstring GetProgramFileName();
        std::wstring ReplaceExtension(std::wstring_view path, std::wstring_view ext);
    }
}
