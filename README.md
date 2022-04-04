# SlugfyBinaryMask - Image to string functions to WebHigiia

This repository contain the main functions to convert a binary image (mask/overlay) into a compacted, base64 string that can be stored as a BLOB into a relational DBMS.
Compression algorithm is z-lib implemented by the Qt-SDK.

# Background technologies and 3rd-party libraries

Siren relies on a series of background technologies and 3rd-party libraries to work properly, namely:

1. Background technologies

- [Qt SDK][qt] - Qt Cross-Platform and SDK C++ development environment.

2. 3rd-party libraries

- [Hermes][hermes] - Our own C++ library of distance functions (and utils).
- [Artemis][artemis] - Our own wrapper library for images (and utils).
- [Dicomlib][dicomlib] - The classical self-contained Trevor Morgan dicomlib library from Google Code Archive (We were able to compile it with brand new Emscripten 😀 - Classic codes die hard).
- [Boost][boost] - A few (self-contained) Boost header files (without the need for compiling the entire library) - wasm-compliant.
- [Eigen][eigen] - A few (self-contained) Eigen header files (without the need for compiling the entire library) - wasm-compliant.


## Installation

Install the background technologies and download the source code of 3rd-party libraries.
Then, adjust the include paths of `slug.pro.example` file to point to the installation folders of the 3rd-party libraries and rename it to `slug.pro`.

```sh
#!/bin/sh
/Qt/5.15.1/gcc_64/bin/qmake   #for desktop-binary building
```


Then, run the following command.

```sh
cd SlugfyBinaryMask
make && make clean
```

## Routines

1. readAndCompressMask(std::string imageFileName) - Read and compress a binary PNG image.

2.  uncompressMask(QString zipStr) - Read a QString and uncompress it to an (Artemis) Image.


[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format it nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

   [siren]: <https://github.com/marcosivni/siren>
   [higiiaddl]: <https://github.com/marcosivni/webhigiia/blob/main/model/Higiia_DDL.sql>
   [qt]: <https://www.qt.io/download>
   [ws]: <https://github.com/marcosivni/siren_web_socket>
   [ems]: <https://emscripten.org/docs/introducing_emscripten/index.html>
   [hermes]: <https://github.com/marcosivni/hermes>
   [artemis]: <https://github.com/marcosivni/artemis>
   [dicomlib]: <https://github.com/marcosivni/dicomlib>
   [boost]: <https://www.boost.org/>
   [eigen]: <https://eigen.tuxfamily.org/>
   [model]: <https://github.com/marcosivni/wia-spine/blob/main/model/Model.md>
   
