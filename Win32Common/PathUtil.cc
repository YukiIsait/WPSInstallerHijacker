#include "PathUtil.h"
#include "Exception.h"
#include <Windows.h>
#include <Shlwapi.h>

namespace Win32 {
    std::wstring PathUtil::GetParent(std::wstring_view path) {
        std::wstring buffer(path);
        Exception::ThrowLastErrorIf(!::PathRemoveFileSpecW(buffer.data()), ERROR_PATH_NOT_FOUND);
        buffer.resize(buffer.find((wchar_t) 0));
        return buffer;
    }

    std::wstring PathUtil::GetFullPath(std::wstring_view path) {
        DWORD bufferSize = ::GetFullPathNameW(path.data(), 0, nullptr, nullptr);
        Exception::ThrowLastErrorIf(bufferSize == 0);
        std::wstring buffer(bufferSize, 0);
        bufferSize = ::GetFullPathNameW(path.data(), bufferSize, buffer.data(), nullptr);
        Exception::ThrowLastErrorIf(bufferSize == 0);
        buffer.resize(buffer.size() - 1);
        return buffer;
    }

    size_t PathUtil::FindExtension(std::wstring_view path) {
        wchar_t* extension = ::PathFindExtensionW(path.data());
        Exception::ThrowLastErrorIf(!*extension, ERROR_PATH_NOT_FOUND);
        return extension - path.data();
    }

    std::wstring PathUtil::Combine(std::wstring_view pathIn, std::wstring_view pathMore) {
        std::wstring buffer(MAX_PATH, 0);
        Exception::ThrowLastErrorIf(!::PathCombineW(buffer.data(), pathIn.data(), pathMore.data()));
        buffer.resize(buffer.find((wchar_t) 0));
        return buffer;
    }

    std::wstring PathUtil::GetProgramFileName() {
        std::wstring buffer(MAX_PATH, 0);
        DWORD retSize = ::GetModuleFileNameW(nullptr, buffer.data(), MAX_PATH);
        Exception::ThrowLastErrorIf(retSize == 0 || retSize == MAX_PATH);
        buffer.resize(retSize);
        return buffer;
    }

    std::wstring PathUtil::ReplaceExtension(std::wstring_view path, std::wstring_view ext) {
        std::wstring buffer(MAX_PATH, 0);
        std::wmemcpy(buffer.data(), path.data(), path.size());
        Exception::ThrowLastErrorIf(!::PathRenameExtensionW(buffer.data(), ext.data()));
        return buffer;
    }
}
