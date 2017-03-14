#include <iostream>
#include <string>
#include "substring.h"

using namespace std;

bool is_prefix(char const* string, char const* target)
{
	if (string[0] == '\0')
		return true;
	else if (string[0]!= target[0])
		return false;
	else
		return is_prefix(&string[1], &target[1]);
	return true;
}

int substring_position(char const* string, char const* target)
{
	int index;
	if (is_prefix(string, target))
		return 0;
	if (target[0] != '\0')
	{
		index = substring_position(string, &target[1]);
		if (index == -1)
			return -1;
		else
			return index + 1;
	}
	return -1;
}
