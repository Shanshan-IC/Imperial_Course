#include <iostream>
#include <fstream>

#include "check.h"
#include "errors.h"

using namespace std;

//Check plugboard file
int check_plugboard(const char *plug_file)
{
    ifstream instream;
    instream.open(plug_file);
    
    //Check whether it encounters any errors opening
    if (instream.fail())
    {
        cerr << "ERROR_OPENING_CONFIGURATION_FILE" << endl;
        return ERROR_OPENING_CONFIGURATION_FILE;
    }
    
    int num;
    int number[26];
    int count = 0;
    instream >> ws >> num;
    for (int i = 0; !instream.fail(); i++ )
    {
	//Check whether the plugboard configuration file is not well-formed
        for (int j = 0; j < i; j++)
        {
            if (number[j] == num && count < 26)
            {
                instream.close();
                cerr << "IMPOSSIBLE_PLUGBOARD_CONFIGURATION" << endl;
                return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
            }
        }
            
        //Check whether num is not between 0 and 25
        if (num < 0 || num > 25)
        {
            instream.close();
            cerr << "INVALID_INDEX" << endl;
            return INVALID_INDEX;
        }
            
        number[i] = num;
        count++;
        instream >> ws >> num;
    }
    
    //Check whether it contains any characters other than numeric characters(When it encounters non-numerica character, instream failed, but it is not in the end of file.)
    if (!instream.eof())
    {
        instream.close();
        cerr << "Non-numeric character in plugboard file plugboard.pb" << endl;
        return NON_NUMERIC_CHARACTER;
    }
    
    //Check whether it contains an odd number of numbers or over 26 numbers
    if (count % 2 != 0 || count > 26)
    {
        instream.close();
        cerr << "Incorrect number of parameters in plugboard file plugboard.pb" << endl;
        return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }
    
    instream.close();
    return NO_ERROR;
}

//Check rotors file
int check_rotors(const char *rotor_file)
{
    ifstream instream;
    instream.open(rotor_file);
    //Check whether it encounters any errors opening
    if (instream.fail())
    {
        cerr << "ERROR_OPENING_CONFIGURATION_FILE" << endl;
        return ERROR_OPENING_CONFIGURATION_FILE;
    }
    
    int num;
    int number[26];
    int count = 0;
    
    instream >> ws >> num;
    for (int i = 0; !instream.fail(); i++ )
    {
        //The first 26 numbers specify the mapping implemented by the rotor
        if (i < 26)
        {
        //Check whether it attempts to map more than one input to the same output
            number[i] = num;
            for (int j = 0; j < i; j++)
            {
                if (number[j] == num)
                {
                    instream.close();
                    cerr << "Invalid mapping of input " << i << " to output " << num << " (output " << num;
                    cerr << " is already mapped to from input " << j << ") in rotor file: rotor.rot" <<endl;
                    return INVALID_ROTOR_MAPPING;
                }
            }
                
            //Check whether num is not between 0 and 25
            if (num < 0 || num > 25)
            {
                instream.close();
                cerr << "INVALID_INDEX" << endl;
                return INVALID_INDEX;
            }
                
            count++;
            instream >> ws >> num;
        }
        else
            instream >> ws >> num;
        }
    
    //Check whether it contains any characters other than numeric characters
    if (!instream.eof())
    {
        instream.close();
        cerr << "Non-numeric character for mapping in rotor file rotor.rot" << endl;
        return NON_NUMERIC_CHARACTER;
    }
    
    //Check whether it does not provide a mapping for some inputs
    if (count < 26)
    {
        instream.close();
        cerr << "Not all inputs mapped in rotor file: rotor.rot" << endl;
        return INVALID_ROTOR_MAPPING;
    }
    
    instream.close();
    return NO_ERROR;
}

//Check postion file
int check_pos(const char *pos_file, int num_rotor)
{
    ifstream instream;
    instream.open(pos_file);
    
    //Check whether it encounters any errors opening
    if (instream.fail())
    {
        cerr << "ERROR_OPENING_CONFIGURATION_FILE" << endl;
        return ERROR_OPENING_CONFIGURATION_FILE;
    }
    
    int num, i;
    instream >> ws >> num;
    for (i = 0; !instream.fail(); i++ )
    {
	//Check whether num is not between 0 and 25
        if (num < 0 || num > 25)
        {
            instream.close();
            cerr << "INVALID_INDEX" << endl;
            return INVALID_INDEX;
        }
        instream >> ws >> num;
    }

    //Check whether it contains any characters other than numeric characters
    if (!instream.eof())
    {
        instream.close();
        cerr << "Non-numeric character in rotor positions file rotor.pos" << endl;
        return NON_NUMERIC_CHARACTER;
    }
    
    //Check whether no starting position for some rotors in rotor position file
    if (i < num_rotor)
    {
        instream.close();
        cerr << "No starting position for rotor 0 in rotor position file: rotor.pos" << endl;
	//cout << NO_ROTOR_STARTING_POSITION << endl;
        return NO_ROTOR_STARTING_POSITION;
    }
 
    instream.close();
    return NO_ERROR;
}

//Check reflector file
int check_reflector(const char *ref_file)
{
    ifstream instream;
    instream.open(ref_file);
    
    //Check whether it encounters any errors opening
    if (instream.fail())
    {
        cerr << "ERROR_OPENING_CONFIGURATION_FILE" << endl;
        return ERROR_OPENING_CONFIGURATION_FILE;
    }
    
    int num;
    int count = 0;
    int number[26];
    
    instream >> ws >>num;
    for (int i = 0; !instream.fail(); i++ )
    {
	number[i] = num;
            
	//Check whether it attempts to map an input to itself or pair each index with more than one other
	for (int j = 0; j < i; j++)
	{
            if (number[j] == num && count < 26)
            {
                    instream.close();
                    cerr << "INVALID_REFLECTOR_MAPPING" << endl;
                    return INVALID_REFLECTOR_MAPPING;
            }
        }
            
        //Check whether num is not between 0 and 25
        if (num < 0 || num > 26)
        {
            instream.close();
            cerr << "INVALID_INDEX" << endl;
            return INVALID_INDEX;
        }
            
        count++;
        instream >> ws >> num;
    }
    
    //Check whether it contains any characters other than numeric characters
    if (!instream.eof())
    {
        instream.close();
        cerr << "Non-numeric character in reflector file reflector.rf" << endl;
        return NON_NUMERIC_CHARACTER;
    }
    
    //Check whether the number of parameters in reflector file is odd
    if (count % 2 != 0)
    {
        instream.close();
        cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf" << endl;
        return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
    
    //Check whether it does not contain exactly 13 pairs of numbers
    if (count != 26)
    {
        instream.close();
        cerr << "Insufficient number of mappings in reflector file: reflector.rf" << endl;
        return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
    
    instream.close();
    return NO_ERROR;
}
