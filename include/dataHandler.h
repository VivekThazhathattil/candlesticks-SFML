#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class DataHandler {
public:
  DataHandler();
  ~DataHandler();
  void fetch(const std::string filePath, std::vector<std::string> &xData,
             std::vector<std::vector<double>> &yData, std::string &title);

private:
	void getTitleFromFilePath(std::string &title, const std::string &filePath);
};
