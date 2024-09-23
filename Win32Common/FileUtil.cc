#include "FileUtil.h"
#include "Exception.h"
#include <Windows.h>
#include <Shlwapi.h>

namespace Win32 {
    namespace FileUtil {
        void Copy(std::wstring_view existingFileName, std::wstring_view newFileName, bool failIfExists) {
            Exception::ThrowLastErrorIf(!::CopyFileW(existingFileName.data(), newFileName.data(), failIfExists));
        }

        bool Exists(std::wstring_view fileName) {
            return ::PathFileExistsW(fileName.data());
        }
    }
}
