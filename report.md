# Code Documentation

The aim of this project is to get some familiarity with the LLVM tool. Many research works have used to implement complex compiler features, including , but not limited to , code hardening, sensitivity analysis, verification etc.

Our aim is to use some of the LLVM functionality to mark a node as important and then remove that function from the binary, only to be called using a wrapper which is free to deal with this extracted function.

The code that we have till now in the repo contains implementation of some of the basic primitives of C language in LLVM 3.8.

The aim is to generate a valid llvm IR code, whic then is used to generate an object file using the *llvm assembler*.

## Key files

**c.y** This file contains the rule of the parser. We use *bison* to generate a parser and _flex_ to generate the lexer. Lexer and parser, both are c codes, which takes the source code as the input and parses it in to extract the TOKENS present in the files.

An example will be:

`int a =10`

will be converted to:

`KEYWORD INDENTIFIER TOKEN CONSTANT (20)`

with the _constant_ carrying the value of the constant, i.e. 20, with itself for further processing. This is then verified agains the grammar present in the _c.y_ file. If the rules allows for such a construct then the code is valid or else the compiler will throw an error.

**c.l** is the lexer file, which contains the rule for the lexical analysis.

_cc.cpp_ THis is the main file which orchestrates the whole operation. This is equivalent to _gcc_. In its current form, it takes  a source code as the input and generates the corresponding IR construct (assuming that there is no error in the sourc code).

## Key points

YY_DECL is the macro in the c.l file which contains the call to the yy_lex or the lexer. We do not call this directly. This is called by the parser when this is required.

Similarly, _yy_parse()_ is the key function used by the parser to generate. We call this in our _cc.cpp_ file followed by the call to generate the code.

cc.cpp:

```
 char const *filename = argv[1];
    yyin = fopen(filename, "r");
    assert(yyin);

    int ret_code = yyparse();
    cout << "Return Code: " << ret_code << endl;

    CodeGenContext context; // populated during parsing
    context.generateCode(*programBlock);
```

_generateCode_ in codegen.cpp file:

```
void CodeGenContext::generateCode(BlockNode &rootNode) {
    rootNode.codeGen(*this);
    module->dump();
}
```