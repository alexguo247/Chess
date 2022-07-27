CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = chess
OBJECTS = main.o bishop.o board.o chessgame.o human.o king.o pawn.o knight.o piece.o player.o queen.o rook.o scoreboard.o level1computer.o level2computer.o level3computer.o level4computer.o sdl_wrap.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
		${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lSDL2 -lSDL2_image -lSDL2_ttf

-include ${DEPENDS}

.PHONY: clean
clean:
		rm ${OBJECTS} ${EXEC} ${DEPENDS}
