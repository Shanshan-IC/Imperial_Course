#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <iterator>

#include "rotors.h"
#include "errors.h"

using namespace std;

//Read rotor file
rotors::rotors(char *rot_file)
{
    rotation = 0;
    int num;
    notch_number = 0;
    ifstream instream;
    instream.open(rot_file);
    
    //The first 26 numbers specify the mapping implemented by the rotor, stored in mapping[i]
    int i = 0;
    while (!instream.fail())
    {
        if (i < 26)
        {
            instream >> ws >> num;
            mapping[i] = num;
            i++;
        } 
        else
        {
            /*The remaining numbers specify the positions on the rotor where the turnover notches are placed.
            notch[] means which letters rotors are place on*/
            instream >> ws >> num;
            notch[notch_number] = num;
            notch_number++;
        }
    }
    instream.close();
}

void rotors::rotate()
{
    rotation = (rotation + 1) % 26;
}

//Use position(on the pos_file) to initial rotation
void rotors::set_mapping(int position)
{
    rotation = position;
}

//If the previous rotor has reached a notch location, this bool function isnotch would return true
bool rotors::isnotch()
{
    for(int i=0; i <= notch_number; i++)
    {
        if ( rotation == notch[i] )
            return true;
    }
    return false;
}
  
//Go forward for swapping letters
void rotors::swap_forwards(char &input)
{
    int temp;
    temp = input - 65;
    /*Find the index m(after rotate(rotation depends on intial rotation(position) and rotate times afterwards), return mapping[m] and the difference between the m and temp*/
    for (int m=0; m< 26;m++)
    {
	if( m == (temp + rotation) % 26)
	{
	    temp = (mapping[m] - m + temp + 26) % 26;
	    input = temp + 65;
	    return;
	}
    }
}

//Go backwards for swapping letters
void rotors::swap_backwards(char &input)
{
    int temp;
    temp = input - 65;
    //Find input corresponds to mapping[m], return the difference
    for (int m = 0;m < 26;m++)
    {
        if(mapping[m]== (temp + rotation) % 26)
        {
	  temp = (m - mapping[m] +temp + 26)% 26;
	  input = temp + 65;
	  return;
	}
    }
}

