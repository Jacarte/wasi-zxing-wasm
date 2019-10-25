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

![](https://www.codepool.biz/wp-content/uploads/2019/10/test-640x480.png)

![](https://www.codepool.biz/wp-content/uploads/2019/10/wapm-zxing-barcode-wasi-720x242.png)

## Blog
[How to Build ZXing C++ to Wasm using WASI SDK in Linux](https://www.codepool.biz/wasi-sdk-zxing-barcode-wasm.html)



