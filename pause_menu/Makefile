
CXX = g++
C = gcc
CFLAGS = -std=c99
CXXFLAGS = -std=c++0x
SDLFLAGS = -lSDL2

CPPOBJS = pauseMenu.o runPauseMenu.o 

ALLOBJS = pauseMenu.o runPauseMenu.o clunkyCore.o clunkyAdvancedCollisions.o clunkyEventElements.o clunkyHash.o menu.o menuHelpers.o generalHelpers.o 

CPPSRCS = pauseMenu.cpp runPauseMenu.cpp 

CSRCS = ../clunky_gl/clunkyCore.c ../clunky_gl/clunkyAdvancedCollisions.c ../clunky_gl/clunkyEventElements.c ../clunky_gl/clunkyHash.c 

HEADERS = pauseMenu.hpp ../menu_functions/menu.hpp ../menu_functions/menuHelpers.hpp ../menu_functions/generalHelpers.hpp ../clunky_gl/clunkyCore.h ../clunky_gl/clunkyAdvancedCollisions.h ../clunky_gl/clunkyEventElements.h ../clunky_gl/clunkyHash.h 

pauseMenu: ${ALLOBJS} ${HEADERS}
	${CXX} ${ALLOBJS} ${SDLFLAGS} -o pauseMenu

menu.o: ../menu_functions/menu.cpp
	${CXX} ${CXXFLAGS} -c ../menu_functions/menu.cpp

menuHelpers.o: ../menu_functions/menuHelpers.cpp
	${CXX} ${CXXFLAGS} -c ../menu_functions/menuHelpers.cpp

generalHelpers.o: ../menu_functions/generalHelpers.cpp
	${CXX} ${CXXFLAGS} -c ../menu_functions/generalHelpers.cpp   

clunkyCore.o: ../clunky_gl/clunkyCore.c
	${CXX} ${CXXFLAGS} -c ../clunky_gl/clunkyCore.c

clunkyAdvancedCollisions.o: ../clunky_gl/clunkyAdvancedCollisions.c
	${CXX} ${CXXFLAGS} -c ../clunky_gl/clunkyAdvancedCollisions.c

clunkyEventElements.o: ../clunky_gl/clunkyEventElements.c
	${CXX} ${CXXFLAGS} -c ../clunky_gl/clunkyEventElements.c 

clunkyHash.o: ../clunky_gl/clunkyHash.c
	${CXX} ${CXXFLAGS} -c ../clunky_gl/clunkyHash.c 

${CPPOBJS}: ${CPPSRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm *.o pauseMenu
