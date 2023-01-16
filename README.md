# IFT606

## Prerequisits

- C++ compiler that supports `C++20` ex: `gcc` or `clang`
- CMake (>= 3.2.0)
- VsCode
    - [Extension CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)

## Building

Run the `CMake: Build` action using `Ctrl+Shift+P` shortcut.

or 

Use the build shortcut: `Ctrl+Shift+B`

## Debug

Simply press `F5` to start debugging.

## Usage

The input format is `base64` defined as such:

```c++
0 -> 25 = 'A' -> 'Z'
26 -> 51 = 'a' -> 'z'
52 -> 62 = '0' -> '9'
63 = '+'
64 = '/'
```

In the command line as so:
```
> ./TP1 <Key as base64 string> <Message as base64 string> <N offset>
```