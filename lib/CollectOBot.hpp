#pragma once

#include "Hearthstone.hpp"
#include "RapidjsonUtils.hpp"

//const string names
const std::string	WIN("win"),
					LOSS("loss"),
					OPPONENT("opponent"),
					ME("me");

//recursive 4-parts method. Adds the info of matches to tuples.
template <class TuplesFile>
void count_match(	TuplesFile& Tuples,
					const int numberOfCards,
					const std::vector<int>& CardIndices,
					bool winFlag,
					std::vector<int>& Counters	)
{
	//creates the tuple, based in the indices which are in counters (tuple of cards)
    std::vector<int> Tuple(Counters.size());
    for( int c1=0; c1<Tuple.size(); ++c1)
		Tuple[ c1 ]=CardIndices[ Counters[ c1 ] ];
                        
    //gets the index in Tuples of Tuple 
    int i = mult_index(numberOfCards,Tuple);
            
    //in case is not an 1-tuple
    if(Tuples[i].HasMember("isValid"))
	{
		if(Tuples[i]["isValid"].GetInt()==1){
			Tuples[i]["playedMatches"].SetInt( Tuples[i]["playedMatches"].GetInt() + 1 );
			if(winFlag)
				Tuples[i]["wonMatches"].SetInt( Tuples[i]["wonMatches"].GetInt() + 1 );
		}
	}

	//in case is an 1-tuple
	else
	{
		Tuples[i]["playedMatches"].SetInt( Tuples[i]["playedMatches"].GetInt() + 1 );
		if(winFlag)
			Tuples[i]["wonMatches"].SetInt( Tuples[i]["wonMatches"].GetInt() + 1 );
	}
}
    
template <class TuplesFile>
void add_counted_matches_recursively(	TuplesFile& Tuples,
										const int numberOfCards,
										const std::vector<int>& CardIndices,
										bool winFlag,
										std::vector<int>& Counters,
										int level	)
{
    //checks the level to adjust indices
    if(level==0)Counters[level]=0;
    else    Counters[level] = Counters[level-1] + 1;
    
    //walks trought the indices to add counted matches to each tuple
    while(Counters[level]<CardIndices.size()-Counters.size()+1+level)
	{
		//recursive step
        if( level < Counters.size() - 1 )
        add_counted_matches_recursively(	Tuples,
                                            numberOfCards,
                                            CardIndices,
                                            winFlag,
                                            Counters,
                                            level+1	);
		//counts the match of this tuple
        else    count_match(Tuples,numberOfCards,CardIndices,winFlag,Counters);
                    
        ++Counters[level];
    }    
}
    
template <class MatchFile, class TuplesFile, class CardsFile>
void prepareInfoToAddMatch(	const MatchFile& Match, 
                            TuplesFile& Tuples, 
                            const std::string& cardClass,
                            const CardsFile& Cards,
                            const int TUPLE_NUMBER,
                            const std::string& P, 
                            const std::string& V	)
{
	//list with the indices of cards which appeared in this match
	std::vector<int> CardIndices;
                        
    auto& cardHistory=Match["card_history"];
	//fills cardIndices 
		for(int c2=0;c2<cardHistory.Size();++c2)
			if( P.compare(cardHistory[c2]["player"].GetString())==0 )
			{
				int index=get_card_index(cardHistory[c2]["card"]["id"].GetString(),Cards);
				if(index!=-1)CardIndices.push_back(index);
			}
                
	//checks if it counted at least a card
	if(CardIndices.size()>=TUPLE_NUMBER)
	{
		std::sort(CardIndices.begin(),CardIndices.end());
                
		//flag to know if this player won
		bool winFlag=false;
		if(V.compare(Match["result"].GetString())==0)winFlag=true;
            
		//adds the match to each card which appeared
		std::vector<int> counters(TUPLE_NUMBER);
		add_counted_matches_recursively(Tuples,Cards.Size(),CardIndices,winFlag,counters,0);
    }
}
    
template<class MatchDayFile, class TuplesFile, class CardsFile>
int add_counted_matches(	const MatchDayFile& MatchDay, 
							TuplesFile& Tuples, 
							const std::string& cardClass,
							const CardsFile& Cards,
							const int TUPLE_NUMBER	)
{
    //number of added matches
    int countedMatches=0;
        
    //walks trough games in this match day
    for(int c1=0;c1<MatchDay["games"].Size();++c1)
	{
		auto& Match = MatchDay["games"][c1];
        
        //checks if the class of "hero" player is equal to CARD CLASS
		if( cardClass.compare(Match["hero"].GetString())==0 )
		{
			prepareInfoToAddMatch(Match,Tuples,cardClass,Cards,TUPLE_NUMBER,ME,WIN);
			++countedMatches;
        }

        //checks if the class of "opponent" player is equal to CARD CLASS
		if( cardClass.compare(Match["opponent"].GetString())==0 )
		{
			prepareInfoToAddMatch(Match,Tuples,cardClass,Cards,TUPLE_NUMBER,OPPONENT,LOSS);
			++countedMatches;
        }
    }
    return countedMatches;
}
