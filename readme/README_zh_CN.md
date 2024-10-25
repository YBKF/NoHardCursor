# NoHardCursor

**[English](/README.md) | 简体中文**

设定鼠标指针在 Windows 系统中的渲染方式。

当在 Windows 里加载了一个显示器的校色文件时（或者不知做了什么），
鼠标指针在这个显示器上就有可能会变异常（如指针颜色会变得灰白，尤其是那些带动画的彩色的指针最明显）。

通过将鼠标指针的渲染方式更改为软件渲染，鼠标指针有可能就会变正常，并与当前显示器的校色文件相匹配。

## 程序用法

### 双击执行

程序默认将鼠标指针的渲染方式更改为软件渲染。

### 使用命令行

    ./NoHardCursor.exe [OPTION]

#### 常见用法

不带任何参数:

    ./NoHardCursor.exe  # 默认将渲染方式改为软件渲染
                        # 等于   './NoHardCursor.exe -s'
                        # 或者   './NoHardCursor.exe --soft'

使用 '--help' 参数:

    ./NoHardCursor.exe --help   # 获取帮助

## 编译与运行

### 编译环境

- Microsoft Windows 10 or 11
- MSYS2 or MinGW-w64 (提供编译所需要的 Linux 工具链)

### 克隆 Github 仓库

    git clone https://github.com/YBKF/NoHardCursor.git && cd NoHardCursor

### Make

For MSYS2:

    make

Or MinGW-w64:

    mingw32-make

### 运行

    cd ./build && ./NoHardCursor.exe # 默认将渲染方式改为软件渲染

### 获取帮助

    ./NoHardCursor.exe --help

## 已知问题

- 因为程序是通过修改“鼠标轨迹”相关的设置来实现功能的，所以“鼠标轨迹”功能将无法使用。
- 在运行某些全屏独占的应用程序时（如，游戏），光标将会消失，使用“无边框窗口”或许能解决这个问题。

## 灵感来源

- [SoftCursor](https://www.monitortests.com/forum/Thread-SoftCursor)

## 参考

<https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-systemparametersinfoa>
