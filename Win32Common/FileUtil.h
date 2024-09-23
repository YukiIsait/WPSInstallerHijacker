#pragma once
#include <string>

namespace Win32 {
    namespace FileUtil {
        void Copy(std::wstring_view existingFileName, std::wstring_view newFileName, bool failIfExists);
        bool Exists(std::wstring_view fileName);
    }
}
