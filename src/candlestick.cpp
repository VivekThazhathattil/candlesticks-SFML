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
	double bodyHeight = fmax(pixelScaleMultiplier * abs(_open - _close), 1);
	double openPos = fmin(pixelScaleMultiplier * abs(_high - _open), pixelScaleMultiplier * abs(_high - _close));
	_body.setPosition(pos.x, pos.y + openPos);
	_body.setSize(sf::Vector2f(PARAMS::CANDLESTICK_BODY_WIDTH, bodyHeight));
	if( bodyHeight == 1)
		_body.setFillColor(sf::Color(120,120,121));
	else{
		if(_open < _close)
			_body.setFillColor(sf::Color::Green);
		else
			_body.setFillColor(sf::Color::Red);
	}
}
void Candlestick::createWick(const Pos &pos, const Pos &origin, const double &pixelScaleMultiplier){
	_wick.setPosition(pos.x + PARAMS::CANDLESTICK_BODY_WIDTH/2 - PARAMS::CANDLESTICK_WICK_WIDTH/2 , pos.y);
	double wickHeight = fmax(pixelScaleMultiplier * abs(_high - _low), 1);
	_wick.setSize(sf::Vector2f(PARAMS::CANDLESTICK_WICK_WIDTH, wickHeight));
	_wick.setFillColor(sf::Color(120,120,121));
}
void Candlestick::createText(){
}
