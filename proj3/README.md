# adaComplier Proj3

## OverView
這是一個關於simple ada language的語法解析project，proj3的部分為產生java btye code(關於java byte code可以參考[wiki](https://en.wikipedia.org/wiki/Java_bytecode_instruction_listings) )

## Files
* semcheck.h / .c：處理語意錯誤
* symtable.h / .c：建立variable或procedure的symbol table
* util.h / .c ：關於一些資料結構與其函式
* parser.y：yacc file，進行句法檢查
* tokens.l：lex file，tokenize 輸入檔案
* codeGen.h / .c：產生java byte code
* stringBuf.h / stringBuf.c：類似c++ string的類別
* proj3.pdf：關於simple ada language的規則敘述
* 
* test director：存放一些測試用的檔案(.ada)
* 

## Execute
使用makefile產生parser
```
make
```
### 輸入檔案
```
./parse <filename>
```

### Example
```
make
./parse test_file/test.ada
```
### Output
會產生一個與ada檔案同名的.jasm 
