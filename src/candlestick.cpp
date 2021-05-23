#include "../include/candlestick.h"

Candlestick::Candlestick(const double &o, const double &h, const double &l,\
	const double &c, const sf::Font &font, const Pos &pos, const Pos &origin, const double &pixelScaleMultiplier){
	_open = o;
	_high = h;
	_low = l;
	_close = c;
	createBody(pos, origin, pixelScaleMultiplier);
	createWick(pos, origin, pixelScaleMultiplier);
}
Candlestick::~Candlestick(){}

void Candlestick::createBody(const Pos &pos, const Pos &origin, const double &pixelScaleMultiplier){
	_body.setPosition(pos.x, pos.y);
	double bodyHeight = pixelScaleMultiplier * abs(_open - _close);
	_body.setSize(sf::Vector2f(PARAMS::CANDLESTICK_BODY_WIDTH, bodyHeight));
	if(_open < _close)
		_body.setFillColor(sf::Color::Green);
	else
		_body.setFillColor(sf::Color::Red);
}
void Candlestick::createWick(const Pos &pos, const Pos &origin, const double &pixelScaleMultiplier){
	_wick.setPosition(pos.x, pos.y);
	double wickHeight = pixelScaleMultiplier * abs(_high - _low);
	_wick.setSize(sf::Vector2f(PARAMS::CANDLESTICK_WICK_WIDTH, wickHeight));
	if(_open < _close)
		_wick.setFillColor(sf::Color::Green);
	else
		_wick.setFillColor(sf::Color::Red);
}
void Candlestick::createText(){
}
