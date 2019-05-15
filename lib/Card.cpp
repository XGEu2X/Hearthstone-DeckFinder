#include "Card.hpp"

Card::Card(	const std::string& id,
			const int dbfId,
			const std::string& name,
			const std::string& cardClass,
			const std::string& set,
			const std::string& rarity,
			int playedMatches,
			int wonMatches,
			double winRatio,
			int quantity	)
{
	this->id = id;
	this->dbfId = dbfId;
	this->name = name;
	this->cardClass = cardClass;
	this->set = set;
	this->rarity = rarity;
	this->playedMatches = playedMatches;
	this->wonMatches = wonMatches;
	this->winRatio = winRatio;
	this->quantity = quantity;
}
