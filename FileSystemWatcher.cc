#include "Common/Exception.h"
#include "FileSystemWatcher.h"
#include <Windows.h>

FileSystemWatcher::FileSystemWatcher(std::wstring_view fileName, size_t bufferSize): buffer(bufferSize),
                                                                                     handle(CreateFileW(fileName.data(), GENERIC_READ | GENERIC_WRITE | FILE_LIST_DIRECTORY,
                                                                                                        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                                                                                        nullptr,
                                                                                                        OPEN_EXISTING,
                                                                                                        FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
                                                                                                        nullptr)) {
    Win32::Exception::Assert(handle != INVALID_HANDLE_VALUE);
}

void FileSystemWatcher::Watch(bool watchSubtree, Change filter, std::function<bool(Action action, const std::wstring& fileName)> handler) {
    DWORD bytesReturned;
    while (true) {
        Win32::Exception::Assert(ReadDirectoryChangesW(handle, &buffer[0], (DWORD) buffer.size(), watchSubtree, (DWORD) filter, &bytesReturned, nullptr, nullptr));
        Win32::Exception::Assert(bytesReturned != 0, ERROR_INSUFFICIENT_BUFFER);
        PFILE_NOTIFY_INFORMATION info = (PFILE_NOTIFY_INFORMATION) &buffer[0];
        do {
            if (!handler((Action) info->Action, std::wstring(info->FileName, info->FileNameLength / sizeof(wchar_t)))) {
                return;
            }
            info = (PFILE_NOTIFY_INFORMATION) ((PBYTE) info + info->NextEntryOffset);
        } while (info->NextEntryOffset);
    }
}
