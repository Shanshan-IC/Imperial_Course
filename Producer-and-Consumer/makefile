OBJ = main.o terminal.o rotors.o reflector.o plugboard.o check.o
EXE = enigma
CXX = g++
CPPFLAGS = -Wall -g -MMD

$(EXE): $(OBJ)
		$(CXX) $(CPPFLAGS) $(OBJ) -o $(EXE)
%.o: %.cpp
		$(CXX) $(CPPFLAGS) -c $<

-include $(OBJ:.o=.d)

.PHONY: clean

clean:
		rm -f $(EXE) $(OBJ) $(OBJ:.o=.d)
