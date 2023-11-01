# zcc -- just another C compiler

This is a C compiler that is very much under construction. Currently it can handle the following extremely simplified C grammar:

```
<program> ::= <function>
<function> ::= "int" <id> "(" ")" "{" <statement> "}"
<statement> ::= "return" <exp> ";"
<exp> ::= <int>
```

![Demo](tapes/demo1.gif)

Unlike the [on-the-fly Jack compiler front-end](https://github.com/zrottman/nand2tetris/tree/main/projects/11) I built in Python, where the lexer, parser, and code writer classes are tighly coupled, I've designed this compiler in such a way that these modules work in three distinct stages.
- The `lexer` module is responsible for reading in a `.c` file, tokenizing it and storing those tokens as a singly-linked list, and returning the head of that linked list
- The `parser` module takes the head of the linked list of tokens and, using a recursive descent algorithm, produces an abstract syntax tree, before returning the root to that tree.
- The `writer` module, finally, accepts the root of the AST and emits the corresponding assembly.
