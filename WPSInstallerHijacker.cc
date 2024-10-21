#include "FileSystemWatcher.h"
#include "Common/PathUtil.h"
#include "Common/ProcessUtil.h"
#include "Common/FileUtil.h"
#include <cstdio>

int main() {
    try {
        std::wstring sourceProductPath = Win32::PathUtil::Combine(Win32::PathUtil::GetParent(Win32::PathUtil::GetProgramFileName()), L"product.dat");
        if (!Win32::FileUtil::Exists(sourceProductPath)) {
            fputs("Replacement product.dat not found.", stderr);
            return 1;
        }
        std::wstring tempPath = Win32::ProcessUtil::GetEnvironment(L"Temp");
        std::wstring wpsTempPath = Win32::PathUtil::Combine(tempPath, L"wps");
        if (!Win32::FileUtil::Exists(wpsTempPath)) {
            Win32::FileUtil::CreateDirectory(wpsTempPath);
        }
        FileSystemWatcher watcher(wpsTempPath, 0x10000);
        puts("Waiting for WPS installer to run...");
        watcher.Watch(true, FileSystemWatcher::Change::LastWrite, [&wpsTempPath, &sourceProductPath](FileSystemWatcher::Action action, const std::wstring& fileName) -> bool {
            if (action == FileSystemWatcher::Action::Modified && fileName.rfind(L"product.dat") != std::wstring::npos) {
                Win32::FileUtil::CopyFile(sourceProductPath, Win32::PathUtil::Combine(wpsTempPath, fileName), false);
                return false;
            }
            return true;
        });
        puts("Target product.dat has been replaced.");
    } catch (const std::exception& exception) {
        fputs(exception.what(), stderr);
        return 1;
    }
    return 0;
}
