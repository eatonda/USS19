
CXX = g++
CXXFLAGS = -std=c++0x

OBJS = getHighScores.o scoresTest.o writeScores.o

SRCS = getHighScores.cpp scoresTest.cpp writeScores.cpp

HEADERS = getHighScores.hpp writeScores.hpp

scoresTest: ${OBJS} ${HEADERS}
	${CXX} ${OBJS} -o scoresTest

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm *.o scoresTest
