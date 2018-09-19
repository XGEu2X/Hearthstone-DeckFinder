#pragma once

#include <fstream>
#include "Hearthstone.hpp"

class ResultsDeck 
{
public:
	//Constructors
	ResultsDeck(std::string cardClass, int playedMatches, int wonMatches);
	//methods
	inline void add_id(const std::string& id) { ListOfNames.push_back(id); }
	template <class CardsFile>
	void fill_list_of_indices(const CardsFile& Cards) 
	{
		ListOfIndices.clear();
		ListOfIndices.reserve(ListOfNames.size());
		for(std::string s:ListOfNames)
		{
			for (int c1 = 0; c1 < Cards.Size(); ++c1)
			{
				if (s.compare(Cards[c1]["name"].GetString())==0)
				{
					ListOfIndices.push_back(c1);
					break;
				}
			}
		}
		std::sort(ListOfIndices.begin(),ListOfIndices.end());
	}
	void print_names();
	void print_indices();
    void print();
    //Variables
	std::string cardClass;
	int playedMatches, wonMatches;
	std::vector<std::string> ListOfNames;
	std::vector<int> ListOfIndices;
private:
};

class ResultsFile
{
public:
	//Constructors
	ResultsFile(const std::string& fileName);
	//methods
	template <class CardsFile>
	void fill_list_of_indices(const CardsFile& Cards, int numberOfResultsDeck) 
	{
		ListOfResultsDecks[numberOfResultsDeck].fill_list_of_indices(Cards);
	}
	inline std::vector<ResultsDeck> get_list_of_Results_decks()const { return ListOfResultsDecks; }
	inline std::vector<ResultsDeck>::iterator get_list_of_Results_decks_begin(){return ListOfResultsDecks.begin();}
	inline std::vector<ResultsDeck>::iterator get_list_of_Results_decks_end(){return ListOfResultsDecks.end();}
	void print();
private:
	//Variables
	std::vector<ResultsDeck> ListOfResultsDecks;

};

template <class TuplesFile, class CardsFile>
void add_counted_stats_recursively(	const std::vector<int> Indices,
									const int playedMatches,
									const int wonMatches,
									TuplesFile& Tuples,
									const CardsFile& Cards,
									std::vector<int>& Counters,
									int level	) 
{
	if (level > 0)Counters[level] = Counters[level - 1] + 1;
	while (Counters[level] < Indices.size() - Counters.size() + 1 + level)
	{
		std::vector<int> Tuple(Counters.size());
		for (int c1 = 0; c1 < Counters.size()-1; ++c1)
			Tuple[c1] = Indices[Counters[c1]];
        
		if (level == Counters.size() - 1)
		{
			Tuple[level] = Indices[Counters[level]];
			int index = mult_index(Cards.Size(), Tuple);
			Tuples[index]["playedMatches"].SetInt(Tuples[index]["playedMatches"].GetInt() + playedMatches);
			Tuples[index]["wonMatches"].SetInt(Tuples[index]["wonMatches"].GetInt() + wonMatches);
		}
		else
		{
			add_counted_stats_recursively(Indices,playedMatches,wonMatches,Tuples,Cards,Counters,level+1);
		}
		++Counters[level];
	}
}

template <class TuplesFile, class CardsFile>
int add_counted_stats(ResultsFile& RF,
	TuplesFile& Tuples,
	const std::string& CARD_CLASS,
	const CardsFile& Cards,
	const int TUPLE_NUMBER) 
{
	int countedStats = 0;
	auto IT = RF.get_list_of_Results_decks_begin(), listEnd= RF.get_list_of_Results_decks_end();
	int ResultsDeckID = 0;
	while (IT != listEnd)
	{
		if (IT->cardClass == CARD_CLASS)
		{
			RF.fill_list_of_indices(Cards,ResultsDeckID);
            
			countedStats += IT->playedMatches;
			std::vector<int> Counters(TUPLE_NUMBER);
            if(IT->ListOfIndices.size()>=TUPLE_NUMBER)
                add_counted_stats_recursively(IT->ListOfIndices, IT->playedMatches, IT->wonMatches, Tuples, Cards, Counters, 0);
		}
		++IT;
		++ResultsDeckID;
	}
	return countedStats;
}
