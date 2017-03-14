#include<iostream>
#include<cstring>
#include <cctype>

using namespace std;

#include"multitap.h"

int encode_character(char ch, char* multitap)
{
	int i, j;
	char temp[2];
	temp[1] = '\0';
	const char *table[] = {" ", ".,!?", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
	if (isdigit(ch))
	{
		multitap[0] = '*';
		multitap[1] = ch;
		multitap[2] = '\0';
		return 2;
	}

	multitap[0] = '\0';
	
	for (i =0; i < 10; i++)
	{
		for (j =0; table[i][j]; j++)
		{	
			if (isupper(ch))
			{
				multitap[0] ='#';
				multitap[1] = '\0';
				if (table[i][j] == tolower(ch))
				{
					for (int m = 0; m <= j; m++)
					{
						temp[0] = '0' + i;
						strcat(multitap, temp);
					}
					return j + 2;
				}
			}
			else
			{		
				if (table[i][j] == ch)
				{
					for (int m = 0; m <= j; m++)
					{
						temp[0] = '0' + i;
						strcat(multitap, temp);
					}					
					return j+1;
				}

			}
		}
	}
	return -1;
}

void encode(const char* plaintext, char* multitap)
{
	char target[100], temp[100];
	int length, size;
	//multitap[0] = '\0';
	strcpy(target, plaintext);
	if (target[0] == '\0')
		return;
	size = encode_character(target[0], temp);
	for(length = 0;multitap[length]!= '\0'; length++);

	//upper and lower letter change
	if (temp[0] == '#' && multitap[length - size] == '#')
	{
		for(int i =0; i< size; i++)
			temp[i] = temp[i+1];
		temp[size] = '\0';
		strcat(multitap, temp);
		return encode(&plaintext[1], multitap);
	}
	if (temp[0] != '#' && multitap[length - size] == '#')
	{
		strcat(multitap, "#");
		strcat(multitap, temp);
		return encode(&plaintext[1], multitap);
	}
	//if (temp[0] == "#" && multitap[length - size - 1] != "#")
 	// the same number
	if (temp[0] == multitap[length-1])
	{
		strcat(multitap, "|");
		strcat(multitap, temp);
		return encode(&plaintext[1], multitap);
	}
	//general situation
	strcat(multitap, temp);
	return encode(&plaintext[1], multitap);
}
