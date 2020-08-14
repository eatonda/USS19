# files to compile
OBJS =  inputName.cpp ../clunky_gl/clunkyCore.c ../clunky_gl/clunkyEventElements.c ../clunky_gl/clunkyHash.c 

# compiler
CC = g++

# flags
COMPILER_FLAGS = -w

# linker flags
LINKER_FLAGS = -lSDL2

# name of executable
OBJ_NAME = name_ex

# compiles
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
