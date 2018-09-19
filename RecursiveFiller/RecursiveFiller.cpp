#include "RecursiveFiller.h"

int main(int argc, char *argv[]) {
	//default parameters
	// minimum ratio of matches to be considered (for cards) 
	double MIN_MATCH_VALID_RATIO = .02;

	//reads parameters
	//checks the number of parameters
	if (argc<3 || argc>4) {
		std::cout << "format: ./RecursiveFiller TUPLE_NUMBER CARD_CLASS MIN_MATCH_VALID_RATIO" << std::endl;
		return 0;
	}
	//reads TUPLE NUMBER
	std::string s_TUPLE_NUMBER(argv[1]);
	std::istringstream ss_TUPLE_NUMBER(argv[1]);
	int TUPLE_NUMBER;
	if (!(ss_TUPLE_NUMBER >> TUPLE_NUMBER)) {
		std::cout << "Error with arguments" << std::endl;
		return 0;
	}
	if(TUPLE_NUMBER < 2){
        std::cout << "Error with arguments" << std::endl;
		return 0;
    }
	//reads CARD CLASS
	std::string CARD_CLASS(argv[2]);
	std::string CARD_CLASS_MIN = upper_to_standar_names(CARD_CLASS);
	//reads MIN MATCH VALID RATIO
	if (argc>3) {
		std::istringstream s_MIN_MATCH_VALID_RATIO(argv[3]);
		if (!(s_MIN_MATCH_VALID_RATIO >> MIN_MATCH_VALID_RATIO)) {
			std::cout << "Error with arguments" << std::endl;
			return 0;
		}
	}
	//checks if the parameters are okay
	if (TUPLE_NUMBER<2)return 0;

	//makes the tuples file object
	rapidjson::Document tuplesFile = read_json("data/" + std::to_string(TUPLE_NUMBER) + "_" + CARD_CLASS + ".json");

	//makes the an object with the previous dimension tuples
	rapidjson::Document prevTuplesFile = read_json("data/" + std::to_string(TUPLE_NUMBER - 1) + "_" + CARD_CLASS + ".json");

	//makes an object with general information about this class
	rapidjson::Document GeneralClassInformation = read_json("data/" + CARD_CLASS + "_Info.json");

	//minimum number of matches that would have a tuple to not need a win ratio replace
	int minMatchValidNumber = GeneralClassInformation["playedMatches"].GetInt()*MIN_MATCH_VALID_RATIO;

	//walks trought  the tuples to repalce its win ratio if it not have enough played matches
	for (int c1 = 0; c1<tuplesFile.Size(); ++c1) {
		if (!tuplesFile[c1]["isValid"].GetInt())continue;

		if (tuplesFile[c1]["playedMatches"].GetInt()<minMatchValidNumber) {
			//makes a list with the values of the tuples in the previous dimension
			//makes a list with the indices of cards in this tuple, except the first one
			std::vector<int> Indices(TUPLE_NUMBER - 1);
			for (int c2 = 1; c2<TUPLE_NUMBER; ++c2)
				Indices[c2 - 1] = tuplesFile[c1]["Indices"][c2].GetInt();

			std::vector<double> previousValues(TUPLE_NUMBER);
			for (int c2 = 0; c2<TUPLE_NUMBER; ++c2) {
				int i = mult_index(TUPLE_NUMBER - 1, Indices);
				previousValues[c2] = prevTuplesFile[i]["winRatio"].GetDouble();

				//change the previous subset of values
				if (c2<TUPLE_NUMBER - 1)
					Indices[c2] = tuplesFile[c1]["Indices"][c2].GetInt();
			}

			//replace the win ratio
			tuplesFile[c1]["winRatio"].SetDouble(geometric_mean(previousValues));
		}
	}

	write_json(tuplesFile, "data/" + std::to_string(TUPLE_NUMBER) + "_" + CARD_CLASS + ".json");

	return 0;
}
