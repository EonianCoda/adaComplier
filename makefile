ALL = parser
OBJS = lex.yy.o y.tab.o util.o symtable.o
LIBS = -lfl
CC = cc
YACC = yacc
LEX = flex

all: $(ALL)
parser: $(OBJS)
	$(CC) $^ $(LIBS) -o parser

y.tab.c y.tab.h: parser.y
	$(YACC) -d $^
lex.yy.c: tokens.l
	$(LEX) $^

lex.yy.o: lex.yy.c y.tab.h util.h
y.tab.o: y.tab.c symtable.h util.h

symtable.o: symtable.c symtable.h util.h
util.o: util.c util.h


.PHONY: clean
clean:
	-rm $(OBJS) $(ALL)
	-rm y.tab.c y.tab.h lex.yy.c
