#CXX = clang++
CXX = g++
#OPT = -O3

LIBS = -lm

#CXXFLAGS = -Wall
#CFLAGS += -Wfloat-equal
#CXXFLAGS += -Wextra
#CXXFLAGS += -pedantic
#CXXFLAGS += -Werror
#CXXFLAGS += -Wmissing-declarations
#CXXFLAGS += -fstack-protector-all

DEBUGFLAGS = -g
DEBUGFLAGS += -ggdb

ASANFLAGS = -fsanitize=address
#ASANFLAGS += -fno-common
#ASANFLAGS += -fno-omit-frame-pointer
AFLFLAGS = -Ofast

GTEST_DIR=../../googletest/googletest
GTEST_INCLUDE=../../googletest/googletest/include
GTEST_HEADERS=$(GTEST_DIR)/include/gtest/*.h \
			  $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_=$(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

SRC_DIR=tesrc
TEST_DIR=./tests

GTEST_INCLUDE2=../googletest/googletest/include/gtest

# GTest facility
# Taken from https://gist.github.com/mihaitodor/bfb8e7ad908489fdf3ceb496573f306a
#
#.PHONY: tests/gtest-all.o tests/gtest_main.o tests/gtest_main.a tests/test.o

.PHONY: test
test: test.out
	@./test.out
	@echo "============================================================================"

#tests/test.o: test.o
#test.o: $(TEST_DIR)/test.cpp $(GTEST_HEADERS)
#	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -c $(TEST_DIR)/test.cpp $(ASANFLAGS) -o tests/test.o
test.out: tests/test.o tests/gtest_main.a
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $(DEBUGFLAGS) -lpthread $^  tesrc/**/*.cpp  tools/toolib.cpp -o $@

tests/gtest-all.o: gtest-all.o
gtest-all.o: $(GTEST_SRCS_)
	$(CXX) -I $(GTEST_DIR) -I $(GTEST_INCLUDE) $(DEBUGFLAGS) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc -o tests/$@

tests/gtest_main.o: gtest_main.o
gtest_main.o: $(GTEST_SRCS_)
	$(CXX) -I $(GTEST_DIR) $(CXXFLAGS) $(DEBUGFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc -o tests/$@

tests/gtest.a: gtest.a
gtest.a: tests/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

tests/gtest_main.a: gtest_main.a
gtest_main.a: tests/gtest-all.o tests/gtest_main.o
	$(AR) $(ARFLAGS) tests/$@ $^
	@echo "gtest_main.a compiled successfully"

tests/test.o: test.o
test.o: $(TEST_DIR)/test.cpp $(GTEST_HEADERS)
	$(CXX) $(CXXFLAGS) -I $(GTEST_INCLUDE2) $(DEBUGFLAGS) -c $(TEST_DIR)/test.cpp $(ASANFLAGS) -o tests/test.o


.PHONY: coverage
coverage: tesrc/lib.cpp tests/test.cpp
	$(CXX) -fprofile-arcs -ftest-coverage tesrc/lib.cpp tests/test.cpp

.PHONY: clean
clean:
	rm tests/*.o
	rm tests/*.a
	rm *.out
