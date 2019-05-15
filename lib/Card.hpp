#pragma once

#include <iostream>

//const string names
const std::string	NEUTRAL("NEUTRAL"),
LEGENDARY("LEGENDARY"),
HERO("HERO"),
FREE("FREE");

class Card {
public:
	//Constructors
	Card(const std::string& id,
		const int dbfId,
		const std::string& name,
		const std::string& cardClass,
		const std::string& set,
		const std::string& rarity,
		int playedMatches = 0,
		int wonMatches = 0,
		double winRatio = 0,
		int quantity = 2
	);
	//Methods
	inline std::string get_id()const { return id; }
	inline int get_dbfId()const { return dbfId; }
	inline std::string get_name()const { return name; }
	inline std::string get_cardClass()const { return cardClass; }
	inline std::string get_set()const { return set; }
	inline std::string get_rarity()const { return rarity; }
	inline int get_playedMatches()const { return playedMatches; }
	inline int get_wonMatches()const { return wonMatches; }
	inline double get_winRatio()const { return winRatio; }
	inline int get_quantity()const { return quantity; }
	inline void set_quantity(int q) { quantity = q; }
private:
	//Variables
	std::string id;
	int dbfId;
	std::string name;
	std::string cardClass;
	std::string set;
	std::string rarity;
	int playedMatches;
	int wonMatches;
	double winRatio;
	int quantity;
};
