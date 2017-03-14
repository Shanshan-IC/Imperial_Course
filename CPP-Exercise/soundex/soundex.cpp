#include <iostream>
#include <cctype>
#include <cstring>
#include "soundex.h"

using namespace std;

void encode(char const* surname, char* soundex)
{
	soundex[0] = toupper(surname[0]);
	int i, j;
	for (i = 0, j = 1; surname[i]!= '\0'&& j < 4; i++)
	{
		if (encode_char(surname[i]) != '0' && encode_char(surname[i])!= encode_char(surname[i-1]))
		{	
			soundex[j] = encode_char(surname[i]);
			j++;
		}
	}
	if (j < 4)
	{	
		for (; j < 4; j++)
		soundex[j] = '0';
	}
	soundex[4] = '\0';
	return;
}

int compare(char const* str1, char const* str2)
{
	if (str1[0] == '\0')
		return 1;
	if (str1[0] != str2[0])
		return 0;
	else
		return compare(&str1[1], &str2[1]);
	return 1;
}

int count(const char* surname, const char* sentence)
{
	char soundex1[5], soundex2[5], target[100];
	char *tok;
	int amount = 0;
	strcpy(target, sentence);
	encode(surname, soundex1);
	for (tok = strtok(target, ", ."); tok != NULL; tok = strtok(NULL, ", ."))
	{	
		encode(tok, soundex2);
		if (compare(soundex1, soundex2))
			amount++;
	}
	return amount;
}

char encode_char(char ch)
{
	switch (ch)
	{
		case 'b':
		case 'f':
		case 'p':
		case 'v':
			return '1';
		case 'c':
		case 'g':
		case 'j':
		case 'k':
		case 'q':
		case 's':
		case 'x':
		case 'z':
			return '2';
		case 'd':
		case 't':
			return '3';
		case 'l':
			return '4';
		case 'm':
		case 'n':
			return '5';
		case 'r':
			return '6';
		default:
			return '0';
	}
}
