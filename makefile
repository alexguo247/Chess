CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chess
OBJECTS = main.o bishop.o board.o chessgame.o human.o king.o pawn.o knight.o piece.o player.o queen.o rook.o scoreboard.o level1computer.o level2computer.o level3computer.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
		${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean:
		rm ${OBJECTS} ${EXEC} ${DEPENDS}