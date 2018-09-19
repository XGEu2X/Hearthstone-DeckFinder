#pragma once

#include "General.hpp"

//rates in base of k-tuples. Uses an lp norm over the k-tuples
template <class Deck,class TuplesFile>
double lp_without_root(const Deck& deck,const TuplesFile& tuplesFile,const int k,double p)
{
	double res=0;
	std::vector<int> List=deck.get_list_of_cards();
	std::vector<int> Indices=get_tuples_indices(List,deck.get_number_of_possible_cards(),k);
	for (int i : Indices)
		res += pow(tuplesFile[i]["winRatio"].GetDouble(),p);
	return res;
}
