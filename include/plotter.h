#include "candlestick.h"
#include "colors.h"
#include "dataHandler.h"
#include "params.h"
#include "position.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cassert>
#include <ctime>
#include <iostream>
#include <string>

class Plotter {
public:
  Plotter();
  ~Plotter();
  void fetchData(const std::string filePath);
  void xAxisRange(const unsigned x_min, const unsigned x_max);
  void yAxisRange(const unsigned y_min, const unsigned y_max);
  void xLabel(const std::string xTitle);
  void yLabel(const std::string yTitle);
  void __title(const std::string uTitle);
  void genPlot(const std::string param);
  void candleSticks();

private:
  std::vector<std::string> _xData;
  std::vector<std::vector<double>> _yData;
  std::string _xLabel;
  std::string _yLabel;
  std::string _title;
  unsigned _axesThickness;
  bool _gridsOn;

  double _xScaleFactor; // num of pixels for one data point
  double _yScaleFactor;

  double _xstep;
  double _ystep;

  double _ymin;
  double _ymax;

	int _xBegIdx;
	int _xEndIdx;
	int _yBegIdx; // same as y_min
	int _yEndIdx; // same as y_max

  std::vector<sf::RectangleShape> axes;
  std::vector<sf::RectangleShape> div;
  std::vector<sf::Text> labels;
  sf::Text title;
  std::vector<sf::RectangleShape> gridLines;
	std::vector<sf::Text> yDivText; 
	std::vector<Candlestick> cs;

  Pos _origin;
  double _pixelScaleMultiplier;

  Color _wickColor;
  Color _bgColor;
  Color _textColor;
  Color _axesColor;
  Color _gridColor;

  bool showSRLevels;
  bool showMACD;
  bool changeColor;

  sf::RenderWindow _window;
	sf::View _view;
  sf::Font _font;

  void changeColors(Candlestick &cs, const Color bull, const Color bear);
  void lightModeSwitch();
  double getMaximumYData() const;
  double getMinimumYData() const;
  void gatherAdditionalInfo(const std::string &param);
  std::vector<sf::RectangleShape> createGridLines() const;
  std::vector<sf::Text> getYDivisionLabels() const;
  std::vector<sf::RectangleShape> createAxes();
  Pos getOrigin() const;
  AxesLength getAxesLength() const;
  std::vector<sf::RectangleShape> createDivisions(const std::string &param);
  void calculateScaleFactor(const std::string &param);
  std::vector<sf::Text> createLabels();
  sf::Text createTitle();
  std::vector<Candlestick> getCandlesticks();
  double getPixelSizeMultiplier();
  void display();
	void updateMinIdxs();
	Pos getCandlesticksViewportOriginInFractions() const;
	Pos getCandlesticksViewportSizeInFractions() const;
};
