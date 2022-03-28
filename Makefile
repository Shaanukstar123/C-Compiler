CPPFLAGS += -std=c++17
CPPFLAGS += -W -Wall -g -O0
CPPFLAGS += -I include # search header files in `/include`
CPPFLAGS += -Wno-unused-parameter

#header_files := $(wildcard include/*.hpp) 
ast_cpp := $(wildcard src/ast/*.cpp)
ast_o   := $(ast_cpp:%.cpp=%.o)

all: bin/c_compiler

%.o: %.cpp
	g++ $(CPPFLAGS) -o $@ -c $<

src/parser.tab.cpp src/parser.tab.hpp: src/parser.y 
	bison -t -v -d src/parser.y -o src/parser.tab.cpp 

src/lexer.yy.cpp: src/lexer.flex src/parser.tab.hpp 
	flex -o src/lexer.yy.cpp src/lexer.flex 

bin/c_compiler : src/c_compiler.o src/lexer.yy.o src/parser.tab.o $(ast_o)
	mkdir -p bin 
	g++ $(CPPFLAGS) -o $@ $^

clean: 
	@echo Cleaning ... 
	-rm -f src/*.o 
	-rm -f bin/*.o 
	-rm -f src/ast/*.o 
	-rm -f src/*.output
	-rm -f src/*.tab.cpp 
	-rm -f src/*.tab.hpp 
	-rm -f src/*.yy.cpp	
	-rm -f bin/c_compiler 
	-rm -f bin/*.s
	-rm -f bin/*.bin
.PHONY: clean 
