EXE = a.out
CXX = c++
CFLAGS = -I include -g -std=c++11 -Wall -Wextra -O3

SRC = main.cc src/Agent.cc src/Environment.cc src/Experiment.cc
OBJ=$(SRC:.cc=.o)
INC = $(wildcard *.h)

all: $(EXE)

clean:
	$(info clean up)
	@rm -rf $(OBJ) $(EXE) src/*~ include/*~ *~ 
	
.PHONY: clean

%.o: %.cc
	$(CXX) -c $< -o $@ $(CFLAGS)

$(EXE): $(OBJ)
	$(CXX) $^ -o $(EXE)

main.o: include/Agent.h include/Environment.h include/Experiment.h

src/Agent.o: include/Agent.h
src/Environment.o: include/Environment.h
src/Experiment.o: include/Agent.h  include/Environment.h include/Experiment.h
