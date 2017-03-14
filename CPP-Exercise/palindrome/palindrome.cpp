#include <iostream>
#include <cctype>
#include <cstring>
#include "palindrome.h"

using namespace std;

void reverse(char const* str1, char* str2)
{
	int length = 0;
	for (; str1[length] != '\0'; length++);
	str2[length] = '\0';
	for (int i = 0; length > 0; length--)
	{
		str2[i] = str1[length-1];
		i++;
	}
	return;
}

int compare(char const* str1, char const* str2)
{
	if (str1[0] == '\0')
		return 1;
	if (ignorable(str1[0]) && ignorable(str2[0]))
		return compare(&str1[1], &str2[1]);
	if (ignorable(str1[0]))
		return compare(&str1[1], str2);
	if (ignorable(str2[0]))
		return compare(str1, &str2[1]);
	if (tolower(str1[0]) != tolower(str2[0]))
		return 0;
	else 
		return compare(&str1[1], &str2[1]);
}

bool ignorable(char ch)
{
	if (ispunct(ch)|| ch == ' ')
		return true;
	return false;
}

int palindrome(char const* sentence)
{
	char string[100];
	reverse(sentence, string);
	if (compare(sentence, string))
		return 1;
	else
		return 0;
}

int anagram(char const* str1, char const* str2)
{
	char temp1[100], temp2[100];
	strcpy(temp1, str1);
	strcpy(temp2, str2);
	if (str1[0] == '\0' && str2[0] == '\0')
		return 1;
	//delete puncition and space
	for (int m = 0; str1[m] != '\0'; m++)
	{
		
		if (ignorable(str1[m]))
		{		
			temp1[m] = '\0';
			strcat(temp1, &str1[m+1]);
		}
	}
	for (int n = 0; str2[n] != '\0'; n++)
	{
		
		if (ignorable(str2[n]))
		{		
			temp2[n] = '\0';
			strcat(temp2, &str2[n+1]);
		}
	}

	for (int j = 0; temp2[j] != '\0'; j++)
	{
		if (tolower(temp1[0]) == tolower(temp2[j]))
		{
			temp2[j] = '\0';
			strcat(temp2, &temp2[j+1]);
			return anagram(&temp1[1], temp2);
		}
	}
	return 0;
}
