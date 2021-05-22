#include "../include/dataHandler.h"

int main(){
	DataHandler dh;
	std::vector<std::string> xData;
	std::vector< std::vector<double>> yData;
	dh.fetch("/mnt/sda_12/projects/algotrading/data/TATASTEEL.NS.csv", xData, yData);
	return 0;
}
