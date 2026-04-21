#!/bin/sh
rm -f jucompiler lex.yy.c y.tab.c y.tab.h y.output
yacc -d -v jucompiler.y
lex jucompiler.l
cc -o jucompiler y.tab.c lex.yy.c ast.c semantics.c