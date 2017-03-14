#include <iostream>
#include <cstring>
#include "correct.h"

using namespace std;

/* You are supplied with two helper functions */

/* converts a character into a binary string representation */
void ascii_to_binary(char ch, char *binary);

/* converts a binary string representation into a character */
char binary_to_ascii(char *binary);

void ascii_to_binary(char ch, char *binary) {
  for (int n = 128; n; n >>= 1) 
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

char binary_to_ascii(char *binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}

/* now add your own functions here */
void text_to_binary(const char* str, char* binary)
{
	char binary2[300];
	binary2[0] = '\0';
	if (str[0] == '\0')
	{
		binary[0] = '\0';
		return;
	}
	
	ascii_to_binary(str[0], binary2);
	strcat(binary, binary2);
	return text_to_binary(&str[1], &binary[8]);
	
}

void binary_to_text(const char* binary, char* str)
{
	char temp[9];
	if (binary[0] == '\0')
	{
		str[0] = '\0';
		return;
	}
	for (int i = 0; i < 8;i++)
		temp[i] = binary[i];
	temp[8] = '\0';
	str[0] = binary_to_ascii(temp);
	return binary_to_text(&binary[8], &str[1]);
}

void add_error_correction(const char* data, char* correct)
{
	if (data[0] == '\0')
	{
		correct[0] = '\0';
		return;
	}
	char ch1, ch2, ch3;
	ch1 = parity(data[0], data[1], data[3]);
	ch2 = parity(data[0], data[2], data[3]);
	ch3 = parity(data[1], data[2], data[3]);
	correct[0] = ch1;
	correct[1] = ch2;
	correct[2] = data[0];
	correct[3] = ch3;
	correct[4] = data[1];
	correct[5] = data[2];
	correct[6] = data[3];
	correct[7] = '\0';
	add_error_correction(&data[4], &correct[7]);
}

int decode(const char* received, char* decoded)
{
	
	if (received[0] == '\0')
	{
		decoded[0] = '\0';
		return 0;
	}
	
	int ch1, ch2, ch3;
	ch1 = parity2(received[3], received[4], received[5], received[6]);
	ch2 = parity2(received[1], received[2], received[5], received[6]);
	ch3 = parity2(received[0], received[2], received[4], received[6]);
	int pos;
	pos = ch3 + ch2 * 2 + ch1 * 4;
	char temp[8];

	for (int i = 0; i < 7; i++)
		temp[i] = received[i];

	temp[7] = '\0';
	if (pos!= 0)
	{
		if (temp[pos - 1] == '0')
			temp[pos - 1] = '1';
		else
			temp[pos - 1] = '0';
	}
	decoded[0] = temp[2];
	decoded[1] = temp[4];
	decoded[2] = temp[5];
	decoded[3] = temp[6];
	decoded[4] = '\0';
	
	if (pos == 0)
		return decode(&received[7], &decoded[4]);
	else
		return 1 + decode(&received[7], &decoded[4]);
}

char parity(char d1, char d2, char d3)
{
	if ((d1+ d2 + d3) % 2 == 0)
		return '0';
	return '1';
}

int parity2(char b1, char b2, char b3, char b4)
{
	if ((b1+ b2 + b3 + b4) % 2 == 0)
		return 0;
	return 1;
}

