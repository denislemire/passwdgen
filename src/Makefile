SRCS = main.cpp cli.cpp
OBJS = ${SRCS:.cpp=.o}
INCLUDES = -I. -I../class

CXXFLAGS = -std=c++17 -fPIC ${INCLUDES} -DPASSWDGEN_BUILD='"${PASSWDGEN_BUILD}"'
LDFLAGS = -L../class -lpassword

TARGET = passwdgen

.PHONY: all clean

all: ${TARGET}

${TARGET}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${LDFLAGS}

clean:
	rm -f ${OBJS} ${TARGET}
