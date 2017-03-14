#include <iostream>
#include <fstream>

#include "reflector.h"

using namespace std;

//Read reflector file
reflector::reflector(const char *reflector_file)
{
    ifstream instream;
    instream.open(reflector_file);
    int num;
    instream >> ws >> num;
    while (!instream.fail())
    {
        for (int i = 0; !instream.fail(); i++ )
        {
            cabble[i] = num;
            instream >> ws >> num;
        }
    }
}

//Swap letters
void reflector::swap(char &input)
{
    
    for (int i = 0; i < 26; i++ )
    {
        if (input == 65 + cabble[i])
        {
            if (i % 2 == 0)
            {
                input = 65 + cabble[i+1];
                return;
            }
            else
            {
                input = 65 + cabble[i-1];
                return;
            }
        }
    }
}
