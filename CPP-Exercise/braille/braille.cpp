#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

#include "braille.h"

int encode_character(const char ch, char* braille)
{
	int ret = 6;
	if (isalpha(ch))
	{	
		if (isupper(ch))
		{
			ret += 6;
			strcat(braille, ".....0");
		}
		switch(tolower(ch))
		{
	case 'a':
      strcat(braille, "0....."); return ret;
    case 'b':
      strcat(braille, "00...."); return ret;
    case 'c':
      strcat(braille, "0..0.."); return ret;
    case 'd':
      strcat(braille, "0..00."); return ret;
    case 'e':
      strcat(braille, "0...0."); return ret;
    case 'f':
      strcat(braille, "00.0.."); return ret;
    case 'g':
      strcat(braille, "00.00."); return ret;
    case 'h':
      strcat(braille, "00..0."); return ret;
    case 'i':
      strcat(braille, ".0.0.."); return ret;
    case 'j':
      strcat(braille, ".0.00."); return ret;
    case 'k':
      strcat(braille, "0.0..."); return ret;
    case 'l':
      strcat(braille, "000..."); return ret;
    case 'm':
      strcat(braille, "0.00.."); return ret;
    case 'n':
      strcat(braille, "0.000."); return ret;
    case 'o':
      strcat(braille, "0.0.0."); return ret;
    case 'p':
      strcat(braille, "0000.."); return ret;
    case 'q':
      strcat(braille, "00000."); return ret;
    case 'r':
      strcat(braille, "000.0."); return ret;
    case 's':
      strcat(braille, ".000.."); return ret;
    case 't':
      strcat(braille, ".0000."); return ret;
    case 'u':
      strcat(braille, "0.0..0"); return ret;
    case 'v':
      strcat(braille, "000..0"); return ret;
    case 'w':
      strcat(braille, ".0.000"); return ret;
    case 'x':
      strcat(braille, "0.00.0"); return ret;
    case 'y':
      strcat(braille, "0.0000"); return ret;
    case 'z':
      strcat(braille, "0.0.00"); return ret;
    	}
	}
	
	if (isdigit(ch)) {
    	switch(ch) { 
    case '1':
      strcpy(braille,"..00000....."); return 12;
    case '2':
      strcpy(braille,"..000000...."); return 12;
    case '3':
      strcpy(braille,"..00000..0.."); return 12;
    case '4':
      strcpy(braille,"..00000..00."); return 12;
    case '5':
      strcpy(braille,"..00000...0."); return 12;
    case '6':
      strcpy(braille,"..000000.0.."); return 12;
    case '7':
      strcpy(braille,"..000000.00."); return 12;
    case '8':
      strcpy(braille,"..000000..0."); return 12;
    case '9':
      strcpy(braille,"..0000.0.0.."); return 12;
    case '0':
      strcpy(braille,"..0000.0.00."); return 12;
    	}
  	}

	if (ispunct(ch)) {
    	switch(ch) {
    case '.':
      strcpy(braille,".0..00"); return 6;
    case ',':
      strcpy(braille,".0...."); return 6;
    case ';':
      strcpy(braille,".00..."); return 6;
    case '-':
      strcpy(braille,"..0..0"); return 6;
    case '!':
      strcpy(braille,".00.0."); return 6;
    case '?':
      strcpy(braille,".00..0"); return 6;
    case '(':
      strcpy(braille,".00.00"); return 6;
    case ')':
      strcpy(braille,".00.00"); return 6;
   	 	}
  	}
	
	return -1;
}

void encode(char const* plaintext, char* braille)
{
	char target[100];
	strcpy(target, plaintext);

	if (target[0] == '\0')
		return;
	else
	{
		int length = encode_character(target[0], braille);
    	return encode(&target[1], &braille[length]); 
	}
}

void print_braille(char const* plaintext, ostream& out)
{
	char braille[100], target[100];
	strcpy(target, plaintext);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; target[j] != '\0' ; j++)
		{
			braille[0] = '\0';
			if (encode_character(target[j], braille)== 6)
				out << braille[i] << braille[i+3] << " ";
			else	
				out << braille[i] << braille[i+3] << " " << braille[i+6] << braille[i+9] << " ";
		}
		out << endl;
	}
	for (int m = 0; target[m] != '\0' ; m++)
	{
		if (encode_character(target[m], braille)== 12)
			out << "    " << target[m];
		else
			out << "  " << target[m];
	}
}
