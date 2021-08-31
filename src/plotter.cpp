#include "../include/plotter.h"
#include <time.h>

Plotter::Plotter()
    : _window(sf::RenderWindow(
          sf::VideoMode(PARAMS::WINDOW_SIZE_X, PARAMS::WINDOW_SIZE_Y),
          "Candlestick Plot", sf::Style::Close)){
  /* default values */
  _xLabel = "";
  _yLabel = "";
  _title = "";
  _axesThickness = 2;
  _xScaleFactor = 1;
  _yScaleFactor = 1;
  _xstep = 10;
  _ystep = 10;
	_xBegIdx = 0;
	_xEndIdx = 0;
	_yBegIdx = 0;
	_yEndIdx = 0;
  _ymax = -1;
  _ymin = -1;
  _pixelScaleMultiplier = -1;

  _wickColor = DarkBG::wickColor;
  _bgColor = DarkBG::bgColor;
  _textColor = DarkBG::textColor;
  _axesColor = DarkBG::axesColor;
  _gridColor = DarkBG::gridColor;

	_mousePressedPos = sf::Vector2i(0,0);

  showSRLevels = false;
  showMACD = false;
  changeColor = false;
	mouseDrag = false;

  if (!_font.loadFromFile("../res/arial.ttf")) {
    std::cerr << "Error loading font! Exiting...\n";
    exit(1);
  }

	_view.reset(sf::FloatRect(0, 0, PARAMS::WINDOW_SIZE_X, PARAMS::WINDOW_SIZE_Y));
	_view.setViewport( sf::FloatRect( getCandlesticksViewportOriginInFractions().x, getCandlesticksViewportOriginInFractions().y, getCandlesticksViewportSizeInFractions().x, getCandlesticksViewportSizeInFractions().y) );
	//_view.reset(sf::FloatRect(0, 0, getAxesLength().x, getAxesLength().y));

  srand(time(0));
}

Plotter::~Plotter() {}

Pos Plotter::getCandlesticksViewportOriginInFractions() const{
	Pos pos;
	pos.x = (_window.getSize().x - getAxesLength().x) / ( 2 * _window.getSize().x );
	pos.y = (_window.getSize().y - getAxesLength().y) / ( 2 * _window.getSize().y );
	std::cout << pos.x << " " << pos.y << std::endl;
	return pos;
}

Pos Plotter::getCandlesticksViewportSizeInFractions() const{
	Pos pos;
	pos.x = getAxesLength().x / _window.getSize().x;
	pos.y = getAxesLength().y / _window.getSize().y;
	std::cout << pos.x << " " << pos.y << std::endl;
	return pos;
}

void Plotter::fetchData(const std::string filePath) {
  DataHandler dh;
  dh.fetch(filePath, _xData, _yData, _title);
}

void Plotter::xAxisRange(const unsigned x_min, const unsigned x_max) {}

void Plotter::yAxisRange(const unsigned y_min, const unsigned y_max) {}

void Plotter::xLabel(const std::string xTitle) { _xLabel = xTitle; }

void Plotter::yLabel(const std::string yTitle) { _yLabel = yTitle; }

void Plotter::__title(const std::string uTitle) { 
	if(uTitle.empty() && _title.length() < 2){
		_title = "CANDLESTICK CHART";
		return;
	}
	else if (!uTitle.empty()){
		_title = uTitle;
		return;
	}
}

void Plotter::candleSticks() { genPlot("ohlc"); }

void Plotter::genPlot(const std::string param) {
  if (_xData.empty() || _yData.empty()) {
    std::cerr << "Input data missing! Exiting..." << std::endl;
    exit(1);
  }

  if (param.compare("ohlc") == 0) {
		this->axes = createAxes();
		this->div = createDivisions(param);
		this->labels = createLabels();
		this->title = createTitle();
		this->gridLines = createGridLines();
		_xEndIdx = _xData.size() - 1;
    gatherAdditionalInfo(param);
    this->yDivText = getYDivisionLabels();
    this->cs = getCandlesticks();
		updateMinIdxs();
		display();
  }
}

void Plotter::updateMinIdxs(){
	_xBegIdx = (static_cast<int>(cs.size()) - static_cast<int>(PARAMS::MAX_CANDLES) > 0)\
						 ? static_cast<int>(cs.size()) - static_cast<int>(PARAMS::MAX_CANDLES) \
						 : 0;
	// [dve] temp values
	_xEndIdx = cs.size()-1;
	_yBegIdx = getMinimumYData();
	_yEndIdx = getMaximumYData();
}


std::vector<sf::Text> Plotter::getYDivisionLabels() const {
  std::vector<sf::Text> v;
  /* y div labels */
  for (unsigned i = 0; i < PARAMS::NUM_DIVS_Y + 1; ++i) {
    v.push_back(sf::Text());
    v.back().setFont(_font);
    v.back().setString(
        std::to_string(int(_ymin + i * (_ymax - _ymin) / PARAMS::NUM_DIVS_Y)));
    v.back().setFillColor(sf::Color(_textColor.R, _textColor.G, _textColor.B));
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
    v.back().setFillColor(sf::Color(_textColor.R, _textColor.G, _textColor.B));
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
    v.back().setFillColor(sf::Color(_gridColor.R, _gridColor.G, _gridColor.B));
    v.back().setSize(sf::Vector2f(getAxesLength().x, 2));
  }

  for (unsigned i = 0; i < PARAMS::NUM_DIVS_X + 1; ++i) {
    v.push_back(sf::RectangleShape());
    v.back().setPosition(origin.x + i * _xScaleFactor, origin.y);
    v.back().setFillColor(sf::Color(_gridColor.R, _gridColor.G, _gridColor.B));
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
  for (unsigned i = _xBegIdx; i <= _xEndIdx; ++i) {
    if (_yData[i][1] > max)
      max = _yData[i][1];
  }
  return max;
}
double Plotter::getMinimumYData() const {
  double min = 1000000;
  for (unsigned i = _xBegIdx; i <= _xEndIdx; ++i) {
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
  v.back().setFillColor(sf::Color(_axesColor.R, _axesColor.G, _axesColor.B));

  /* for y axis */
  v.push_back(sf::RectangleShape());
  v.back().setPosition(sf::Vector2f(getOrigin().x, getOrigin().y));

  if (_axesThickness > 1)
    v.back().setOrigin(0, float(_axesThickness / 2));
  v.back().setSize(sf::Vector2f(getAxesLength().y, _axesThickness));
  v.back().setFillColor(sf::Color(_axesColor.R, _axesColor.G, _axesColor.B));
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
		v.back().setFillColor(sf::Color(_axesColor.R, _axesColor.G, _axesColor.B));
  };
  /* y divisions */
  for (unsigned i = 0; i * _yScaleFactor < getAxesLength().y; ++i) {
    v.push_back(sf::RectangleShape());
    v.back().setSize(sf::Vector2f(PARAMS::DIV_SIZE_Y, 1));
    v.back().setPosition(getOrigin().x, getOrigin().y - i * _yScaleFactor);
    v.back().setRotation(180.0);
		v.back().setFillColor(sf::Color(_axesColor.R, _axesColor.G, _axesColor.B));
  };
  return v;
}

void Plotter::calculateScaleFactor(const std::string &param) {
  if (param.compare("ohlc") ==
      0) { // calculate scalefactor for candlesticks case
    _xScaleFactor =
        getAxesLength().x /
        PARAMS::NUM_DIVS_X; // fix the number of divisions on each axes to PARAMS::NUM_DIV_X and PARAMS::NUM_DIVS_Y respectively
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
	v.back().setFillColor(sf::Color(_textColor.R, _textColor.G, _textColor.B));
  //	v.back().setOrigin( v.back().getGlobalBounds().width/2
  //,PARAMS::LABEL_SIZE_X/2);

  /* y label */
  v.push_back(sf::Text(_yLabel, _font, PARAMS::LABEL_SIZE_Y));
  v.back().setOrigin(v.back().getLocalBounds().width / 2,
                     v.back().getLocalBounds().height / 2);
  v.back().setPosition(sf::Vector2f(
      getOrigin().x - v.back().getLocalBounds().height / 2 - PARAMS::OFFSET_Y,
      getOrigin().y - getAxesLength().y / 2));
	v.back().setFillColor(sf::Color(_textColor.R, _textColor.G, _textColor.B));
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
  t.setFillColor(sf::Color(_textColor.R, _textColor.G, _textColor.B));
  return t;
}

void Plotter::changeColors(Candlestick &cs, const Color bull,
                           const Color bear) {
  cs.changeColor(bull, bear);
}
void Plotter::lightModeSwitch(){
  // find out current mode
  if (_bgColor.R == LightBG::bgColor.R && _bgColor.G == LightBG::bgColor.G &&
      _bgColor.B ==
          LightBG::bgColor.B) { // currently in light mode. Switch to dark mode.
    _wickColor = DarkBG::wickColor;
    _bgColor = DarkBG::bgColor;
    _textColor = DarkBG::textColor;
    _axesColor = DarkBG::axesColor;
    _gridColor = DarkBG::gridColor;
  } else { // currently in dark mode. Switch to light mode.
    _wickColor = LightBG::wickColor;
    _bgColor = LightBG::bgColor;
    _textColor = LightBG::textColor;
    _axesColor = LightBG::axesColor;
    _gridColor = LightBG::gridColor;
  }

  for (unsigned i = 0; i < gridLines.size(); ++i)
    gridLines[i].setFillColor(
        sf::Color(_gridColor.R, _gridColor.G, _gridColor.B));
  for (unsigned i = 0; i < axes.size(); ++i)
    axes[i].setFillColor(sf::Color(_axesColor.R, _axesColor.G, _axesColor.B));
  for (unsigned i = 0; i < yDivText.size(); ++i)
    yDivText[i].setFillColor(
        sf::Color(_textColor.R, _textColor.G, _textColor.B));
  for (unsigned i = 0; i < cs.size(); ++i)
		cs[i].changeDetColor(_textColor);
  for (unsigned i = 0; i < div.size(); ++i)
    div[i].setFillColor(
        sf::Color(_axesColor.R, _axesColor.G, _axesColor.B));

}
void Plotter::display(){
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
      if (e.type == sf::Event::KeyPressed) {
				switch(e.key.code){
					case(sf::Keyboard::S):
          	showSRLevels = !showSRLevels;
						break;
					case(sf::Keyboard::M):
          	showMACD = !showMACD;
						break;
					case(sf::Keyboard::C):
          	changeColor = !changeColor;
						break;
					case(sf::Keyboard::B):
          	lightModeSwitch();
						break;
					case(sf::Keyboard::Add):
						_view.zoom(0.9f);
						break;
					case(sf::Keyboard::Subtract):
						_view.zoom(1.1f);
						break;
					case(sf::Keyboard::Left):
						_view.move(-10.0f, 0);
						break;
					case(sf::Keyboard::Right):
						_view.move(10.0f, 0);
						break;
					case(sf::Keyboard::Up):
						_view.move(0, 10.0f);
						break;
					case(sf::Keyboard::Down):
						_view.move(0, -10.0f);
						break;
				}
      }
			if (e.type == sf::Event::MouseWheelScrolled){
				int scrollCount = e.mouseWheelScroll.delta;
					_view.zoom(1.0f + scrollCount * 0.1f);
			}
			if (e.type == sf::Event::MouseButtonPressed)
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					mouseDrag = true;
					_mousePressedPos = sf::Mouse::getPosition();
				}
			if (e.type == sf::Event::MouseButtonReleased){
					mouseDrag = false;
					_mousePressedPos = sf::Vector2i(0,0);
				}
    }
    _window.clear(sf::Color(_bgColor.R, _bgColor.G, _bgColor.B));
    for (unsigned i = 0; i < gridLines.size(); ++i) {
      _window.draw(gridLines[i]);
    }
    _window.draw(axes[0]);
    _window.draw(axes[1]);
    for (unsigned i = 0; i < div.size(); ++i)
      _window.draw(div[i]);

    //-----------------------------------------
    // TODO: handle the change color in a separate function
    const Color bull = bullColors[rand() % bullColors.size()];
    const Color bear = bearColors[rand() % bearColors.size()];

		_window.setView(_view);
    for (unsigned i = _xBegIdx; i < _xEndIdx; ++i) {
      if (changeColor) {
        changeColors(cs[i], bull, bear);
      }
      _window.draw(cs[i].getWick());
      _window.draw(cs[i].getBody());
    }
		if(mouseDrag){
			sf::Vector2i newMousePos = sf::Mouse::getPosition();
			sf::Vector2i mouseDelta = _mousePressedPos - newMousePos;
			_view.move(mouseDelta.x, mouseDelta.y);
			_mousePressedPos = newMousePos;
		}
		_window.setView(_window.getDefaultView());
    if (changeColor)
      changeColor = !changeColor;
    //-----------------------------------------
    for (unsigned i = _xBegIdx; i <= _xEndIdx; ++i) {
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
