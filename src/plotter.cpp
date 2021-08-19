#include "../include/plotter.h"
// TODO [DONE] : show x axis div labels
// TODO: get SR levels
// TODO: get  MACD
// TODO [DONE] : add keyboard shortcuts help, MACD view, SR view
// TODO: fetch data from yahoo finance directly given quote

Plotter::Plotter()
    : _window(sf::RenderWindow(
          sf::VideoMode(PARAMS::WINDOW_SIZE_X, PARAMS::WINDOW_SIZE_Y),
          "Candlestick Plot", sf::Style::Close)) {
  /* default values */
  _xLabel = "";
  _yLabel = "";
  _title = "";
  _axesThickness = 2;
  _xScaleFactor = 1;
  _yScaleFactor = 1;
  _xstep = 10;
  _ystep = 10;
  _ymax = -1;
  _ymin = -1;
  _pixelScaleMultiplier = -1;

  showSRLevels = false;
  showMACD = false;
	changeColor = false;

  if (!_font.loadFromFile("../res/arial.ttf")) {
    std::cerr << "Error loading font! Exiting...\n";
    exit(1);
  }
}

Plotter::~Plotter() {}

void Plotter::fetchData(const std::string filePath) {
  DataHandler dh;
  dh.fetch(filePath, _xData, _yData);
}

void Plotter::xAxisRange(const unsigned x_min, const unsigned x_max) {}

void Plotter::yAxisRange(const unsigned y_min, const unsigned y_max) {}

void Plotter::xLabel(const std::string xTitle) { _xLabel = xTitle; }

void Plotter::yLabel(const std::string yTitle) { _yLabel = yTitle; }

void Plotter::title(const std::string uTitle) { _title = uTitle; }

void Plotter::candleSticks() { genPlot("ohlc"); }

void Plotter::genPlot(const std::string param) {
  if (_xData.empty() || _yData.empty()) {
    std::cerr << "Input data missing! Exiting..." << std::endl;
    exit(1);
  }

  std::vector<sf::RectangleShape> axes = createAxes();
  std::vector<sf::RectangleShape> div = createDivisions(param);
  std::vector<sf::Text> labels = createLabels();
  sf::Text title = createTitle();
  std::vector<sf::RectangleShape> gridLines = createGridLines();

  if (param.compare("ohlc") == 0) {
    gatherAdditionalInfo(param);
    std::vector<sf::Text> yDivText = getYDivisionLabels();
    std::vector<Candlestick> candlesticks = getCandlesticks();
    display(gridLines, axes, yDivText, labels, title, div, candlesticks);
  }
}

std::vector<sf::Text> Plotter::getYDivisionLabels() const {
  std::vector<sf::Text> v;
  /* y div labels */
  for (unsigned i = 0; i < PARAMS::NUM_DIVS_Y + 1; ++i) {
    v.push_back(sf::Text());
    v.back().setFont(_font);
    v.back().setString(
        std::to_string(int(_ymin + i * (_ymax - _ymin) / PARAMS::NUM_DIVS_Y)));
    v.back().setFillColor(sf::Color(124, 128, 133));
    v.back().setCharacterSize(PARAMS::DIV_TEXT_SIZE_Y);
    v.back().setOrigin(sf::Vector2f(0, v.back().getLocalBounds().height +
                                           PARAMS::OFFSET_Y / 2));
    v.back().setPosition(sf::Vector2f(getOrigin().x + PARAMS::OFFSET_X / 2,
                                      getOrigin().y - i * _yScaleFactor));
  }
  /* x div labels */
  for (unsigned i = 0; i < PARAMS::NUM_DIVS_X + 1; ++i) {
    v.push_back(sf::Text());
    v.back().setFont(_font);
    float step = float(_xData.size()) / PARAMS::NUM_DIVS_X;
    std::string labelString =
        _xData[(int(i * step) >= _xData.size()) ? _xData.size() - 1
                                                : int(i * step)];
    std::cout << i * step << ")" << labelString << std::endl;
    v.back().setString(labelString);
    v.back().setFillColor(sf::Color(124, 128, 133));
    v.back().setCharacterSize(PARAMS::DIV_TEXT_SIZE_X);
    v.back().setOrigin(sf::Vector2f(v.back().getLocalBounds().width,
                                    v.back().getLocalBounds().height));
    v.back().setPosition(sf::Vector2f(getOrigin().x + i * _xScaleFactor,
                                      getOrigin().y + PARAMS::OFFSET_Y / 2));
    v.back().setRotation(-30.0);
  }
  return v;
}

std::vector<sf::RectangleShape> Plotter::createGridLines() const {
  std::vector<sf::RectangleShape> v;
  /* for horizontal lines */
  Pos origin = getOrigin();
  for (unsigned i = 0; i < PARAMS::NUM_DIVS_Y + 1; ++i) {
    v.push_back(sf::RectangleShape());
    v.back().setPosition(origin.x, origin.y - i * _yScaleFactor);
    v.back().setFillColor(sf::Color(30, 33, 42));
    v.back().setSize(sf::Vector2f(getAxesLength().x, 2));
  }

  for (unsigned i = 0; i < PARAMS::NUM_DIVS_X + 1; ++i) {
    v.push_back(sf::RectangleShape());
    v.back().setPosition(origin.x + i * _xScaleFactor, origin.y);
    v.back().setFillColor(sf::Color(30, 33, 42));
    v.back().setSize(sf::Vector2f(2, -getAxesLength().y));
  }
  return v;
}

void Plotter::gatherAdditionalInfo(const std::string &param) {
  if (param.compare("ohlc") == 0) {
    _ymax = getMaximumYData();
    _ymin = getMinimumYData();
    _pixelScaleMultiplier = getPixelSizeMultiplier();
  }
}

double Plotter::getMaximumYData() const {
  double max = -1;
  for (unsigned i = 0; i < _yData.size(); ++i) {
    if (_yData[i][1] > max)
      max = _yData[i][1];
  }
  return max;
}
double Plotter::getMinimumYData() const {
  double min = 1000000;
  for (unsigned i = 0; i < _yData.size(); ++i) {
    if (_yData[i][2] < min)
      min = _yData[i][2];
  }
  return min;
}

double Plotter::getPixelSizeMultiplier() {
  return getAxesLength().y / (_ymax - _ymin);
}

std::vector<Candlestick> Plotter::getCandlesticks() {
  assert(_xData.size() == _yData.size());
  std::vector<Candlestick> v;
  for (unsigned i = 0; i < _xData.size(); ++i) {
    double yPixelLoc =
        getOrigin().y -
        _pixelScaleMultiplier *
            (_yData[i][1] -
             _ymin); // data high passed bc bounding box origin is at top-left.
    v.push_back(Candlestick(
        _xData[i], _yData[i], _font,
        Pos(getOrigin().x + i * getAxesLength().x / _xData.size(), yPixelLoc),
        getOrigin(), _pixelScaleMultiplier,
        Pos(getOrigin().x + getAxesLength().x, getOrigin().y)));
  }
  return v;
}

Pos Plotter::getOrigin() const {
  return Pos(PARAMS::OFFSET_X + PARAMS::LABEL_SIZE_X + PARAMS::DIV_TEXT_SIZE_X,
             PARAMS::WINDOW_SIZE_Y - (PARAMS::OFFSET_Y + PARAMS::LABEL_SIZE_Y +
                                      PARAMS::DIV_TEXT_SIZE_Y));
}

AxesLength Plotter::getAxesLength() const {
  return AxesLength(
      PARAMS::WINDOW_SIZE_X - 2 * (PARAMS::OFFSET_X + PARAMS::LABEL_SIZE_X +
                                   PARAMS::DIV_TEXT_SIZE_X),
      PARAMS::WINDOW_SIZE_Y - 2 * (PARAMS::OFFSET_Y + PARAMS::LABEL_SIZE_Y +
                                   PARAMS::DIV_TEXT_SIZE_Y));
}

std::vector<sf::RectangleShape> Plotter::createAxes() {
  std::vector<sf::RectangleShape> v;

  /* for x axis */
  v.push_back(sf::RectangleShape());
  v.back().setPosition(sf::Vector2f(getOrigin().x, getOrigin().y));

  if (_axesThickness > 1)
    v.back().setOrigin(0, float(_axesThickness / 2));
  v.back().setSize(sf::Vector2f(getAxesLength().x, _axesThickness));

  /* for y axis */
  v.push_back(sf::RectangleShape());
  v.back().setPosition(sf::Vector2f(getOrigin().x, getOrigin().y));

  if (_axesThickness > 1)
    v.back().setOrigin(0, float(_axesThickness / 2));
  v.back().setSize(sf::Vector2f(getAxesLength().y, _axesThickness));
  v.back().setRotation(-90.0);

  return v;
}

std::vector<sf::RectangleShape>
Plotter::createDivisions(const std::string &param) {
  calculateScaleFactor(param);
  std::vector<sf::RectangleShape> v;
  /* x divisions */
  for (unsigned i = 0; i * _xScaleFactor < getAxesLength().x; ++i) {
    v.push_back(sf::RectangleShape());
    v.back().setSize(sf::Vector2f(PARAMS::DIV_SIZE_X, 1));
    v.back().setPosition(getOrigin().x + i * _xScaleFactor, getOrigin().y);
    v.back().setRotation(90.0);
  };
  /* y divisions */
  for (unsigned i = 0; i * _yScaleFactor < getAxesLength().y; ++i) {
    v.push_back(sf::RectangleShape());
    v.back().setSize(sf::Vector2f(PARAMS::DIV_SIZE_Y, 1));
    v.back().setPosition(getOrigin().x, getOrigin().y - i * _yScaleFactor);
    v.back().setRotation(180.0);
  };
  return v;
}

void Plotter::calculateScaleFactor(const std::string &param) {
  if (param.compare("ohlc") ==
      0) { // calculate scalefactor for candlesticks case
    _xScaleFactor =
        getAxesLength().x /
        PARAMS::NUM_DIVS_X; // fix the number of divisions on each axes to 10
    _yScaleFactor = getAxesLength().y / PARAMS::NUM_DIVS_Y;
  }
}

std::vector<sf::Text> Plotter::createLabels() {
  std::vector<sf::Text> v;

  /* xlabel */
  v.push_back(sf::Text(_xLabel, _font, PARAMS::LABEL_SIZE_X));
  v.back().setPosition(sf::Vector2f(getOrigin().x + getAxesLength().x / 2 -
                                        v.back().getLocalBounds().width / 2,
                                    getOrigin().y + PARAMS::OFFSET_Y));
  //	v.back().setOrigin( v.back().getGlobalBounds().width/2
  //,PARAMS::LABEL_SIZE_X/2);

  /* y label */
  v.push_back(sf::Text(_yLabel, _font, PARAMS::LABEL_SIZE_Y));
  v.back().setOrigin(v.back().getLocalBounds().width / 2,
                     v.back().getLocalBounds().height / 2);
  v.back().setPosition(sf::Vector2f(
      getOrigin().x - v.back().getLocalBounds().height / 2 - PARAMS::OFFSET_Y,
      getOrigin().y - getAxesLength().y / 2));
  //	v.back().setOrigin( v.back().getGlobalBounds().width/2
  //,PARAMS::LABEL_SIZE_Y/2);
  v.back().setRotation(-90.0);

  return v;
}

sf::Text Plotter::createTitle() {
  sf::Text t(_title, _font, PARAMS::TITLE_SIZE);
  t.setPosition(
      sf::Vector2f(PARAMS::WINDOW_SIZE_X / 2 - t.getLocalBounds().width / 2,
                   PARAMS::OFFSET_Y));
  return t;
}

void Plotter::changeColors(Candlestick &cs){
	const Color bullCol(100,20,30);
	const Color bearCol(200,100,20); 
	cs.changeColor(bullCol, bearCol);	
}
void Plotter::display(const std::vector<sf::RectangleShape> gridLines,
                      const std::vector<sf::RectangleShape> &axes,
                      const std::vector<sf::Text> yDivText,
                      const std::vector<sf::Text> &labels,
                      const sf::Text &title,
                      const std::vector<sf::RectangleShape> &div,
                      std::vector<Candlestick> &cs) {
  _window.setPosition(
      sf::Vector2i(int(sf::VideoMode::getDesktopMode().width / 2 -
                       PARAMS::WINDOW_SIZE_X / 2),
                   int(sf::VideoMode::getDesktopMode().height / 2 -
                       PARAMS::WINDOW_SIZE_Y / 2)));
  _window.setFramerateLimit(PARAMS::FRAME_LIMIT);

  while (_window.isOpen()) {
    sf::Event e;
    while (_window.pollEvent(e)) {
      if (e.type == sf::Event::Closed)
        _window.close();
      if (e.type == sf::Event::KeyPressed){
        if (e.key.code == sf::Keyboard::S) {
          /* show SR levels */
          showSRLevels = !showSRLevels;
        } else if (e.key.code == sf::Keyboard::M) {
          /* show MACD */
          showMACD = !showMACD;
        } else if (e.key.code == sf::Keyboard::C){
					changeColor = !changeColor;
				}
			}
    }
    _window.clear(sf::Color(12, 14, 16));
    for (unsigned i = 0; i < gridLines.size(); ++i) {
      _window.draw(gridLines[i]);
    }
    _window.draw(axes[0]);
    _window.draw(axes[1]);
    for (unsigned i = 0; i < div.size(); ++i)
      _window.draw(div[i]);
    for (unsigned i = 0; i < cs.size(); ++i) {
			if(changeColor)
				changeColors(cs[i]);
      _window.draw(cs[i].getWick());
      _window.draw(cs[i].getBody());
    }
		if(changeColor)
			changeColor = !changeColor;
    for (unsigned i = 0; i < cs.size(); ++i) {
      if (cs[i].mouseInCandleStick(Pos(sf::Mouse::getPosition(_window).x,
                                       sf::Mouse::getPosition(_window).y))) {
        _window.draw(cs[i].getText());
        break;
      }
    }

    for (unsigned i = 0; i < yDivText.size(); ++i) {
      _window.draw(yDivText[i]);
    }
//    if (showSR) {
//      /* show support and resistance levels */
//      SRLevels sr(_pixelScaleMultiplier, _yData, getOrigin(), _ymin);
//      std::vector<sf::Lines> v = getSRLevelLines();
//      for (unsigned i = 0; i < v.size(); ++i) {
//        _window.draw(v[i]);
//      }
//    }
    if (showMACD) {
      /* complete this */
    }
    _window.draw(labels[0]);
    _window.draw(labels[1]);
    _window.draw(title);
    _window.display();
  }
}
