# FFI Demo

## 目标
- 通过语言交互接口FFI(Foreign Function Interface)实现Java调用Python函数
    - Demo: Java传入日期参数, 由Python返回星期几
        - 数论：`w=y+[y/4]+[c/4]-2c+[26(m+1)/10]+d-1`

- x86_64 + Mac
    ```sh
    # 配置环境
    export JAVA_HOME=${JAVA_HOME}
    export PYTHONHOME=${PYTHONHOME}
    # https://pypi.org/project/find-libpython/
    export LIBPYTHON=${LIBPYTHON}

    # 编写java代码, 声明本地方法, 生成header文件
    javac -h src/main/c/com/syntomic/ffi/include src/main/java/com/syntomic/ffi/FFIDemo.java

    # 在C中嵌入python，编译及链接生成相应库
    gcc -c -fPIC -I${JAVA_HOME}/include -I${JAVA_HOME}/include/darwin -I${PYTHONHOME}/include/python3.9 -I${PYTHONHOME}/include src/main/c/com/syntomic/ffi/com_syntomic_ffi_FFIDemo.c -o output/com_syntomic_ffi_FFIDemo.o
    gcc -dynamiclib -L${PYTHONHOME}/lib -lpython3.9 -ldl -o output/com_syntomic_ffi_FFIDemo.dylib output/com_syntomic_ffi_FFIDemo.o

    # 运行java
    javac -d output src/main/java/com/syntomic/ffi/FFIDemo.java
    java -cp ./output com.syntomic.ffi.FFIDemo
    ```

## 预备知识
- 编程语言
    - Java: 1.8
    - C/C++: c99
    - Python: 3.9

- FFI
    - JNI(Java Native Interface): [Guide to JNI](https://www.baeldung.com/jni)
    - Python/C API：
        - [Build Python A C Extension Module](https://realpython.com/build-python-c-extension-module/)
        - [Embedding Python in Another Application](https://docs.python.org/3/extending/embedding.html)

- 编译与链接
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


## TODO
- [ ] 深入研究，参考[Pemja](https://github.com/alibaba/pemja)
