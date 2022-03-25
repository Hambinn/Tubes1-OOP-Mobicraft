EXT_OUT = out
EXT_ANS = ans
EXECUTABLE_FILENAME = main
ALL_SRCS := $(wildcard *.cpp)
ALL_SRCS := $(wildcard *.cpp) $(wildcard */*.cpp)
SRCS     := $(filter-out check.cpp, $(ALL_SRCS))

all: compile test check
@@ -24,3 +24,7 @@ check: FORCE check.cpp
	./check

FORCE: ;

mobita:
	g++ -std=c++17 -o $(EXECUTABLE_FILENAME) $(SRCS)
	./${EXECUTABLE_FILENAME} 