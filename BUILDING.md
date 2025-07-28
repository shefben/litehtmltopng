# Building the litehtmltopng PHP Extension

This repository includes a PHP extension that renders HTML to PNG using the
[litehtml](https://github.com/tordex/litehtml) engine with the
[Cairo](https://cairographics.org/) graphics library and
[FreeType](https://freetype.org/) for fonts.

The `libs` directory contains the source code (and in the case of Windows,
prebuilt binaries) for these dependencies:

- `litehtmlcpp98` – lightweight HTML renderer
- `cairo` – 2D graphics library
- `freetype` – font rasterization library

If packages for Cairo and FreeType are not available on your platform you can
compile them from these sources.

## Building Dependencies

### Cairo
- **Linux**: install `libcairo2-dev` with your package manager or run `./configure && make && sudo make install` inside `libs/cairo`.
- **Windows**: prebuilt `cairo.dll`/`cairo.lib` are provided under `libs/cairo/64`. To compile manually open `libs/cairo/src/Makefile.win32` with Visual Studio and build the `Release` target.

### FreeType
- **Linux**: install `libfreetype6-dev` or build from `libs/freetype` using `cmake`.
- **Windows**: DLL and LIB files are available in `libs/freetype/release dll/win64`. To rebuild use the Visual Studio project files in that directory.

### litehtmlcpp98
The litehtml sources are built automatically when compiling the PHP extension, no separate installation step is needed.

## Building on Linux
1. Ensure PHP 8.4 development headers and a compiler are installed.
2. Install or build Cairo and FreeType as described above.
3. Compile and install the extension:
```sh
cd php_extension
phpize
./configure --enable-litehtmltopng
make
sudo make install
```
4. Add `extension=litehtmltopng.so` to `php.ini`.

## Building on Windows
1. Use the PHP SDK or a Visual Studio developer command prompt.
2. Make sure the DLLs from `libs/cairo/64` and `libs/freetype/release dll/win64` are available in your PATH during build and runtime.
3. Build the extension:
```cmd
cd php_extension
phpize
configure --enable-litehtmltopng
nmake
nmake install
```
4. Copy `cairo.dll`, `freetype.dll` and the generated `litehtmltopng.dll` next to `php.exe` or a directory listed in `PATH`.
5. Enable the extension with `extension=litehtmltopng.dll` in `php.ini`.
