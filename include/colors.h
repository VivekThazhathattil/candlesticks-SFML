#pragma once
struct ColorCode {
	unsigned R, G, B; 
  ColorCode() : R(0), G(0), B(0) {}
  ColorCode(unsigned valR, unsigned valG, unsigned valB): R(valR), G(valG), B(valB) {}
};

typedef struct ColorCode Color;
