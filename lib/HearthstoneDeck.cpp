#include "HearthstoneDeck.hpp"

Deck::Deck(int numberOfPossibleCards,int firstLegendary_):
	DECK(numberOfPossibleCards)
	,firstLegendary(firstLegendary_)
    ,totalOfCards(NUMBER_OF_CARDS)
    ,value(-1)
	,error(false)
{    
    //limit of equal cards by deck
	int8_t limitOfCards=2;
    
    //counts how many cards has this deck
	int numberOfAddedCards=0;
    
    //adds random cards
	while( numberOfAddedCards < NUMBER_OF_CARDS )
	{
		int r=random_int(0,numberOfPossibleCards);
		
		if ( r >= firstLegendary ) limitOfCards = 1;
		if ( r < firstLegendary ) limitOfCards = 2;
		
		if( DECK[r] < limitOfCards ) 
		{
			++DECK[r]; 
			++numberOfAddedCards;
		}
			
    }
}
Deck::Deck(const std::vector<int>& DECK_, int firstLegendary_)
    :DECK(DECK_)
    ,firstLegendary(firstLegendary_)
    ,value(-1)
	,error(false)
{
    //counts how many cards has this deck
	totalOfCards=0;
	for(int i:DECK)totalOfCards+=i;
}

int Deck::get_number_of_cards()
{
    int res=0;
    for(int n:DECK)
        if(n>0)++res;
    return res;
}

std::vector<int> Deck::get_list_of_cards() const
{
    std::vector<int>listOfCards;
    listOfCards.reserve(NUMBER_OF_CARDS);
    
    for(int c1=0;c1<DECK.size();++c1){
        if(DECK[c1]>0){
            listOfCards.push_back(c1);
            if(DECK[c1]>1)listOfCards.push_back(c1);
        }
    }
    return listOfCards;
}
void Deck::normalize(const std::vector<int>& l,const std::vector<int>& h){
    //checks if its entries are in a valid range
	for(int c1=0;c1<DECK.size();++c1)
	{
		if(DECK[c1]<l[c1])
		{
			totalOfCards-=DECK[c1];
			DECK[c1]=l[c1];
		}
		if(DECK[c1]>h[c1])
		{
			totalOfCards-=DECK[c1]-h[c1];
			DECK[c1]=h[c1];
        }
    }
        
    //add or remove cards to have the number of permitted cards
	if(totalOfCards<NUMBER_OF_CARDS)
		add_random_cards(NUMBER_OF_CARDS-totalOfCards,h);
	if(totalOfCards>NUMBER_OF_CARDS)
		remove_random_cards(totalOfCards-NUMBER_OF_CARDS,l);
}

void Deck::add_random_cards(int times, const std::vector<int>& h)
{
	int deckSize = DECK.size();
	int c1 = 0;
	while (c1 < times) {
		int r = random_int(0, deckSize);
		if (DECK[r] < h[r]) {
			++DECK[r];
			++totalOfCards;
			++c1;
		}
	}
}
void Deck::remove_random_cards(int times, const std::vector<int>& l) {
	int deckSize = DECK.size();
	int c1 = 0;
	while (c1 < times) {
		int r = random_int(0, deckSize);
		if (DECK[r] > l[r]) {
			--DECK[r];
			--totalOfCards;
			++c1;
		}
	}
}

Deck operator+(const Deck& d1,const Deck& d2){
    std::vector<int> list;
    list.reserve( d1.get_number_of_possible_cards() );
    for(int c1=0;c1<d1.get_number_of_possible_cards();++c1)
        list.push_back(d1.get_number_of_cards(c1)+d2.get_number_of_cards(c1));
    return Deck(list,d1.get_first_legendary());
}
Deck operator*(const int a,const Deck& d){
    std::vector<int> list;
    list.reserve( d.get_number_of_possible_cards() );
    for(auto c: d.get_deck() )
        list.push_back( a*c );
    return Deck(list,d.get_first_legendary());
}
Deck mutate(const Deck& d1, const Deck& d2, double p){
    std::vector<int> listOfCards;
    listOfCards.reserve(d1.get_number_of_possible_cards());
    for(int c1=0;c1<d1.get_number_of_possible_cards();++c1){
        if(probability_of_true(p))listOfCards.push_back(d2.get_number_of_cards(c1));
        else    listOfCards.push_back(d1.get_number_of_cards(c1));
    }
    return Deck(listOfCards,d1.get_first_legendary());
}
