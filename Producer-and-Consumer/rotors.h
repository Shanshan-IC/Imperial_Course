#ifndef rotors_h
#define rotors_h

class rotors{
private:
    int mapping[26];
    int notch[26];
    int initial_rotor, notch_number;
    int pos[50];
public:
    int rotation;
    rotors(char *rot_file);
    void rotate();
    void set_mapping(int position);
    bool isnotch();
    void swap_forwards(char &input);
    void swap_backwards(char &input);
};

#endif 
