#include "../include/plotter.h"

int main(){
	Plotter plot;
	std::string filePath = "/mnt/sda_12/projects/algotrading/data/TATASTEEL.NS.csv";
	plot.fetchData(filePath);
	plot.xLabel("Test label x");
	plot.yLabel("Test label y");
	plot.title("Test Title");
	plot.genPlot();
	return 0;
}
