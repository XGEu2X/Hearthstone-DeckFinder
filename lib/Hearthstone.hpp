#pragma once

#include "General.hpp"
#include "Base64.hpp"

//const string names
const std::string	NEUTRAL("NEUTRAL"),
					LEGENDARY("LEGENDARY"),
					HERO("HERO"),
					FREE("FREE");

//number of cards by deck
const int NUMBER_OF_CARDS=30;

//returns the index of the first card which is LEGENDARY
template <class CardsFile>
int get_first_legendary_index(const CardsFile& Cards){
	int firstLegendaryIndex = Cards.Size();
	for( int c1=0; c1<Cards.Size(); ++c1)
		if (LEGENDARY.compare(Cards[c1]["rarity"].GetString()) == 0)
		{
			firstLegendaryIndex = c1;
			break;
		}
	return firstLegendaryIndex;
}

//returns the index of the card which have id as ... id.
template <class CardsFile>
int get_card_index(const std::string& id ,const CardsFile& Cards){
	int index=-1;
	for(int c1=0;c1<Cards.Size();++c1)
	{
		if( id.compare( Cards[c1]["id"].GetString() ) == 0 )
		{
			index=c1;
			break;
		}
	}
	return index;
}
// returns the index of the card which have dbfId as ... dbfId.
template <class CardsFile>
int get_card_index(const int dbfId, const CardsFile& Cards) {
	int index = -1;
	for (int c1 = 0; c1 < Cards.Size(); ++c1)
	{
		if (dbfId == Cards[c1]["dbfId"].GetInt())
		{
			index = c1;
			break;
		}
	}
	return index;
}

//checks if a tuple is able to be used
bool is_valid_tuple(int numberOfCards,int firstLegendary,const std::vector<int>& Counters);
//separates bits of numbers in the deckstring way
std::vector<uint8_t> separate_bits(int n);
//collects bits of numbers in the deckstring way
int  collect_bits(const std::vector<uint8_t>& Numbers);
//checks if a list of integer describes some kind of deck
/*
	Only checks:
		-Correct number of parameters
		-Correct constant numbers
*/
bool is_a_valid_list_code(const Base64String& code);
