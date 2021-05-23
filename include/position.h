#pragma once
struct Position{
	float x, y;
	Position() : x(0), y(0) {}
	Position(float valX, float valY) : x(valX), y(valY) {}
};

typedef struct Position Pos;
typedef struct Position AxesLength;
typedef struct Position Size;
