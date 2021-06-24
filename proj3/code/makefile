ALL = parser
OBJS = lex.yy.o y.tab.o util.o symtable.o semcheck.o codeGen.o stringBuf.o
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

lex.yy.o: lex.yy.c y.tab.h util.h codeGen.h
y.tab.o: y.tab.c codeGen.h symtable.h util.h semcheck.h stringBuf.h

util.o: util.c util.h
symtable.o: symtable.c symtable.h util.h
codeGen.o: codeGen.c codeGen.h symtable.h util.h stringBuf.h
semcheck.o: semcheck.c semcheck.h symtable.h util.h 
stringBuf.o: stringBuf.c stringBuf.h


.PHONY: clean
clean:
	-rm $(OBJS) $(ALL)
	-rm y.tab.c y.tab.h lex.yy.c
