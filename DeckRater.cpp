#include "HearthstoneDeck.hpp"
#include "FunctionsToRate.hpp"
#include "RapidjsonUtils.hpp"

//sets which function will use to rate
#define f lp_without_root 

int main(int argc, char *argv[])
{
	//default parameters
	double p=2;

	//reads parameters
	if (argc < 3 || argc>4)
	{
		std::cout << "format: ./DeckRater TUPLE_NUMBER CARD_CLASS LP_NORM_EXPONENT" << std::endl;
		return 0;
	}
	//reads tuple number
	std::istringstream ss_TUPLE_NUMBER(argv[1]);
	int TUPLE_NUMBER;
	if (!(ss_TUPLE_NUMBER >> TUPLE_NUMBER))
	{
		std::cout << "Error with arguments" << std::endl;
		return 0;
	}
	//reads card class
	std::string CARD_CLASS(argv[2]);
	//reads exponent to lp norm
	if (argc > 3)
	{
		std::istringstream ss_p(argv[3]);
		if (!(ss_p >> p))
		{
			std::cout << "Error with arguments" << std::endl;
			return 0;
		}
	}

	rapidjson::Document Cards = read_json("data/1_"+CARD_CLASS+".json");
	rapidjson::Document GI = read_json("data/"+CARD_CLASS+"_Info.json");
	rapidjson::Document Tuples = read_json("data/"+std::to_string(TUPLE_NUMBER)+"_"+CARD_CLASS+".json");
	int heroDbfId = GI["heroDbfId"].GetInt();
	std::string code;
	while (true)
	{
		std::cout << "Please insert a valid code of your class ('exit' to finish): " << std::endl;
		std::cin >> code;
		if (code == "exit")break;
		Deck D(Cards, code);
		if (D.has_error())
		{
			std::cout << D.get_error_message() << std::endl;
			continue;
		}
		D.print(Cards, heroDbfId);

		D.set_value(f(D, Tuples, TUPLE_NUMBER, p));
		std::cout << "Value: " << D.get_value() << std::endl;
	} 
	return 0;
}
