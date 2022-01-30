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

#COVFLAGS = -fprofile-arcs
#COVFLAGS += -ftest-coverage

SOURCE_DIR = src
LIB_DIR = lib
PROJECT_NAME = fighting
LIB_NAME = table

.PHONY: default
default: build

.PHONY: build
build: $(SOURCE_DIR)/* $(LIB_DIR)/*
	@echo Building
	@$(CXX) $(DEBUGFLAGS) $(CPPFLAGS) $(OPT) $(SOURCE_DIR)/*.cpp $(LIB_DIR)/*.cpp -o build.out $(LIBS)
	
.PHONY: sanitize
sanitize: $(SOURCE_DIR)/* $(LIB_DIR)/*
	@echo Building
	@$(CXX) $(ASANFLAGS) $(DEBUGFLAGS) $(CPPFLAGS) $(OPT) $(SOURCE_DIR)/*.cpp $(LIB_DIR)/*.cpp -o asan.out $(LIBS)
	@echo "ASAN passed"



#########################################################################################################
.PHONY: project
project: lib$(LIB_NAME).so
	@echo "Building project"
	@$(CXX) -L. -Wl,-rpath=. $(CPPFLAGS) $(SOURCE_DIR)/*.cpp -l$(LIB_NAME) -o $(PROJECT_NAME).out 
#%.o: %.cpp %.hpp
#	@$(CXX) -c -Wall -fpic $< -o $@
#
#%.so: %.o
#	@$(CXX) -shared $< -o $@
#

lib$(LIB_NAME).so: lib$(LIB_NAME).o
	@$(CXX) -shared $< -o $@

lib$(LIB_NAME).o: $(LIB_DIR)/*.cpp $(LIB_DIR)/*.hpp
	@$(CXX) -c -Wall -fpic $< -o $@



.PHONY: clean
clean:
	@echo Deleting .o, .so, .out
	-@rm *.out 2>/dev/null || true
	-@rm *.o 2>/dev/null || true
	-@rm *.so 2>/dev/null || true
	-@rm -rf html latex Untitled.ipynb
