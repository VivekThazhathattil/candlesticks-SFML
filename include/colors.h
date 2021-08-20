#pragma once
#include <vector>
struct ColorCode {
	unsigned R, G, B; 
  ColorCode() : R(0), G(0), B(0) {}
  ColorCode(unsigned val) : R(val), G(val), B(val) {}
  ColorCode(unsigned valR, unsigned valG, unsigned valB): R(valR), G(valG), B(valB) {}
};

typedef struct ColorCode Color;

const std::vector<Color> bullColors = {\
	Color(124,252,0),\
	Color(50,205,50),\
	Color(0,255,0),\
	Color(34,139,34),\
	Color(0,100,0),\
	Color(173,255,47),\
	Color(0,255,127),\
	Color(144,238,144),\
	Color(60,179,113),\
	Color(46,139,87),\
	Color(107,142,35)\
};
const std::vector<Color> bearColors =  {\
	Color(255,160,122),\
	Color(250,128,114),\
	Color(205,92,92),\
	Color(220,20,60),\
	Color(178,34,34),\
	Color(255,0,0),\
	Color(139,0,0),\
	Color(255,99,71),\
	Color(255,69,0),\
	Color(219,112,147)\
};

namespace LightBG{
	const Color wickColor(120, 120, 121),\
		bgColor(255),\
		textColor(105),\
		titleColor,\
		axesColor,\
		gridColor(173,216,230);
}

namespace DarkBG{
	const Color wickColor(120, 120, 121),\
		bgColor(12, 14, 16),\
		textColor(124, 128, 133),\
		titleColor(255),\
		axesColor(255),\
		gridColor(30, 33, 42);
}
