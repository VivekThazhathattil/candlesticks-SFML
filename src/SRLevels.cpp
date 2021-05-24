#include "../include/SRLevels.h"

SRLevels::SRLevels(const double &d2pScale, const std::vector< std::vector<double >> &dat,\
			const Position &origin, const double &minDat){
	genLevels(dat);
	genLevelLines(d2pScale, origin, minDat);
}

SRLevels::~SRLevels() {}

void SRLevels::genLevels(const std::vector< std::vector< double >> &y){
	
}

void SRLevels::genLevelLines(const double &d2p, const Position &orig, const double &yMin){
	for(unsigned i = 0; i < _levels.size(); ++i){
		v.push_back(sf::RectangleShape());
		v.back().setSize( 100, 2); // change later
		v.back().setPosition( orig.x + _levels[i].x * d2p ,\
				orig.y + (_levels[i].y - yMin ) * d2p);
		v.back().setFillColor(sf::Color::Blue);
	}
}
