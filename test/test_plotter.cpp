#include "../include/plotter.h"

int main(){
	Plotter plot;
	std::string filePath = "/mnt/sda_12/projects/algotrading/data/GOOG.csv";
	plot.fetchData(filePath);
	plot.xLabel("");
	plot.yLabel("");
	plot.title("GOOG");
	plot.candleSticks();
	return 0;
}
