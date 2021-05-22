#include "../include/plotter.h"

Plotter::Plotter() : _window(sf::RenderWindow(sf::VideoMode(PARAMS::WINDOW_SIZE_X,\
				PARAMS::WINDOW_SIZE_Y), "plot", sf::Style::Close)) {
	/* default values */
	_xLabel = "";
	_yLabel = "";
	_title = "";
	_axesThickness = 2;

	if(!_font.loadFromFile("../res/arial.ttf")){
		std::cerr << "Error loading font! Exiting...\n";
		exit(1);
	}
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

void Plotter::title(const std::string uTitle){
	_title = uTitle;
}

void Plotter::candleSticks(){
	genPlot();
}

void Plotter::genPlot(){
	std::vector<sf::RectangleShape> axes = createAxes();
//	createDivisions();
	std::vector<sf::Text> labels = createLabels();
	sf::Text title = createTitle();
	display(axes, labels, title);
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
	v.back().setSize(sf::Vector2f(axesLengthY, _axesThickness));
	v.back().setRotation(-90.0);

	return v;
}

std::vector<sf::Text> Plotter::createLabels(){
	std::vector<sf::Text> v;

	/* xlabel */
	v.push_back(sf::Text( _xLabel, _font, PARAMS::LABEL_SIZE_X));
	v.back().setPosition(sf::Vector2f(PARAMS::WINDOW_SIZE_X/2, PARAMS::WINDOW_SIZE_Y - PARAMS::OFFSET_Y/2 - PARAMS::LABEL_SIZE_X));
//	v.back().setOrigin( v.back().getGlobalBounds().width/2 ,PARAMS::LABEL_SIZE_X/2);

	/* y label */
	v.push_back(sf::Text( _yLabel, _font, PARAMS::LABEL_SIZE_Y));
	v.back().setPosition(sf::Vector2f(PARAMS::OFFSET_X/2, PARAMS::WINDOW_SIZE_Y/2 - PARAMS::OFFSET_Y/2));
//	v.back().setOrigin( v.back().getGlobalBounds().width/2 ,PARAMS::LABEL_SIZE_Y/2);
	v.back().setRotation(-90.0);

	return v;
}

sf::Text Plotter::createTitle(){
	sf::Text t(_title, _font, PARAMS::TITLE_SIZE); 
	t.setPosition( sf::Vector2f(PARAMS::WINDOW_SIZE_X/2 - t.getLocalBounds().width/2, PARAMS::OFFSET_Y ) );
	return t;
}
void Plotter::display(const std::vector<sf::RectangleShape> &axes, const std::vector<sf::Text> &labels,\
		const sf::Text &title){
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
		_window.draw(labels[0]);
		_window.draw(labels[1]);
		_window.draw(title);
		_window.display();
	}
}
