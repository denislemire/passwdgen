CXXFLAGS = -std=c++11 -Wall -I../class

OBJS = ../class/password.o ../class/pwdgenerr.o
SRC = test_password.cpp
BIN = runTests

all: test

test: ${BIN}
	./${BIN} -r junit -o ../test-results/junit/results.xml

${BIN}: ${SRC} ${OBJS}
	${CXX} ${CXXFLAGS} ${SRC} ${OBJS} -o ${BIN}

clean:
	rm -f ${BIN} ../test-results/junit/results.xml
