#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "check.h"
#include "terminal.h"

using namespace std;

class terminal;

int main(int argc, char **argv)
{
    //status means check all the files returns different errors values
    int status = 0;
    int num_rotor;
    char filename[50];
    
    //If argc < 3, it means there is no enough plugboard, reflector and rotors
    if (argc < 3)
    {
        cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?" << endl;
        return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    }
    else
        num_rotor = argc - 4;//The number of rotors
    
    //Loop through the files from the command line backwards
    //If index = 1, it is a plugboard; if index = 2, it is a reflector; if it is the last file, it is a rotors' position file, else it is rotors. Check every file's errors.
    for(int i = 1; i < argc; i++)
    {
        strcpy(filename, argv[i]);
        if (i == 1)
            status = check_plugboard(filename);
        else if (i == 2)
            status = check_reflector(filename);
        else if (i == argc - 1)
            status = check_pos(filename, num_rotor);
        else
            status = check_rotors(filename);
        if (status > 0)
            return status;
    }
   
    //Initial enigma
    terminal enigma = terminal(argc, argv);
   
    char input;
    cin >> ws >> input;
    while (!cin.eof())
    {
        //Check whether input is an upperletter
        if (input < 'A' || input > 'Z')
        {
            cerr <<  input << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
            return INVALID_INPUT_CHARACTER;
        }
        else
        {
            //running enigma and cout input
            enigma.running(input);
        }
        cin >> ws >> input;    
    }
    return 0;
}

