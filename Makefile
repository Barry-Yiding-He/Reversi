CXX = g++ -Werror=vla 
CXXFLAGS = -std=c++14 
OBJECTS = info.o cell.o grid.o observer.o state.o subject.o textdisplay.o main.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = Reversi

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
