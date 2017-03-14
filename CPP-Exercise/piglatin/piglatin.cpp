#include <iostream>
#include <cctype>
#include <fstream>
#include <cstring>
#include "piglatin.h"

using namespace std;

int findFirstVowel(const char* word)
{
	int index;
	for (index = 0; word[index]!= '\0'; index++)
	{
	 	switch(tolower(word[index]))
		{
			case 'y':
				if (index == 0||word[index+1] =='\0') 
					break;
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				return index;
		}
	}
	return -1;
}

void translateWord(const char* english, char* piglatin)
{
	int index;
	char temp[100];
	strcpy(temp, english);
	if (isupper(english[0]))
		temp[0] = tolower(temp[0]);
	//if it starts as a number
	if (isdigit(temp[0]))
	{
		strcpy(piglatin, temp);
		return;
	}
	index = findFirstVowel(temp);
	if (index == 0)
	{
		strcpy(piglatin, temp);
		strcat(piglatin, "way");
		return;
	}
	else if (index == -1)
	{
		strcpy(piglatin, temp);
		strcat(piglatin, "ay");
		return;
	}
	else
	{
		temp[index] = '\0';
		strcpy(piglatin, &english[index]);
		strcat(piglatin, temp);
		strcat(piglatin, "ay");
	}
	if (isupper(english[0]))
		piglatin[0] = toupper(piglatin[0]);

	return;
}

void translateStream(istream& input, ostream& output)
{
	if (input.fail())
		return;
	char lines[1000], word2[100], temp2[2];
	char word[100];
	int length;
	word[0] = '\0';
	word2[0] = '\0';
	temp2[1] = '\0';
	input.getline(lines, 1000);
	for(int i = 0; lines[i] != '\0'; i++)
	{	
		temp2[0] = lines[i];
		strcat(word, temp2);
		for (length = 0; word[length] != '\0'; length++);
		if (lines[i] == ' ')
		{
			word[length - 1] = '\0';

			translateWord(word, word2);
			output << word2 << ' ';
	
			word[0] = '\0';
		}
		
		if (ispunct(word[0]))
		{
			output << lines[i];
			word[0] = '\0';
		}
		if (ispunct(word[length - 1]))
		{
			word[length - 1] = '\0';
			translateWord(word, word2);
			output << word2 << lines[i];
			word[0] = '\0';
		}
	}
	cout << endl;
	translateStream(input, output);
}
