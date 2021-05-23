#include <SFML/Graphics.hpp>
#include "position.h"
#include "params.h"
#include <cmath>

class Candlestick{
	public:
		Candlestick(const double &o, const double &h, const double &l,\
				const double &c, const sf::Font &font, const Pos &pos,\
				const Pos &origin, const double &pixelScaleMultiplier);
		~Candlestick();

		sf::RectangleShape getBody() const { return _body; }
		sf::RectangleShape getWick() const { return _wick; }
	private:
		double _open;
		double _high;
		double _low;
		double _close;

		sf::Font _font;
		sf::Text _det;
		sf::RectangleShape _body;
		sf::RectangleShape _wick;
		
		void createBody(const Pos &pos, const Pos &origin, const double &pixelScaleMultiplier);
		void createWick(const Pos &pos, const Pos &origin, const double &pixelScaleMultiplier);
		void createText();

};
