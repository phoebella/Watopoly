CXX = g++
CXXFLAGS = -std=c++14 -MMD
EXEC = watopoly
OBJECTS = main.o Academic.o Chance.o Gameboard.o Gym.o helper.o Needles.o Nonacademic.o Nonownable.o Ownable.o Player.o Rez.o SLC.o Square.o Textdisplay.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

