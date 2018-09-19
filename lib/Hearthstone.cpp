#include "Hearthstone.hpp"

bool is_valid_tuple(int numberOfCards,int firstLegendary,const std::vector<int>& Counters)
{
	bool isValid = true;
    std::vector<int> Hand(numberOfCards);
    char limOfCards=2;
    for(int c:Counters)
	{
        limOfCards=2;
        ++Hand[c];
        if(c>=firstLegendary)limOfCards=1;
        if(Hand[c]>limOfCards)isValid = false;
    }
    return isValid;
}

std::vector<uint8_t> separate_bits(int n)
{
	std::vector<uint8_t> Result;
	while (n >= 128)
	{
		Result.push_back( ( 127 & n ) + 128 );
		n = n >> 7;
	}
	Result.push_back(n);
	return Result;
}
int collect_bits(const std::vector<uint8_t>& Numbers)
{
	int result=Numbers[Numbers.size() - 1];
	for (int c1 = Numbers.size() - 2; c1 >= 0; --c1)
	{
		int actual = (Numbers[c1] & 127) << 1;
		result = (result << 8) | actual;
		result = result >> 1;
	}
	return result;
}

bool is_a_valid_list_code(const Base64String& code)
{
	std::vector<uint8_t> Decimals = code.get_list_of_decimals();
	auto begin = Decimals.begin(), end = Decimals.end();
	if (*begin != 0)return false; ++begin; if (begin == end)return false; 
	if (*begin != 1)return false; ++begin; if (begin == end)return false; 
	if (*begin != 2)return false; ++begin; if (begin == end)return false; 
	if (*begin != 1)return false; ++begin; if (begin == end)return false; 
	while (*begin >= 128)
	{
		++begin;
		if (begin == end)return false;
	}++begin; if (begin == end)return false; 
	int numberOfSingleCards = *begin; ++begin; if (begin == end)return false; 
	for (int c1 = 0; c1 < numberOfSingleCards; ++c1)
	{
		while (*begin >= 128)
		{
			++begin;
			if (begin == end)return false;
		}++begin; if (begin == end)return false;
	} 
	int numberOfDoubleCards = *begin; ++begin; if (begin == end)return false;
	for (int c1 = 0; c1 < numberOfDoubleCards; ++c1)
	{
		while (*begin >= 128)
		{
			++begin;
			if (begin == end)return false;
		}++begin; if (begin == end)return false;
	} 
	if (*begin != 0)return false; 
	++begin;
	if (begin != end)return false;

	return true;
}
