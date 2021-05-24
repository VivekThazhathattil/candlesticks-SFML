#include <SFML/Graphics.hpp>
#include <vector>
#include "position.h"
#include "params.h"

class SRLevels{
	public:
		SRLevels(const double &d2pScale, const std::vector< std::vector<double >> &dat,\
				const Position &origin, const double &minDat);
		~SRLevels();

		std::vector<double> getSRLevels const () { return _levels; }
		std::vector<sf::RectangleShape> getSRLevelLines () const { return _levelLines; }

	private:
		std::vector<Pos> _levels;
		std::vector<sf::RectangleShape> _levelLines;

		void genLevels(const std::vector< std::vector< double >> &y);
		void genLevelLines(const double &d2p, const Position &orig, const double &yMin);
};
