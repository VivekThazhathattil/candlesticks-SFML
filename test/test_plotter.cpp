#include "plotter.h"

int main() {
  Plotter plot(sf::Font{});
  std::string filePath = "data/TATASTEEL.NS.csv";
  plot.fetchData(filePath);
  plot.xLabel("");
  plot.yLabel("");
  plot.__title("");
  plot.candleSticks();
  return 0;
}
