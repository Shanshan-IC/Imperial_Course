#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

#include "terminal.h"
#include "errors.h"
#include "plugboard.h"
#include "reflector.h"
#include "rotors.h"

using namespace std;

//Initial the whole machie(terminal)
terminal::terminal(int argc, char **argv)
{
    char filename[50];
    num_rotor = argc - 4;
    number_rotor = 0;
    int initial_rotor[num_rotor];
    
    /*Loop through the array of input
      If index = 1, it is a plugboard; if index = 2, it is a reflector; if it is the last file, it is a rotors' position file, else it is rotors. Check every file's errors*/
    for(int i = 1; i < argc; i++)
    {
        strcpy(filename, argv[i]);
        if (i == 1)
            pb = new plugboard(filename);
        else if (i == 2)
            rf = new reflector(filename);
        //Read rotors' position file
        else if (i == argc - 1)
        {
            ifstream instream;
            instream.open(filename);
            int num;
            instream >> ws >> num;
            while (!instream.fail())
            {
                for (int j = 0; !instream.fail(); j++ )
                {
                    initial_rotor[j] = num;
                    instream >> ws >> num;
                }
                //Use rotors' position as initial rotors rotation
                for (int i = 0; i < num_rotor; i++)
                    rotorsarray[i] -> set_mapping(initial_rotor[i]);
            }
        }
	//Rotors array stores all the rotors
        else
        {
            rotorsarray[number_rotor] = new rotors(filename);
            number_rotor++;
        }
    }
}
//Terminal running function
void terminal::running(char &input)
{
    //Signal be sent to the plugboard, swap letters
    pb -> swap(input);
    //Every time input a letter, the final rotor rotates one time
    rotorsarray[num_rotor-1]->rotate();
    //If latter rotor mapping the notch, the former rotor rotates
    for( int i = num_rotor - 1; i > -1; i--)
    {
        if(rotorsarray[i]-> isnotch())
        {
	  if ((i-1) > -1)
                rotorsarray[i-1]->rotate();
	}
    }
    
    for( int i = num_rotor - 1; i > -1; i--){
        rotorsarray[i] -> swap_forwards(input);
    }
    //Signal be sent to the reflector, swap letters
    rf-> swap(input);
    //Inverse process
    for(int i = 0; i < num_rotor; i++)
        rotorsarray[i] -> swap_backwards(input);
    pb->swap(input);
    
    cout << input;
}
