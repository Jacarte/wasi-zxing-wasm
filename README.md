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

Install [wasmer](https://github.com/wasmerio/wasmer), [wasmtime](https://github.com/CraneStation/wasmtime) or [wapm](https://wapm.io/help/install).

Run `zxing_barcode_reader.wasm`:

**wasmer**
```
wasmer run zxing_barcode_reader.wasm --dir=<image folder> <image file>

```

**wasmtime**

```
wasmtime zxing_barcode_reader.wasm --dir=<image folder> <image file>
```

**wapm**

```
wapm install yushulx/zxing_barcode_reader
wapm run zxing_barcode_reader --dir=<image folder> <image file>
```



