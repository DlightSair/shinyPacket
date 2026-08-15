# ShinyPacket

Work in Progress

A small command-line tool for basic PPM image processing in C.

## Features

- Read/write PPM images (`P3` ASCII and `P6` binary input; output is always
  written as `P3`)
- Greyscale conversion
- Convolution-based edge detection (3x3 kernel)

## Building

Requires CMake (>= 3.10) and a C compiler (GCC/Clang/MSVC).

```bash
cmake --build build
```

## Usage

```bash
cvison <input.ppm> <output.ppm> [options]
cvison <input.ppm> -o <output.ppm> [options]
```

### Options

| Flag                     | Description               |
|---------------------------|---------------------------|
| `-o <file>`                | Set output file           |
| `-g`, `--greyscale`         | Convert image to greyscale |
| `-ed`, `--edgedetection`    | Apply edge detection       |
| `-h`, `--help`              | Show help                  |


