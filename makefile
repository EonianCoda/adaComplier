ALL = parser
OBJS = lex.yy.o y.tab.o structure.o
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

lex.yy.o: lex.yy.c y.tab.h structure.h
y.tab.o: y.tab.c structure.h 

structure.o: structure.c structure.h

.PHONY: clean
clean:
	-rm $(OBJS) $(ALL)
	-rm y.tab.c y.tab.h lex.yy.c
