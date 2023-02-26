# FFI Demo

通过语言交互接口FFI(Foreign Function Interface)实现[Java调用Python函数Demo](https://syntomic.github.io/2023/02/25/Java%E8%B0%83%E7%94%A8Python/)

## Quick Start：x86_64 + MacOS
```sh
export JAVA_HOME=${JAVA_HOME}
export PYTHONHOME=${PYTHONHOME}
export LIBPYTHON=${LIBPYTHON}

javac -h src/main/c/cn/syntomic/ffi/include src/main/java/cn/syntomic/ffi/FFIDemo.java

gcc -c -fPIC -I${JAVA_HOME}/include -I${JAVA_HOME}/include/darwin -I${PYTHONHOME}/include/python3.9 -I${PYTHONHOME}/include src/main/c/cn/syntomic/ffi/cn_syntomic_ffi_FFIDemo.c -o FFIDemo.o
gcc -dynamiclib -L${PYTHONHOME}/lib -lpython3.9 -ldl -o FFIDemo.dylib FFIDemo.o

javac -d target/classes/cn/syntomic/ffi src/main/java/cn/syntomic/ffi/FFIDemo.java
java -cp target/classes cn.syntomic.ffi.FFIDemo
```

## Cheat Sheet

- g++ 命令参数
    - `-c`: Only run preprocess, compile, and assemble steps
    - `-fPIC`: If supported for the target machine, emit position-independent code, suitable for dynamic linking and avoiding any limit on the size of the global offset table
    - `-I`: Add directory to the end of the list of include search paths
    - `-i <directory>`: Add directory to SYSTEM include search path
    - `-o`: Write output to file
    - `-dynamiclib`: When passed this option, GCC will produce a dynamic library instead of an executable when linking, using the Darwin libtool command
    - `-L`: Add directory to library search path
    - `-l`: Search the library named library when linking;The linker searches a standard list of directories for the library, which is actually a file named liblibrary.a. The linker then uses this file as if it had been specified precisely by name.
    - `-D`: Predefine name as a macro, with definition 1.
    - `-O2`: Optimize even more. GCC performs nearly all supported optimizations that do not involve a space-speed tradeoff.
    - `-fwrapv`: Treat signed integer overflow as two's complement
