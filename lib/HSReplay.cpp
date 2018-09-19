#include "HSReplay.hpp"

ResultsDeck::ResultsDeck(std::string cardClass_, int playedMatches_, int wonMatches_)
	:cardClass(cardClass_),
	playedMatches(playedMatches_),
	wonMatches(wonMatches_)
{
}
void ResultsDeck::print_names() 
{
	for (int c1 = 0; c1 < ListOfNames.size();++c1)
	{
		std::cout << ListOfNames[c1];
		std::cout << std::endl;
	}
}
void ResultsDeck::print_indices()
{
	for (int c1 = 0; c1 < ListOfIndices.size();++c1)
	{
		std::cout << ListOfIndices[c1];
		std::cout << std::endl;
	}
}
void ResultsDeck::print()
{
    std::cout << cardClass << std::endl;
	std::cout << playedMatches << std::endl << wonMatches << std::endl;
    print_names();
    print_indices();
}

ResultsFile::ResultsFile(const std::string& fileName) 
{
	std::string line;
	std::ifstream file(fileName);
	if (file.is_open()) 
	{	
		int c1 = 0;
		while (std::getline(file, line)) 
		{
			std::string cardClass(line);
			
			std::getline(file, line);
			int playedMatches = std::stoi(line);

			std::getline(file, line);
			int wonMatches = std::stoi(line);

			ListOfResultsDecks.push_back( ResultsDeck(cardClass,playedMatches,wonMatches) );
			while (std::getline(file, line)) 
			{
				if (line.length() == 0)break;
				ListOfResultsDecks[c1].add_id(line);
			}

			++c1;
		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open the results file" << std::endl;
	}
}
void ResultsFile::print() 
{
	for (int c1 = 0; c1 < ListOfResultsDecks.size(); ++c1)
		ListOfResultsDecks[c1].print();
}
