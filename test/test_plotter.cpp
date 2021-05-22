#include "../include/plotter.h"

int main(){
	Plotter plot;
	std::string filePath = "/mnt/sda_12/projects/algotrading/data/TATASTEEL.NS.csv";
	plot.fetchData(filePath);
	plot.genPlot();
	return 0;
}
