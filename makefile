CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chess
OBJECTS = main.o textdisplay.o bishop.o board.o chessgame.o empty.o human.o king.o level1computer.o pawn.o piece.o player.o queen.o rook.o subject.o scoreboard.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
		${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean:
		rm ${OBJECTS} ${EXEC} ${DEPENDS}