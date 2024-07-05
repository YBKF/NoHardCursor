# NoHardCursor

Setting the cursor rendering in Microsoft Windows.

When you changed the color profile of your monitor in Windows, the mouse cursor might be looked "weird" (Obvious on colored cursor).

By changing the mouse cursor rendering setting to software rendering, it can make your cursor match the monitor's color profile, appearing more "natural".

## Usage

### Double Click

Enable software cursor rendering by default.

### Use Command Line

    ./NoHardCursor.exe [OPTION]

#### Frequently Used Options

With no parameter:

    ./NoHardCursor.exe  # Software rendering used by default
                        # Equal to './NoHardCursor.exe -s'
                        #       or './NoHardCursor.exe --soft'

Using the '--help' Option:

    ./NoHardCursor.exe --help   # Getting help

## Build and Run

### Requirements

- Microsoft Windows 10 or 11
- MSYS2 or MinGW-w64 (Linux toolchain support)

### Clone GitHub Repository

    git clone https://github.com/YBKF/NoHardCursor.git && cd NoHardCursor

### Make

For MSYS2:

    make

Or MinGW-w64:

    mingw32-make

### Running It

    cd ./build && ./NoHardCursor.exe # Software rendering used by default

### Getting Help

    ./NoHardCursor.exe --help

## Known issues

- Mouse Trails will be disabled due to the use of relevant options.
- The cursor will not display in some applications or games in full screen mode, to solve this issue use borderless mode if possible.

## Inspiration

- [SoftCursor](https://www.monitortests.com/forum/Thread-SoftCursor)

## Reference

<https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-systemparametersinfoa>
