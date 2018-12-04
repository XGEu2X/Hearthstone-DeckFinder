#include "PrepareCards.h"

//fills the object file in a recursive way.
template <class GeneralFile>
void fill_tuples_file_recursively(	GeneralFile& File,		
									const int numberOfCards, 
									const int firstLegendary, 
									std::vector<int>& counters, 
									int level	) 
{
	//set the index in the current recursive level
	if (level == 0)counters[level] = 0;
	else    counters[level] = counters[level - 1];

	//walk trough the indices in this level
	while (counters[level]<numberOfCards) 
	{
		//recursive step
		if (level<counters.size() - 1)
			fill_tuples_file_recursively(File, numberOfCards, firstLegendary, counters, level + 1);

		//if is in the last level, add the respective tuple 
		else 
		{
			//create the tuple object
			rapidjson::Value tuple(rapidjson::kObjectType);

			//add some members
			tuple.AddMember("isValid", (is_valid_tuple(numberOfCards, firstLegendary, counters)) ? 1 : 0, File.GetAllocator());
			tuple.AddMember("playedMatches", 0, File.GetAllocator());
			tuple.AddMember("wonMatches", 0, File.GetAllocator());
			tuple.AddMember("winRatio", 0.0, File.GetAllocator());

			//create a member which will have the indices of the cards of this tuple
			rapidjson::Value Indices;
			Indices.SetArray();
			for (int c : counters)Indices.PushBack(c, File.GetAllocator());

			//add the array to the tuple
			tuple.AddMember("Indices", Indices, File.GetAllocator());

			//add the tuple object to the file
			File.PushBack(tuple, File.GetAllocator());
		}

		++counters[level];
	}
}

int main(int argc, char *argv[]) 
{
	//reads parameters
	//checks the number of parameters
	if (argc < 3 || argc > 4)
	{
		std::cout << "format: ./PrepareCards TUPLE_NUMBER CARD_CLASS USE_MY_CARDS (1 if yes, 0 if not)" << std::endl;
		return 0;
	}
	//reads TUPLE_NUMBER
	std::string s_TUPLE_NUMBER(argv[1]);
	std::istringstream ss_TUPLE_NUMBER(argv[1]);
	int TUPLE_NUMBER;
	if (!(ss_TUPLE_NUMBER >> TUPLE_NUMBER)) 
	{
		std::cout << "Error with arguments" << std::endl;
		return 0;
	}
	//reads CARD_CLASS
	std::string CARD_CLASS(argv[2]);
    //reads if you will use only your cards
    bool CARDS_FILE_FLAG = 0;
    if(argc > 3)
    {
        std::istringstream s_CARDS_FILE_FLAG(argv[3]);
        if(!(s_CARDS_FILE_FLAG >> CARDS_FILE_FLAG))
        {
            std::cout << "Error with arguments" << std::endl;
            return 0;
        }
    }
    
	//It makes the list of cards of this class
	if (TUPLE_NUMBER == 1) 
	{
		//Here is the list of valid sets (Change for something upgradable**)
		std::vector<std::string> LIST_OF_VALID_SETS;
		LIST_OF_VALID_SETS.push_back("CORE");
		LIST_OF_VALID_SETS.push_back("EXPERT1");
		LIST_OF_VALID_SETS.push_back("UNGORO");
		LIST_OF_VALID_SETS.push_back("ICECROWN");
		LIST_OF_VALID_SETS.push_back("LOOTAPALOOZA");
		LIST_OF_VALID_SETS.push_back("GILNEAS");
		LIST_OF_VALID_SETS.push_back("BOOMSDAY");

		//makes an object with all the cards in game
		rapidjson::Document document = read_json("data/cards.json");

		//fills a list whith the cards that have to prepare
		std::vector<Card> listOfCards;
		for (int c1 = 0; c1<document.Size(); ++c1)
		{
			if (	document[c1].HasMember("rarity") &&
					document[c1].HasMember("set") &&
					document[c1].HasMember("cardClass") &&
					document[c1].HasMember("name") &&
					document[c1].HasMember("dbfId") &&
					document[c1].HasMember("id") &&
					document[c1].HasMember("collectible")	)
			{
				std::string set = document[c1]["set"].GetString();
				if (!is_in(set, LIST_OF_VALID_SETS))continue;

				std::string cardClass(document[c1]["cardClass"].GetString());
				if (cardClass == CARD_CLASS || cardClass == NEUTRAL)
				{
					listOfCards.push_back(Card(	document[c1]["id"].GetString(),
												document[c1]["dbfId"].GetInt(),
												document[c1]["name"].GetString(),
												document[c1]["cardClass"].GetString(),
												document[c1]["set"].GetString(),
												document[c1]["rarity"].GetString()	));
				}
			}
		}

		//sorts the cards, leaving legendary cards at the end
		std::sort(listOfCards.begin(), listOfCards.end(), [](const Card& a, const Card& b)->bool {
			if (a.get_rarity() != LEGENDARY && b.get_rarity() == LEGENDARY)return true;
			return false;
		});

		int firstLegendary = 0;
		while (listOfCards[firstLegendary].get_rarity() != LEGENDARY)
		{
			++firstLegendary;
			if (firstLegendary == listOfCards.size())break;
		}

		//makes the rapidjson object to write the file
		rapidjson::Document cards;
		cards.SetArray();
		for (auto& c : listOfCards) {
			rapidjson::Value card(rapidjson::kObjectType);

			card.AddMember("id", rapidjson::Value(c.get_id().c_str(), cards.GetAllocator()), cards.GetAllocator());
			card.AddMember("dbfId", c.get_dbfId(), cards.GetAllocator());
			card.AddMember("name", rapidjson::Value(c.get_name().c_str(), cards.GetAllocator()), cards.GetAllocator());
			card.AddMember("cardClass", rapidjson::Value(c.get_cardClass().c_str(), cards.GetAllocator()), cards.GetAllocator());
			card.AddMember("set", rapidjson::Value(c.get_set().c_str(), cards.GetAllocator()), cards.GetAllocator());
			card.AddMember("rarity", rapidjson::Value(c.get_rarity().c_str(), cards.GetAllocator()), cards.GetAllocator());
			card.AddMember("playedMatches", 0, cards.GetAllocator());
			card.AddMember("wonMatches", 0, cards.GetAllocator());
			card.AddMember("winRatio", 0.0, cards.GetAllocator());

			cards.PushBack(card, cards.GetAllocator());
		}

		if(CARDS_FILE_FLAG)
        {
            std::cout << "Im in";
            nlohmann::json myCardsFile = nlohmann_read_json("data/HSCT.json");
            std::vector<std::string> Names;
            //lists neutral cards
            std::string neutral(upper_to_lowercase(NEUTRAL));
            for(nlohmann::json cardsType:myCardsFile[neutral]["cards"])
                for(nlohmann::json card:cardsType)
                    Names.push_back(card["name"]);
            
            std::string cardClass(upper_to_lowercase(CARD_CLASS));
            //list class cards
            for(nlohmann::json cardsType:myCardsFile[cardClass]["cards"])
                for(nlohmann::json card:cardsType)
                    Names.push_back(card["name"]);
        
            keep_cards_by_name(cards,Names);
        }
		
		//writes the file with cards of CARD CLASS
		write_json(cards, "data/1_" + CARD_CLASS + ".json");

		//looks for hero dbfId
		rapidjson::Document collectibleCards = read_json("data/cards.collectible.json");
		int heroDbfId = 0;
		for (int c1 = 0; c1 < collectibleCards.Size(); ++c1)
		{
			if (CARD_CLASS.compare(collectibleCards[c1]["cardClass"].GetString()) == 0 &&
				HERO.compare(collectibleCards[c1]["type"].GetString()) == 0)
			{
				heroDbfId = collectibleCards[c1]["dbfId"].GetInt();
				break;
			}
		}

		//writes the general information file of this card class
		rapidjson::Document GeneralInformation;
		GeneralInformation.SetObject();
		GeneralInformation.AddMember("heroDbfId", heroDbfId, GeneralInformation.GetAllocator());
		GeneralInformation.AddMember("numberOfCards", 0, GeneralInformation.GetAllocator());
		GeneralInformation.AddMember("playedMatches", 0, GeneralInformation.GetAllocator());
		write_json(GeneralInformation, "data/" + CARD_CLASS + "_Info.json");
	}

	//It makes the list of tuples of this class
	else {
		//makes an object with the cards of CARD CLASS
		rapidjson::Document dataBase = read_json("data/1_" + CARD_CLASS + ".json");

		//makes the rapidjson object with tuples
		rapidjson::Document tuplesFile;
		tuplesFile.SetArray();
		std::vector<int> counters(TUPLE_NUMBER);
		fill_tuples_file_recursively(	tuplesFile,
										dataBase.Size(),
										get_first_legendary_index(dataBase),
										counters,
										0	);

		//writes the file with the tuples
		write_json(tuplesFile, "data/" + s_TUPLE_NUMBER + "_" + CARD_CLASS + ".json");
	}
	return 0;
}
