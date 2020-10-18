CCX=g++

CXXFLAGS= -g -std=c++11 #-lpthread

OBJS = */*.cpp *.cpp
all: ${OBJS}
	$(CCX) $(CXXFLAGS)   -o messenger ${OBJS} $(OPENCV)
