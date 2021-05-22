#include "../include/plotter.h"

Plotter::Plotter() : _window(sf::RenderWindow(sf::VideoMode(PARAMS::WINDOW_SIZE_X,\
				PARAMS::WINDOW_SIZE_Y), "plot", sf::Style::Close)) {
	_xLabel = "";
	_yLabel = "";
	_title = "";
	_axesThickness = 2;
}

Plotter::~Plotter(){}

void Plotter::fetchData(const std::string filePath){
	DataHandler dh;
	dh.fetch(filePath, _xData, _yData);
}	

void Plotter::xAxisRange(const unsigned x_min, const unsigned x_max){
}

void Plotter::yAxisRange(const unsigned y_min, const unsigned y_max){
}	

void Plotter::xLabel(const std::string xTitle){
	_xLabel = xTitle;
}

void Plotter::yLabel(const std::string yTitle){
	_yLabel = yTitle;
}

void Plotter::candleSticks(){
	genPlot();
}

void Plotter::genPlot(){
	std::vector<sf::RectangleShape> axes = createAxes();
//	createDivisions();
//	createLabels();
//	createTitle();
	display(axes);
}

std::vector<sf::RectangleShape> Plotter::createAxes(){
	std::vector<sf::RectangleShape> v;

	unsigned totalXOffset = PARAMS::OFFSET_X + PARAMS::LABEL_SIZE_X + PARAMS::DIV_TEXT_SIZE_X;
	unsigned totalYOffset = PARAMS::OFFSET_Y + PARAMS::LABEL_SIZE_Y + PARAMS::DIV_TEXT_SIZE_Y;
	unsigned axesLengthX = PARAMS::WINDOW_SIZE_X - totalXOffset*2;
	unsigned axesLengthY = PARAMS::WINDOW_SIZE_Y - totalYOffset*2;

	/* for x axis */
	v.push_back(sf::RectangleShape());
	v.back().setPosition( sf::Vector2f( totalXOffset, PARAMS::WINDOW_SIZE_Y - totalYOffset));

	if ( _axesThickness > 1)
		v.back().setOrigin( 0, float(_axesThickness/2) );
	v.back().setSize(sf::Vector2f(axesLengthX, _axesThickness));

	/* for y axis */
	v.push_back(sf::RectangleShape());
	v.back().setPosition( sf::Vector2f( totalXOffset, PARAMS::WINDOW_SIZE_Y - totalYOffset));

	if ( _axesThickness > 1)
		v.back().setOrigin( 0, float(_axesThickness/2) );
	v.back().setSize(sf::Vector2f(axesLengthX, _axesThickness));
	v.back().setRotation(-90.0);

	return v;
}

void Plotter::display(const std::vector<sf::RectangleShape> &axes){
	_window.setPosition(
			sf::Vector2i(
				int( sf::VideoMode::getDesktopMode().width/2 - PARAMS::WINDOW_SIZE_X/2 ), 
				int( sf::VideoMode::getDesktopMode().height/2 - PARAMS::WINDOW_SIZE_Y/2 )
				)
			);

	while(_window.isOpen()){
		sf::Event e;
		while(_window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				_window.close();
		}
		_window.clear();
		_window.draw(axes[0]);
		_window.draw(axes[1]);
		_window.display();
	}
}
