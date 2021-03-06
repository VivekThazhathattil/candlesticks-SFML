#include "../include/plotter.h"
#include <iostream>
double f(double in) { return 2 * in; }
int main() {
  Plotter plot;
  std::string filePath = "../data/OHLC.csv";
  plot.fetchData(filePath);
  plot.xAxisRange(0, 500);
  plot.yAxisRange(0, 500);
  plot.xLabel("Time");
  plot.yLabel("Units");
  plot.__title("Candlestick Chart");
  plot.candleSticks();
  plot.gridOn;
  return 0;
}
