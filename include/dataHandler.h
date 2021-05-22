#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

class DataHandler{
	public:
		DataHandler();
		~DataHandler();
		void fetch(const std::string filePath, 
				std::vector<std::string> &xData, 
				std::vector<std::vector <double>> &yData);
};
