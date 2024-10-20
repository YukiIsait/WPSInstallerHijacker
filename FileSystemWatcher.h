#pragma once
#include "Common/Handle.hh"
#include <functional>
#include <string>
#include <vector>

class FileSystemWatcher {
public:
    enum class Change {
        FileName = 0x00000001,   // 监视文件名更改
        DirName = 0x00000002,    // 监视目录名更改
        Attributes = 0x00000004, // 监视文件属性更改
        Size = 0x00000008,       // 监视文件大小更改
        LastWrite = 0x00000010,  // 监视文件最后写入时间更改
        LastAccess = 0x00000020, // 监视文件最后访问时间更改
        Creation = 0x00000040,   // 监视文件创建
        Security = 0x00000100,   // 监视文件安全描述符更改
        All = 0x0000017F         // 监视所有情况
    };

    enum class Action {
        Add = 0x00000001,       // 文件添加
        Remove = 0x00000002,    // 文件删除
        Modified = 0x00000003,  // 文件更改
        RenameOld = 0x00000004, // 文件重命名（旧名字）
        RenameNew = 0x00000005  // 文件重命名（新名字）
    };

private:
    Win32::Handle<> handle;
    std::vector<uint8_t> buffer;

public:
    FileSystemWatcher(std::wstring_view fileName, size_t bufferSize = 4096);
    void Watch(bool watchSubtree, Change filter, std::function<bool(Action action, const std::wstring& fileName)> handler);
};
