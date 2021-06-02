#include "../include/dataHandler.h"

DataHandler::DataHandler() {}
DataHandler::~DataHandler() {}

void DataHandler::fetch(const std::string filePath,
                        std::vector<std::string> &xData,
                        std::vector<std::vector<double>> &yData) {
  xData.clear();
  yData.clear();

  std::ifstream pFile(filePath);
  if (!pFile.is_open()) {
    std::cerr << "Error opening the data file. Exiting...\n";
    exit(1);
  }

  std::string line;
  std::vector<std::string> v;
  unsigned lineCount = 0;

  while (getline(pFile, line)) {
    std::stringstream ss(line);
    v.clear();
    /* collect all substrings from a line into v */
    while (ss.good()) {
      std::string substr;
      getline(ss, substr, ',');
      v.push_back(substr);
    }
    /* convert the substrings of a line into double type and store it in yData
     */
    yData.push_back(std::vector<double>());
    bool isDouble =
        true; // whether std::stod (string to double) is valid for a substring

    for (unsigned i = 0; i < v.size(); ++i) {
      if (i != 0) { // i = 0 corresponds to xData and everything else is yData
        double val = 0.0;
        try {
          val = std::stod(v[i]);
        } catch (std::exception &e) {
          yData[lineCount].pop_back();
          std::cerr << "Invalid argument in std::stod encountered. Omitting..."
                    << std::endl;
          isDouble = false;
          break;
        }
        if (isDouble)
          yData[lineCount].push_back(val);
      } else { // i == 0 case i.e. xData case
        xData.push_back(v[i]);
      }
    }

    if (isDouble)
      ++lineCount;
    else {
      xData.pop_back();
      yData.pop_back();
    }
    // if (!yData[lineCount].empty())
    //	++lineCount;
    // else
    //	yData.pop_back();
  }

  if (yData.empty()) {
    std::cerr << "dataHandler.cpp: yData empty fetch error. Exiting...\n";
    exit(1);
  }
  //	else{
  //		for(unsigned i = 0; i < yData.size(); ++i){
  //			std::cout << i+1 << ")\t" << "size: " << yData[i].size() <<
  //"\t"; 			for(unsigned j = 0; j < yData[i].size(); ++j){ 				std::cout <<
  //yData[i][j] << " ";
  //			}
  //			std::cout << std::endl;
  //		}
  //		for(unsigned i = 0; i < xData.size(); ++i){
  //			std::cout << i+1 << ")\t";
  //			std::cout << xData[i] << std::endl;
  //		}
  //	}

  pFile.close();
}
