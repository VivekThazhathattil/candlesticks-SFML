#include "colors.h"
#include "params.h"
#include "position.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <vector>

class Candlestick {
public:
  Candlestick(const std::string &x, const std::vector<double> &y,
              sf::Font &font, const Pos &pos, const Pos &origin,
              const double &pixelScaleMultiplier, const Pos &textPos);
  ~Candlestick();

  sf::RectangleShape getBody() const { return _body; }
  sf::RectangleShape getWick() const { return _wick; }
  sf::Text getText() const { return _det; }
  bool mouseInCandleStick(const Pos &pos) const;
  void changeColor(const Color bullColor, const Color bearColor);
	void changeDetColor(const Color color);

private:
  double _open;
  double _high;
  double _low;
  double _close;
  double _bodyHeight;
  std::string _x;

  sf::Text _det;
  sf::RectangleShape _body;
  sf::RectangleShape _wick;

  void createBody(const Pos &pos, const Pos &origin,
                  const double &pixelScaleMultiplier);
  void createWick(const Pos &pos, const Pos &origin,
                  const double &pixelScaleMultiplier);
  void createText(const Pos &pos);
};
