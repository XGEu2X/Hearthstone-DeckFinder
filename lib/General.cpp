#include "General.hpp"

std::string upper_to_standar_names(const std::string s)
{
	std::string name(s);
	for (int c1 = 1; c1<s.size(); ++c1)
		name[c1] = s[c1] + 32;
	return name;
}

int Comb(int n, int k)
{
	if (k>n || n < 0 || k<0)return 0;
	int top = n, down = 1;
	for (int c1 = 1; c1<k; ++c1) {
		top *= (n - c1);
		down *= (c1 + 1);
	}
	return (top / down);
}
double geometric_mean(const std::vector<double>& X) 
{
	double GM = 1;
	for (int c1 = 0; c1<X.size(); ++c1)
		GM *= X[c1];
	GM = pow( GM , 1.0 / X.size() );
	return GM;
}
double binary_exponentiation(double x, int n) 
{
	double result;
	if (n == 0)result = 1;
	else if (n == 1)result = x;
	else if (n % 2 == 0) {
		double r = binary_exponentiation(x, n / 2);
		result = r * r;
	}
	else
	{
		result = binary_exponentiation(x, n / 2) * binary_exponentiation(x, (n + 1) / 2);
	}
	return result;
}
int mult_index(const int L, const std::vector<int>& Tuple)
{
	int index = 0, k = Tuple.size();
	if (k == 1)index = Tuple[0];
	else {
		index += Comb(L - 1 + k, k) - Comb(L - 1 + k - Tuple[0], k);
		std::vector<int> NewTuple(Tuple.size() - 1);
		for (int c1 = 1; c1<Tuple.size(); ++c1)
			NewTuple[c1 - 1] = Tuple[c1] - Tuple[0];
		index += mult_index(L - Tuple[0], NewTuple);
	}
	return index;
}

void get_tuples_indices_recursively(
	const std::vector<int>& List,
	const int L,
	std::vector<int>& TuplesIndices,
	std::vector<int>& Counters,
	int level	)
{
	//sets Counters
	if (level == 0)Counters[level] = 0;
	else    Counters[level] = Counters[level - 1] + 1;

	//fills TuplesIndices recursively
	while ( Counters[level] < List.size() - Counters.size() + 1 + level )
	{
		//recursive step
		if ( level < Counters.size() - 1 )
			get_tuples_indices_recursively(List, L, TuplesIndices, Counters, level + 1);
		else 
		{
			std::vector<int> Tuple(Counters.size());
			for (int c1 = 0; c1<Tuple.size(); ++c1)
				Tuple[c1] = List[Counters[c1]];
			TuplesIndices.push_back(mult_index(L, Tuple));
		}
		++Counters[level];
	}
}
std::vector<int> get_tuples_indices(const std::vector<int>& List, const int L, const int k)
{
	std::vector<int> TuplesIndices;
	TuplesIndices.reserve(Comb(List.size(), k));

	//faster than recursivity
	if (k == 1) 
	{
		for (int c1 = 0; c1<List.size(); ++c1)
			TuplesIndices.push_back(List[c1]);
	}
	else {
		std::vector<int> Counters(k);
		get_tuples_indices_recursively(List, L, TuplesIndices, Counters, 0);
	}
	return TuplesIndices;
}
