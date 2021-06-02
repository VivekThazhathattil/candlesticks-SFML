#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class DataHandler {
public:
  DataHandler();
  ~DataHandler();
  void fetch(const std::string filePath, std::vector<std::string> &xData,
             std::vector<std::vector<double>> &yData);
};
