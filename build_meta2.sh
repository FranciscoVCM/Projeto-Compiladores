#!/bin/sh

rm -f claudecompiler lex.yy.c y.tab.c y.tab.h y.output ast.h ast.c

cp meta2_ast.h ast.h
cp meta2_ast.c ast.c

yacc -d -v claudecompiler.y || exit 1
lex claude.l || exit 1
cc -o claudecompiler lex.yy.c y.tab.c ast.c -Wall