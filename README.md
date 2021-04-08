# dciro-examples
Contains the implementation of the examples in [my pages](https://david-ciro.github.io/)

This repository tends to follow a common folder organization found in linux packages. The source code with the example modules and/or APIS can be found under `src/` and gets compiled with a minimal shell script `compile_src.sh`.
The compilation script simply uses `gcc` to generate object files, then copies the headers in `src/` to the `include/` directory and moves the binaries to `bin/`.
The programs to test the modules functionalities can be found under `dbg` in folders with names begining with the corresponding module name. Each test contains its individual compilation script.

