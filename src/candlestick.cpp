#include "../include/candlestick.h"

Candlestick::Candlestick(const std::string &x, const std::vector<double> &y,
                         sf::Font &font, const Pos &pos, const Pos &origin,
                         const double &pixelScaleMultiplier,
                         const Pos &textPos) {
  _open = y[0];
  _high = y[1];
  _low = y[2];
  _close = y[3];
  _x = x;
  _det.setFont(font);

  createBody(pos, origin, pixelScaleMultiplier);
  createWick(pos, origin, pixelScaleMultiplier);
  createText(textPos);
}
Candlestick::~Candlestick() {}

void Candlestick::createBody(const Pos &pos, const Pos &origin,
                             const double &pixelScaleMultiplier) {
  _bodyHeight = fmax(pixelScaleMultiplier * abs(_open - _close), 1);
  double openPos = fmin(pixelScaleMultiplier * abs(_high - _open),
                        pixelScaleMultiplier * abs(_high - _close));
  _body.setPosition(pos.x, pos.y + openPos);
  _body.setSize(sf::Vector2f(PARAMS::CANDLESTICK_BODY_WIDTH, _bodyHeight));
  if (_bodyHeight == 1)
    _body.setFillColor(sf::Color(DarkBG::wickColor.R, DarkBG::wickColor.G,
                                 DarkBG::wickColor.B));
  else {
    if (_open < _close)
      _body.setFillColor(sf::Color::Green);
    else
      _body.setFillColor(sf::Color::Red);
  }
}
void Candlestick::createWick(const Pos &pos, const Pos &origin,
                             const double &pixelScaleMultiplier) {
  _wick.setPosition(pos.x + PARAMS::CANDLESTICK_BODY_WIDTH / 2 -
                        PARAMS::CANDLESTICK_WICK_WIDTH / 2,
                    pos.y);
  double wickHeight = fmax(pixelScaleMultiplier * abs(_high - _low), 1);
  _wick.setSize(sf::Vector2f(PARAMS::CANDLESTICK_WICK_WIDTH, wickHeight));
  _wick.setFillColor(
      sf::Color(DarkBG::wickColor.R, DarkBG::wickColor.G, DarkBG::wickColor.B));
}
void Candlestick::createText(const Pos &pos) {
  _det.setCharacterSize(PARAMS::LABEL_SIZE_X);
  _det.setStyle(sf::Text::Bold);
  _det.setString(_x + "\n" + "O: " + std::to_string(int(_open)) +
                 "\nH: " + std::to_string(int(_high)) +
                 "\nL: " + std::to_string(int(_low)) +
                 "\nC: " + std::to_string(int(_close)));
  _det.setPosition(
      sf::Vector2f(pos.x - _det.getLocalBounds().width - PARAMS::OFFSET_X,
                   pos.y - _det.getLocalBounds().height - PARAMS::OFFSET_Y));
	_det.setFillColor(sf::Color(DarkBG::textColor.R, DarkBG::textColor.G, DarkBG::textColor.B));
}
bool Candlestick::mouseInCandleStick(const Pos &pos) const {
  return (_wick.getGlobalBounds().contains(sf::Vector2f(pos.x, pos.y)) ||
          _body.getGlobalBounds().contains(sf::Vector2f(pos.x, pos.y)));
}

void Candlestick::changeColor(const Color bullColor, const Color bearColor) {
  if (_bodyHeight == 1)
    _body.setFillColor(sf::Color(DarkBG::wickColor.R, DarkBG::wickColor.G,
                                 DarkBG::wickColor.B));
  else {
    if (_open < _close)
      _body.setFillColor(sf::Color(bullColor.R, bullColor.G, bullColor.B));
    else
      _body.setFillColor(sf::Color(bearColor.R, bearColor.G, bearColor.B));
  }
}
void Candlestick::changeDetColor(const Color color){
	_det.setFillColor(sf::Color(color.R, color.G, color.B));
}
