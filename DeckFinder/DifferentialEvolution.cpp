#include "DifferentialEvolution.h"

//sets which function will use to rate
#define f lp_without_root  

int main(int argc, char *argv[]) {

	//default parameters
	int NGen = 10000, NPop = 40, NRPop = 1,LimOfIterationsWithoutImprove=NGen;
	double p = 2, CMut = 0.2;

	//reads parameters
	if (argc<3 || argc>9) 
	{
		std::cout << "format: DifferentialEvolution.exe TUPLE_NUMBER CARD_CLASS GENERATIONS LIMIT_OF_ITERATIONS_WITHOUT_IMPROVMENT AMOUNT_OF_POPULATION PROBABILITY_OF_MUTATION RANDOM_ELEMENTS_IN_POPULATION EXPONENT_TO_LP_NORM" << std::endl;
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
	//reads number of iterations
	if (argc>3) 
	{
		std::istringstream ss_NGen(argv[3]);
		if (!(ss_NGen >> NGen)) {
			std::cout << "Error with arguments" << std::endl;
			return 0;
		}
	}
	//reads limit of valid iterations without improvment
	if (argc>4)
	{
		std::istringstream ss_LimOfIterationsWithoutImprove(argv[4]);
		if (!(ss_LimOfIterationsWithoutImprove >> LimOfIterationsWithoutImprove)) {
			std::cout << "Error with arguments" << std::endl;
			return 0;
		}
		if (LimOfIterationsWithoutImprove <= 0)LimOfIterationsWithoutImprove = NGen;
	}
	//reads number of elements in the population
	if (argc>5)
	{
		std::istringstream ss_NPop(argv[5]);
		if (!(ss_NPop >> NPop)) {
			std::cout << "Error with arguments" << std::endl;
			return 0;
		}
	}
	//reads probability of mutation
	if (argc>6)
	{	
		std::istringstream ss_CMut(argv[6]);
		if (!(ss_CMut >> CMut)) {
			std::cout << "Error with arguments" << std::endl;
			return 0;
		}
	}
	//reads the number of random elements in population
	if (argc>7)
	{
		std::istringstream ss_NRPop(argv[7]);
		if (!(ss_NRPop >> NRPop)) 
		{
			std::cout << "Error with arguments" << std::endl;
			return 0;
		}
		if (NRPop<0)NRPop = 0;
		if(NRPop>NPop)NRPop = NPop;
	}
	//reads exponent to lp norm
	if (argc>8) 
	{
		std::istringstream ss_p(argv[8]);
		if (!(ss_p >> p))
		{
			std::cout << "Error with arguments" << std::endl;
			return 0;
		}
	}

	//object with the list of cards of this class
	rapidjson::Document Cards = read_json("data/1_" + CARD_CLASS + ".json");

	//object with general info of class
	rapidjson::Document ClassInfo = read_json("data/"+CARD_CLASS+"_Info.json");

	//defines remaining parameters
	//dimension
	int D = Cards.Size();
	//l,h and firstLegendary 
	std::vector<int> l(D), h(D);
	int firstLegendary = -1;
	for (int c1 = 0; c1<D; ++c1) 
	{
		if (LEGENDARY.compare(Cards[c1]["rarity"].GetString()) == 0)
		{
			if (firstLegendary == -1)firstLegendary = c1;
			h[c1] = 1;
		}
		else    h[c1] = 2;
	}

	//object with tuples
	rapidjson::Document tuplesFile = read_json("data/" + std::to_string(TUPLE_NUMBER) + "_" + CARD_CLASS + ".json");

	//prepares the initial population
	std::vector<Deck> Population;
	Population.reserve(NPop);
	for (int c1 = 0; c1<NPop; ++c1)
	{
		Population.push_back(Deck(D, firstLegendary));
		Population[c1].set_value(f(Population[c1], tuplesFile, TUPLE_NUMBER, p));
	}

	//declares the value to limit iterations without improvment
	double maxValue = 0;
	int iterationsWithoutImprovment = 0;

	//iterates generations    
	int c1 = 0 ;
	for (c1 = 0; c1<NGen; ++c1) 
	{

		//iterates population
		for (int c2 = 0; c2<NPop; ++c2) 
		{
			//selects 3 random elements of population
			int iw, iy, iz;
			do 
			{
				iw = random_int(0, NPop);
			}while (iw == c2);
			do 
			{
				iy = random_int(0, NPop);
			}while (iy == c2 || iy == iw);
			do
			{
				iz = random_int(0, NPop);
			}while (iz == c2 || iz == iw || iz == iy);

			Deck x1 = Population[iz] + (Population[iy] + (-1)*Population[iw]);
			//x1.normalize(l, h);
			Deck x2 = mutate(x1, Population[c2], CMut);
			x2.normalize(l, h);

			x2.set_value(f(x2, tuplesFile, TUPLE_NUMBER, p));

			//replaces actual element with x2 if it has better rate
			if (x2 > Population[c2])Population[c2] = x2;
		}
		
		//sorts population by value (increasing)
		std::sort(Population.begin(), Population.end(), [](const Deck& d1, const Deck& d2) {
			return d2 > d1;
		});

		//replaces the worst rated elements with random elements
		for (int c2 = 0; c2<NRPop; ++c2) 
		{
			Population[c2] = Deck(D, firstLegendary);
			Population[c2].set_value(f(Population[c2], tuplesFile, TUPLE_NUMBER, p));
		}

		//checks if there was an improvment
		if ( maxValue < Population[NPop - 1].get_value() ) 
		{
			maxValue = Population[NPop - 1].get_value();
			iterationsWithoutImprovment = 0;
		}
		else 
		{
			++iterationsWithoutImprovment;
			if (iterationsWithoutImprovment == LimOfIterationsWithoutImprove)break;
		}	

		//How is it going?
		if (c1 % 100 == 99) {
			std::cout << "Generation " << c1 + 1;
			if (iterationsWithoutImprovment < 100)
				std::cout << ", value = " << maxValue << std::endl;
			else
				std::cout << std::endl;
		}

	}

	//show results
	std::cout << "P = " << p << ", " << TUPLE_NUMBER << "-tuples. Found in generation " << c1 - iterationsWithoutImprovment + 1 << std::endl;
	//show the best deck
	Population[NPop - 1].print(Cards,ClassInfo["heroDbfId"].GetInt());
	//show his rate
	std::cout << "Value: " << Population[NPop - 1].get_value() << std::endl;
	//show number of different cards in the best deck
	std::cout << "Number of different cards: " << Population[NPop - 1].get_number_of_cards() << std::endl;

	return 0;
}
