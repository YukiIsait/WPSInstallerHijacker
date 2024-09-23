#include "ProcessUtil.h"
#include "Exception.h"
#include <Windows.h>

namespace Win32 {
    namespace ProcessUtil {
        std::wstring GetEnvironment(std::wstring_view name) {
            DWORD bufferSize = ::GetEnvironmentVariableW(name.data(), nullptr, 0);
            Exception::ThrowLastErrorIf(bufferSize == 0);
            std::wstring buffer(bufferSize, 0);
            bufferSize = ::GetEnvironmentVariableW(name.data(), buffer.data(), buffer.size());
            Exception::ThrowLastErrorIf(bufferSize == 0);
            buffer.resize(buffer.size() - 1);
            return buffer;
        }

        void SetEnvironment(std::wstring_view name, std::wstring_view value) {
            Exception::ThrowLastErrorIf(!::SetEnvironmentVariableW(name.data(), value.data()));
        }

        void LaunchProcess(std::wstring_view path, std::wstring_view args) {
            STARTUPINFO si = { 0 };
            PROCESS_INFORMATION pi = { 0 };
            si.cb = sizeof(si);
            std::wstring command(path.size() + args.size() + 1, 0);
            std::wstring::iterator commandIterator = std::copy(path.begin(), path.end(), command.begin());
            *commandIterator++ = L' ';
            std::copy(args.begin(), args.end(), commandIterator);
            if (::CreateProcessW(path.data(), const_cast<wchar_t*>(command.data()),
                                 nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
                ::CloseHandle(pi.hProcess);
                ::CloseHandle(pi.hThread);
            } else {
                Exception::ThrowLastError();
            }
        }
    }
}
