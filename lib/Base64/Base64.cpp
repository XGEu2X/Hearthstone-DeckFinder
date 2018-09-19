#include "Base64.hpp"

uint8_t ctod(char c)
{
	uint8_t result=0;
	if ('A' <= c && c <= 'Z')result = c - 'A';
	else if ('a' <= c && c <= 'z')result = c - 'a'+26;
	else if ('0' <= c && c <= '9')result = c - '0'+52;
	else if (c == '+')result = 62;
	else if (c == '/')result = 63;
	return result;
}
char dtoc(uint8_t n)
{
	char result = 0;
	if (0 <= n && n <= 25)result = 'A' + n;
	else if (26 <= n && n <= 51)result = 'a' - 26 + n;
	else if (52 <= n && n <= 61)result = '0' - 52 + n;
	else if (n == 62)	result = '+';
	else if (n == 63)	result = '/';
	return result;

}

Base64String::Base64String(const std::string& s):
	string(s),
	error(false),
	error_message("")
{
	if (s.size() % 4 != 0)
	{
		error_message = "the size of the string is not correct";
		error = true;
		return;
	}
	
	int c1 = 0;
	while (c1 < s.size())
	{
		std::string quatrain = s.substr(c1, 4);
		std::vector<uint8_t> QNumbers(4);
		int flagToEndChar = 0;
		for (int c2 = 0; c2 < 4; ++c2)
		{
			QNumbers[c2] = ctod(quatrain[c2]);
			if (quatrain[c2] == '=')++flagToEndChar;
		}
		
		//the conversion
		uint8_t first = QNumbers[0];
		first = first << 1;
		if (QNumbers[1] >= 32)
		{
			first+=1;
			QNumbers[1] -= 32;
		}
		first = first << 1;
		if (QNumbers[1] >= 16)
		{
			first += 1;
			QNumbers[1] -= 16;
		}
		Decimals.push_back(first);

		if (flagToEndChar < 2)
		{
			uint8_t second = QNumbers[1];
			second = second << 1;
			if (QNumbers[2] >= 32)
			{
				second += 1;
				QNumbers[2] -= 32;
			}
			second = second << 1;
			if (QNumbers[2] >= 16)
			{
				second += 1;
				QNumbers[2] -= 16;
			}
			second = second << 1;
			if (QNumbers[2] >= 8)
			{
				second += 1;
				QNumbers[2] -= 8;
			}
			second = second << 1;
			if (QNumbers[2] >= 4)
			{
				second += 1;
				QNumbers[2] -= 4;
			}
			Decimals.push_back(second);
		}

		if (flagToEndChar < 1)
		{
			uint8_t third = QNumbers[3];
			if (QNumbers[2] >= 2)
			{
				third += 128;
				QNumbers[2] -= 2;
			}
			if (QNumbers[2] >= 1)
			{
				third += 64;
				QNumbers[2] -= 1;
			}
			Decimals.push_back(third);
		}

		c1 += 4;
	}
}
Base64String::Base64String(const std::vector<uint8_t>& Numbers):
	string(""),
	Decimals(Numbers),
	error(false),
	error_message("")
{
	int lastZeroes = ( 3-( Decimals.size() % 3 ) )%3;
	while ( (Decimals.size() % 3) != 0)Decimals.push_back(0);

	int c1 = 0;
	while (c1 < Decimals.size())
	{
		uint8_t c = Decimals[c1];
		c = c >> 2;
		string += dtoc(c);

		c = Decimals[c1 + 1];
		c = c >> 4;
		if ((1 & Decimals[c1]) == 1)c += 16;
		if ((2 & Decimals[c1]) == 2)c += 32;
		string += dtoc(c);

		if (lastZeroes==2 && ( Decimals.size()-c1 )==3)
		{
			string += '=';
		}
		else
		{
			c = Decimals[c1 + 2];
			c = c >> 6;
			if ((1 & Decimals[c1 + 1]) == 1)c += 4;
			if ((2 & Decimals[c1 + 1]) == 2)c += 8;
			if ((4 & Decimals[c1 + 1]) == 4)c += 16;
			if ((8 & Decimals[c1 + 1]) == 8)c += 32;
			string += dtoc(c);
		}

		if (lastZeroes > 0 && (Decimals.size() - c1) == 3)
		{
			string += '=';
		}
		else
		{
			c = Decimals[c1 + 2];
			if (c >= 128)c -= 128;
			if (c >= 64)c -= 64;
			string += dtoc(c);
		}

		c1 += 3;
	}
}
