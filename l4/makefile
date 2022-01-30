CXX = clang++
#CXX = g++
#OPT = -O3

LIBS = -lm

CPPFLAGS = -Wall
#CFLAGS += -Wfloat-equal
CPPFLAGS += -Wextra
CPPFLAGS += -pedantic
#CPPFLAGS += -Werror
#CPPFLAGS += -Wmissing-declarations
#CPPFLAGS += -fstack-protector-all

DEBUGFLAGS = -g
DEBUGFLAGS += -ggdb

ASANFLAGS = -fsanitize=address
AFLFLAGS = -Ofast

SFML_DIR=../SFML
SFML_INCL=../SFML/include

SRC_DIR=src
TOOLS=tools

SRC = $(SRC_DIR)/**/*.cpp tools/toolib.cpp

.default: game.out

game.out: game.o
	clang++ -g -ggdb -fsanitize=address *.o -o game.out -lsfml-graphics -lsfml-window -lsfml-system

game.o: $(SRC) 
	clang++ -c $(SRC) -g -ggdb -fsanitize=address


.PHONY: clean
clean:
	rm *.o  || true 
	rm *.a  || true 
	rm *.out || true
	rm src/**/*.gch

