# CTM

CTM (or **C Turing Machine**) is both a programming language, and the C library upon which it is based.

## Installation

1. Install the *libctm*
```
make
sudo make install
make clean
```

2. Install the [RKTM transpiler](https://github.com/gaboflowers/rktm)
```
cd rktm
sudo ./install.sh
```

## Usage

Transpile any CTM program `program.ctm`  to C by running `rktm filename.ctm`, and then compile it to binary using the flag `-lctm`: `gcc -o filename filename.c -lctm`.
