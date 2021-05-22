#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "params.h"
#include "dataHandler.h"

class Plotter{
	public:
		Plotter();
		~Plotter();
		void fetchData(const std::string filePath);
		void xAxisRange(const unsigned x_min, const unsigned x_max);
		void yAxisRange(const unsigned y_min, const unsigned y_max);
		void xLabel(const std::string xTitle);
		void yLabel(const std::string yTitle);
		void title(const std::string uTitle);
		void genPlot();
		void candleSticks();
		
	private:
		std::vector<std::string> _xData;
		std::vector<std::vector<double>> _yData;
		std::string _xLabel;
		std::string _yLabel;
		std::string _title;
		unsigned _axesThickness;	
		bool _gridsOn;
		sf::RenderWindow _window;

		std::vector<sf::RectangleShape> createAxes();
//		std::vector<sf::RectangleShape> createDivisions();
//		std::vector<sf::Text> createLabels();
//		sf::Text createTitle();
		void display( const std::vector<sf::RectangleShape> &axes);
};
