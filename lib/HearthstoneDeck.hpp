#pragma once

#include "Hearthstone.hpp"

class Deck{
public:
    //constructors
	//makes a deck with random cards
	Deck(int numberOfPossibleCards, int firstLegendary);
	//makes a deck with cards in DECK
	Deck(const std::vector<int>& DECK, int firstLegendary);
	//makes a deck with cards provided by CODE
	template <class GeneralFile>
	Deck(const GeneralFile& Cards, const std::string& Code, int firstLegendary_ = -1) :
		DECK(Cards.Size()),
		firstLegendary(firstLegendary_),
		value(-1),
		code(Base64String(Code)),
		error(false)
	{
		if ( !is_a_valid_list_code( code ) )
		{
			error_message = "This is not a valid code";
			error = true;
			return;
		}

		std::vector<uint8_t> Decimals = code.get_list_of_decimals();
		auto IT = Decimals.begin();
		IT += 4;
		while (*IT >= 128)++IT;
		++IT;

		//walks the list of single cards
		int numberOfSingleCards = *IT; ++IT;
		for (int c1 = 0; c1 < numberOfSingleCards; ++c1)
		{
			std::vector<uint8_t> List;
			while (*IT >= 128)
			{
				List.push_back(*IT);
				++IT;
			}
			List.push_back(*IT);
			++IT;
			int i = get_card_index(collect_bits(List), Cards);
			if (i >= DECK.size())
			{
				error_message = "A card is not in the cards file";
				error = true;
				return;
			}
			++DECK[i];
		}
		//walks the list of double cards
		int numberOfDoubleCards = *IT; ++IT;
		for (int c1 = 0; c1 < numberOfDoubleCards; ++c1)
		{
			std::vector<uint8_t> List;
			while (*IT >= 128)
			{
				List.push_back(*IT);
				++IT;
			}
			List.push_back(*IT);
			++IT;
			DECK[get_card_index(collect_bits(List), Cards)] += 2;
		}

		totalOfCards = numberOfSingleCards + (2 * numberOfDoubleCards);
	
		if (firstLegendary == -1)
		{
			for (int c1 = 0; c1 < Cards.Size(); ++c1)
			{
				if (LEGENDARY.compare(Cards[c1]["rarity"].GetString()) == 0)
				{
					firstLegendary = c1;
					break;
				}
			}
		}
	}
    //methods
	inline double get_value() const{return value;}
	inline void set_value(double v){value=v;}
	int get_number_of_cards();
	inline int get_number_of_cards(const int index) const{return DECK[index];}
	inline int get_first_legendary() const{return firstLegendary;}
	inline int get_number_of_possible_cards() const{return DECK.size();}
	inline std::string get_deck_code() const { return code.get_string(); }
	inline std::vector<int> get_deck()const{return DECK;}
	//makes a list with the cards which are in this deck (with repetitions)
	std::vector<int> get_list_of_cards() const;
    //normalizes this deck into constrains that have to fulfill
	void normalize(const std::vector<int>& l,const std::vector<int>& h);
	//creates the deck code
	template<class CardsFile>
	std::string get_deck_code(const CardsFile& Cards, int heroDbfId)
	{
		if (!code.is_void())return code.get_string();
		std::vector<int> ListOfdbfIdsSingle, ListOfdbfIdsDouble;
		ListOfdbfIdsSingle.reserve(NUMBER_OF_CARDS); ListOfdbfIdsDouble.reserve(NUMBER_OF_CARDS);
		int singleCards = 0;
		for (int c1 = 0; c1 < DECK.size(); ++c1)
		{
			if (DECK[c1] > 0 && DECK[c1] < 2)
			{
				ListOfdbfIdsSingle.push_back(Cards[c1]["dbfId"].GetInt());
				++singleCards;
			}
			if (DECK[c1] > 1)
			{
				ListOfdbfIdsDouble.push_back(Cards[c1]["dbfId"].GetInt());
			}
		}
		
		std::vector<uint8_t>  Decimals;
		//reserved
		Decimals.push_back(0);
		//version
		Decimals.push_back(1);
		//standar
		Decimals.push_back(2);
		//number of heroes
		Decimals.push_back(1);
		//hero code
		auto DecimalsHeroDbfId = separate_bits(heroDbfId);
		Decimals.insert(Decimals.end(), DecimalsHeroDbfId.begin(), DecimalsHeroDbfId.end());
		//number of single cards
		Decimals.push_back(singleCards);
		//single cards
		std::sort(ListOfdbfIdsSingle.begin(), ListOfdbfIdsSingle.end());
		for (int i : ListOfdbfIdsSingle)
		{
			auto DecimalsCardsDbfId = separate_bits(i);
			Decimals.insert(Decimals.end(), DecimalsCardsDbfId.begin(), DecimalsCardsDbfId.end());
		}
		//number of double cards
		Decimals.push_back((NUMBER_OF_CARDS-singleCards)/2);
		//double cards
		std::sort(ListOfdbfIdsDouble.begin(), ListOfdbfIdsDouble.end());
		for (int i : ListOfdbfIdsDouble)
		{
			auto DecimalsCardsDbfId = separate_bits(i);
			Decimals.insert(Decimals.end(), DecimalsCardsDbfId.begin(), DecimalsCardsDbfId.end());
		}
		Decimals.push_back(0);

		code=Base64String(Decimals);

		return code.get_string();
	}
	//prints the names and quantity of each card in this deck
	template <class CardsFile>
	void print(const CardsFile& Cards,const int heroDbfId)
	{
		for (int c1 = 0; c1 < DECK.size(); ++c1)
		{
			if (DECK[c1] > 0)
			{
				std::cout << Cards[c1]["name"].GetString() << " " << DECK[c1] << std::endl;
			}
		}
		std::cout << "https://deck.codes/" << this->get_deck_code(Cards, heroDbfId) << std::endl;
	}
	inline bool has_error() { return error; }
	inline std::string get_error_message() { return error_message; }
        
private:
    //variables
	std::vector<int> DECK;
	int firstLegendary, totalOfCards;
	double value;
	Base64String code;
	bool error;
	std::string error_message;
    //methods
	//adds "times" random cards to deck
	void remove_random_cards(int times,const std::vector<int>& l);
	//removes "times" random cards to deck
	void add_random_cards(int times,const std::vector<int>& h);
};

Deck operator +(const Deck& d1,const Deck& d2);
Deck operator *(const int a,const Deck& d);
inline bool operator >(const Deck& d1,const Deck& d2){return d1.get_value() > d2.get_value();}
//returns a deck which has d1_i as x_i with probability p, has d2_i in other case
Deck mutate(const Deck& d1, const Deck& d2, double p);
