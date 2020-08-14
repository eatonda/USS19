
CXX = g++
CXXFLAGS = -std=c++0x

OBJS = getHighScores.o scoresTest.o writeScores.o enterScore.o

SRCS = getHighScores.cpp scoresTest.cpp writeScores.cpp enterScore.cpp

HEADERS = getHighScores.hpp writeScores.hpp enterScore.hpp

scoresTest: ${OBJS} ${HEADERS}
	${CXX} ${OBJS} -o scoresTest

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm *.o scoresTest
