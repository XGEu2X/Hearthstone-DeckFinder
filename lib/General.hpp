#pragma once

#include <vector>
#include <algorithm>
#include <sstream>
#include <utility>
#include <fstream>

#include "Card.hpp"
#include "Probability.hpp"
#ifdef __linux__ 
    #include "GeneralLinux.hpp"
#elif _WIN32
    #include "GeneralWindows.hpp"
#else

#endif

//downloads HearthstoneJson files
bool get_cards_files(const std::string& url, const std::string& excecutionPath = "");

inline int ctoi(char c) { return c - 48; }
inline bool is_number(char c){ return (c <= '9' && c >= '0'); }

//says if an element 'e' is in a list
template<class Element>
bool is_in(const Element& e, const std::vector<Element> List)
{
	for (Element e2 : List)
		if (e == e2)return true;
	return false;
}

//checks if a file or folder already exists
bool file_exists(const std::string& filename, const std::string& path = "");

//converts a string in upper case to a standar name, i.e. first letter in upper and the others in lower.
std::string upper_to_standar_names(const std::string& s);

//converts a uppercase string into lowercase string
std::string upper_to_lowercase(const std::string& s);

//Combinations
int Comb(int n, int k);
//Geometric mean
double geometric_mean(const std::vector<double>& X);
//binary exponentation
double binary_exponentiation(double x, int n);
//returns the index of a tuple in an ordered list of tuples with maximum value L-1
int mult_index(const int L, const std::vector<int>& Tuple);

//2-part recursive method. returns a list with all k-tuples indices (i.e. in order with L-1 its maximum value) with elements in a another list.
void get_tuples_indices_recursively(	const std::vector<int>& List,
										const int L,
										std::vector<int>& TuplesIndices,
										std::vector<int>& Counters,
										int level	);
std::vector<int> get_tuples_indices(const std::vector<int>& List, const int L, const int k);

//only keeps cards which belongs to Names list
bool keep_cards_by_name(std::vector<Card>& Cards, const std::vector<std::pair<std::string, int>>& AcquiredCards);

//remove cards without enough matches to be considered
template <class TuplesFile>
void remove_entries_without_enough_matches(TuplesFile& Tuples, int minMatchNumber)
{
	for (int c1 = 0; c1< Tuples.Size(); ++c1)
		if (Tuples[c1]["playedMatches"].GetInt() < minMatchNumber)
			Tuples.Erase(Tuples.Begin() + c1--);
}

//remove until N cards are left
template <class TuplesFile>
void remove_extra_cards(TuplesFile& Tuples, int maxNumCards)
{
	std::vector<int> values;
	for (int c1 = 0; c1 < Tuples.Size(); ++c1)
		values.push_back(Tuples[c1]["playedMatches"].GetInt());
	std::sort(values.begin(), values.end());
	if(0 < maxNumCards && maxNumCards <= Tuples.Size())
		remove_entries_without_enough_matches(Tuples, values[Tuples.Size() - maxNumCards]);
}

//calculate winRatio parameter in database
template <class TuplesFile>
void calculate_win_ratio(TuplesFile& Tuples) 
{
	for (int c1 = 0; c1 < Tuples.Size(); ++c1)
		if (Tuples[c1]["playedMatches"].GetInt()>0)
			Tuples[c1]["winRatio"].SetFloat(
				Tuples[c1]["wonMatches"].GetInt() / (double)(Tuples[c1]["playedMatches"].GetInt())
			);
}
