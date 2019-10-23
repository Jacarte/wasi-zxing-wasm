# ZXing Barcode Reader

The source code is ported from https://github.com/nu-book/zxing-cpp.

## Build

```
mkdir build
cd build
cmake ..
cmake --build .
```

## Usage

Install [wasmer](https://github.com/wasmerio/wasmer) or [wasmtime](https://github.com/CraneStation/wasmtime).

Run `zxing_barcode_reader.wasm`:

```
wasmer run zxing_barcode_reader.wasm --dir=<image folder> <image file>

wasmtime zxing_barcode_reader.wasm --dir=<image folder> <image file>
```



