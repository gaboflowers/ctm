# CTM Examples

## Transpilation and compilation
```
make
```

## Detail

1. `allones.ctm` (Alphabet: `1`, `2`; Blank: `0`)

  Accepts on 1s sequences of arbitrary length
```
$ ./allones -vnt 11111 # accepts
$ ./allones -vnt 1111112 # rejects
$ ./allones -vnt 111110 # accepts (0 means halt)
$ ./allones -vnt 1111102 # accepts (0 means halt)
$ echo -n '1111' | ./allones -vn --stdin # accepts
$ echo -n '1111' | ./allones -v --stdin # rejects
$ echo -n '\x01\x01\x01' | ./allones -v --stdin # accepts
$ echo -n '\x31\x31\x31' | ./allones -vn --stdin # accepts
$ echo -n '\x31\x31\x31' | ./allones -v --stdin # rejects
```

2. `allcharones.ctm` (Alphabet: `'1'`,`'2'`; Blank: `'0'`)

  Accepts on '1's sequences of arbitrary length

```
$ ./allcharones -vt 11111 # accepts
$ ./allcharones -vt 1111112 # rejects
$ ./allcharones -vt 111110 # accepts ('0' means halt)
$ ./allcharones -vt 1111102 # accepts ('0' means halt)
$ echo -n '1111' | ./allcharones -vn --stdin # rejects
$ echo -n '1111' | ./allcharones -v --stdin # accepts
$ echo -n '\x01\x01\x01' | ./allcharones -v --stdin # rejects
$ echo -n '\x31\x31\x31' | ./allcharones -v --stdin # accepts
$ echo -n '\x31\x31\x31' | ./allcharones -vn --stdin # rejects
$ echo -n '\x31\x31\x31' | ./allcharones -v --stdin # accepts
```

3. `isbalanced.ctm` (Alphabet: `'('`, `')'`, `'+'`, `'$'`, `'s'`, `'n'`; Blank: `' '`)

  Accepts a balanced string of parentheses.
  Prints "s" on accept, and "n" (and a sequence of as many '+' as excess of open parentheses there are, due to how output is handled on the Tape) on reject.

```
$ ./isbalanced -t '((()(())))' # accepts and prints "s"
$ ./isbalanced -t '(((((())' # rejects and prints "n+++"
$ ./isbalanced -t '()()()()()' # accepts and prints "s"
$ ./isbalanced -t '())))' # rejects and prints "n"
```

4. `hello.ctm` (Alphabet: `'h'`, `'e'`, `'l'`, `'o'`, `' '`; Blank: `-1`)

  Accepts anything. Prepends `"hello "` to whatever inputs is passed on the tape.
```
$ ./hello -t world! # accepts and prints "hello world!"
```
  Compare to `anxiety.ctm`.

