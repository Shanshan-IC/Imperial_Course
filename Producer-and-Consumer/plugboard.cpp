#include <iostream>
#include <fstream>

#include "plugboard.h"

using namespace std;

//Read plugboaard file
plugboard::plugboard(const char *plug_file)
{
    
    ifstream instream;
    instream.open(plug_file);
    cabblenum = 0;
    int num;
    instream >> ws >> num;
    while (!instream.fail())
    {
        for (int i = 0; !instream.fail(); i++ )
        {
            cabble[i] = num;
            instream >> ws >> num;
            cabblenum++;
        }
    }
}
//Swap letter
void plugboard::swap(char &input)
{
    for (int i = 0; i < cabblenum; i++ )
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

