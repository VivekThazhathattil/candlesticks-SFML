#include "../include/plotter.h"

int main() {
  Plotter plot;
  std::string filePath = "/mnt/sda_12/projects/algotrading/data/TATASTEEL.NS.csv";
  plot.fetchData(filePath);
  plot.xLabel("");
  plot.yLabel("");
  plot.__title("");
  plot.candleSticks();
  return 0;
}
