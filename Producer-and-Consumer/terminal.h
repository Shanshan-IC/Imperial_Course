#ifndef terminal_h
#define terminal_h

class plugboard;
class reflector;
class rotors;

class terminal
{
 private:
  int num_rotor, number_rotor;
  char input;
  int initial_rotor[26];
 public:
  plugboard *pb;
  reflector *rf;
  rotors *rotorsarray[26];
  rotors *r;
  terminal(int argc, char **argv);
  void running(char &input);
};

#endif
