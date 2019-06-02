#include "CollectOBot.hpp"
#include "HSReplay.hpp"

int main(int argc, char *argv[]) 
{

	//default parameters
	// minimum ratio of matches to be considered (for cards) 
	double MIN_MATCH_VALID_RATIO = .02;
	int MAX_NUM_CARDS = 50;
	std::string STATS_RESOURCE("stats");

	//reads parameters
	//checks the number of parameters
	if (argc<3 || argc>4) 
	{
		std::cout << "format: ./MatchCollector TUPLE_NUMBER CARD_CLASS MIN_MATCH_VALID_RATIO or format: ./MatchCollector 1 CARD_CLASS MAX_NUM_CARDS" << std::endl;
		return 0;
	}
	//reads TUPLE NUMBER
	std::string s_TUPLE_NUMBER(argv[1]);
	std::istringstream ss_TUPLE_NUMBER(argv[1]);
	int TUPLE_NUMBER;
	if (!(ss_TUPLE_NUMBER >> TUPLE_NUMBER)) 
	{
		std::cout << "Error with arguments" << std::endl;
		return 0;
	}
	//reads CARD CLASS
	std::string CARD_CLASS(argv[2]);
	std::string CARD_CLASS_MIN = upper_to_standar_names(CARD_CLASS);
	//reads MIN MATCH VALID RATIO
	if (argc>3) 
	{
		std::istringstream s_MIN_MATCH_VALID_RATIO(argv[3]);
		if (!(s_MIN_MATCH_VALID_RATIO >> MIN_MATCH_VALID_RATIO)) 
		{
			std::cout << "Error with arguments" << std::endl;
			return 0;
			if (TUPLE_NUMBER == 1)
			{
				MAX_NUM_CARDS = int(MIN_MATCH_VALID_RATIO);
			}
		}
	}
	

	//makes the cards object with the CARD CLASS cards
	rapidjson::Document Cards = read_json("data/1_" + CARD_CLASS + ".json");

	//makes the object with name of tuples file
	std::string tuplesFileName("data/" + s_TUPLE_NUMBER + "_" + CARD_CLASS + ".json");

	//makes the tuples file object
	rapidjson::Document tuplesFile = read_json(tuplesFileName);

	//makes a list with the names of files which have matches
	std::vector<std::string> listOfMatches;
	read_directory("data/"+STATS_RESOURCE+"/", listOfMatches);
	//counts the number of added matches
	int numberOfAddedMatches = 0;

	//counts matches of each file
	for (std::string matchFileName : listOfMatches)
		if (matchFileName != "." && matchFileName != "..") 
		{
			ResultsFile RF(matchFileName);
			numberOfAddedMatches += add_counted_stats(RF,tuplesFile, CARD_CLASS, Cards, TUPLE_NUMBER);
		}

	//if it is counting matches of single cards, removes cards which not have enough matches and writes info of this class
	if (TUPLE_NUMBER == 1) 
	{
		remove_extra_cards(	tuplesFile, MAX_NUM_CARDS );
		
		rapidjson::Document GI = read_json("data/" + CARD_CLASS + "_Info.json");
		GI["playedMatches"].SetInt(GI["playedMatches"].GetInt() + numberOfAddedMatches);
		GI["numberOfCards"].SetInt(tuplesFile.Size());
		write_json(GI, "data/" + CARD_CLASS + "_Info.json");
	}

	calculate_win_ratio(tuplesFile);

	write_json(tuplesFile, tuplesFileName);

	return 0;
}
