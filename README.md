# CTM

**CTM** (or **C Turing Machine**) is both a programming language, and the C library upon which it is based.

## The CTM Language

No better way to learn a language than checking the [examples](https://github.com/gaboflowers/ctm/tree/master/examples), the [BNF](https://github.com/gaboflowers/rktm/blob/master/ctm.bnf), and even the [lexer](https://github.com/gaboflowers/rktm/blob/master/lexer.rkt) and [parser](https://github.com/gaboflowers/rktm/blob/master/parser.rkt) itself.

Anyway, the programs are separated into 3 main blocks:
- The **Setup** block, which manages definitions and configurations, such as the machine's alphabet, or the maximum allowed length of the Tape.
- The **Declare** block, where States are declared, and the Initial state and Final states are specified.
- The **Transition** block, where the program is described. It encodes the Delta function of the Turing Machine.

For example, this machine is a variation of [allones.ctm](https://github.com/gaboflowers/ctm/blob/master/examples/allones.ctm), which accepts the language `/1*/`:
```
setup {
    alphabet {
       1, 2;
    }
    blank_symbol = -1;
}

declare {
    init state qGood;
    state qBad;
    final qGood;
}

transition {
    when (state qGood) {
        if (read 1) {
            header > 1;
        } else {
            goto qBad;
        }
    }
}
```
After compiling its file (say, "machine.ctm"), it can be run by executing `./machine -vnt [some input]`.
- `-v` stands for "verbose": it will show what was passed as input, and will tell whether the machine accepted or rejected. If not passed, you can always check if the machine accepted by doing `echo $?` and checking the return value after its execution.
- `-n` stands for "as number": as its symbols are the *integers* `1` and `2`, it will reject the input `'1'` because it is a *character* (in [ASCII](https://theasciicode.com.ar/), it has value 49). Since you probably want to pass integers as inputs, `-n` tells the initialiser to substract `'0'` to each input character, in order to convert it to a normal integer.
- `-t` tells the machine you are going to pass an input as the next argument.

Executing `./machine -vnt 1111` will show something like:

```
Input tape: '1111'
TM accepted!
```


## Features
### 1. Turing-completeness
Although formal research is still pending, it is speculated that the CTM language might be Turing-complete.

### 2. *for-loop* unrolling and *implicit indexation*
Check the declare block for [hello.ctm](https://github.com/gaboflowers/ctm/blob/master/examples/hello.ctm):
```
declare {
    init state q0;
    for (j from 0 to 7) {
        state qj;
    }
    final q7;
}
```
The for loop is just shorthand for:
```
state q0;
state q1;
state q2;
state q3;
state q4;
state q5;
state q6;
state q7;
```
As you can see, the index is not explicitly identified in `qj`: a substring will do. You can also nest them!

#### Q: "Won't it make a mess?"
**A:** We are transpiling to C. If you're not careful enough, of course it will.

There's even more fun with for-loop-syntactic-sugar in the transition block. Look at this excerpt from [anxiety.ctm](https://github.com/gaboflowers/ctm/blob/master/examples/anxiety.ctm):

```
for (i from 1 to 5) {
    when (state qi) {
        forall {
            write 'A';
            header > 1;
            goto qi+; //
        }
    }
}
```

Now it not only is replacing the index value in the `when (state qi)` part, but it also is evaluating its *increment*. Any `+` or `-` will increment or decrement the value of an index within a for loop.

Of course, there are some limitations: the indexation is only allowed on state identifiers, not on values. After all, where is the fun in programming a Turing machine, if you can use for loops everywhere? Besides that, the increment or decrement is only unitary (+1 or -1, nothing else). Nevertheless, it can still be useful for wapping up monotonous pieces of code.

### 3. Input and Output

By passing the `--stdin` flag, the machine will read is input from the standard input instead of the arguments.
As for output, when a machine halts, it will output the contents of its tape to the standard output, reading from the last position of its header, until it reaches the first blank symbol (check [justprint](https://github.com/gaboflowers/ctm/blob/master/examples/justprint.ctm), [isbalanced](https://github.com/gaboflowers/ctm/blob/master/examples/isbalanced.ctm) or *anxiety* for that).

## Further notice
### Caveats

This is work in progress. If you see the [transpiler](https://github.com/gaboflowers/rktm/blob/master/transpiler.rkt), I even still have a couple "TODO"s around the code. At the present day, the `alphabet` block still serves no purpose (it had one when I was writing the parser, then it disappeared, or I forgot about it). But I intend to make it a compile-time check to help the programmer.

### Future

- I want to make syscalls from CTM. I actually want to be able to write a web server with CTM if I *reeeeeeally* wanted to. I already have the idea of making a `syscall(2)` wrapper, but the memory mapping and pointers are going to be something.
- I want syntax highlighting. Does anyone know how to make that in Vim? I mean, it musn't be that hard, given that the token list is already in the lexer.

## Installation

Linux steps only

0. Clone this repository
```shell
git clone https://github.com/gaboflowers/ctm
```

1. Install the *libctm*
```shell
cd ctm
make
sudo make install
make clean
```

2. Clone and install the [RKTM transpiler](https://github.com/gaboflowers/rktm)
```shell
git clone https://github.com/gaboflowers/rktm
cd rktm
sudo ./install.sh
```

## Usage

Transpile any CTM program `program.ctm`  to C by running `rktm filename.ctm`, and then compile it to binary using the flag `-lctm`: `gcc -o filename filename.c -lctm`.
