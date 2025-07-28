# litehtmltopng PHP Extension

This extension integrates the litehtmltopng renderer directly into PHP so no
external binary is required.

## Functions

- `litehtmltopng_version(): string` – returns extension version.
- `litehtmltopng_render(string $html_file, string $output_png): int` – renders
  an HTML file to PNG using the bundled litehtml and cairo libraries.

## Building

```sh
phpize
./configure --enable-litehtmltopng
make
sudo make install
```

After installation add `extension=litehtmltopng.so` to your `php.ini`.
