
#ifndef reflector_h
#define reflector_h

class reflector{
private:
    int cabble[26];
public:
    reflector(const char *reflector_file);
    void swap(char &input);
};

#endif
