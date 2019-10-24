# ZXing Barcode Reader

The source code is ported from https://github.com/nu-book/zxing-cpp.

## How to Build
Install [wasi-sdk_7.0_amd64.deb
](https://github.com/CraneStation/wasi-sdk/releases).

Set environment variables in terminal:

```
export PATH=/opt/wasi-sdk/bin:$PATH
export CC=/opt/wasi-sdk/bin/clang
export CXX=/opt/wasi-sdk/bin/clang++
```

Build the project:

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
wasmer run zxing_barcode_reader.wasm --dir=<image folder> <PNG file>

```

**wasmtime**

```
wasmtime zxing_barcode_reader.wasm --dir=<image folder> <PNG file>
```

**wapm**

```
wapm install yushulx/zxing_barcode_reader
wapm run zxing_barcode_reader --dir=<image folder> <PNG file>
```

## Blog
[How to Build ZXing C++ to Wasm using WASI SDK in Linux](https://medium.com/@yushulx/how-to-build-zxing-c-to-wasm-using-wasi-sdk-in-linux-c1c618ac83f4)



