SRCS = password.cpp pwdgenerr.cpp
OBJS = ${SRCS:.cpp=.o}
INCLUDES = -I.

CXXFLAGS = -std=c++17 -fPIC ${INCLUDES}

.PHONY: all clean

all: libpassword.a

libpassword.a: ${OBJS}
	ar rcs $@ ${OBJS}

clean:
	rm -f ${OBJS} libpassword.a
