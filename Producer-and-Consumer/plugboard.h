

#ifndef plugboard_h
#define plugboard_h

class plugboard{
private:
    int cabblenum;
    int cabble[26];
public:
    plugboard(const char *plug_file);
    void swap(char &input);
};


#endif
