#pragma once

namespace PARAMS {
const float WINDOW_SIZE_X = 600;
const float WINDOW_SIZE_Y = 600;
const unsigned FRAME_LIMIT = 2;
const float OFFSET_X = 20; // away from the window borders
const float OFFSET_Y = 20; // away from the window borders
const unsigned LABEL_SIZE_X = 14;
const unsigned LABEL_SIZE_Y = 14;
const float TITLE_SIZE = 20;
const float DIV_SIZE_X = 5.0 * WINDOW_SIZE_X / 600;
const float DIV_SIZE_Y = 5.0 * WINDOW_SIZE_Y / 600;
const float NUM_DIVS_X = 5;
const float NUM_DIVS_Y = 5;
const unsigned DIV_TEXT_SIZE_X = 10;
const unsigned DIV_TEXT_SIZE_Y = 10;
const unsigned CANDLESTICK_FONT_SIZE = 8;
const float CANDLESTICK_BODY_WIDTH = WINDOW_SIZE_X / 100;
const float CANDLESTICK_WICK_WIDTH = WINDOW_SIZE_X / 600;
const unsigned MAX_CANDLES = 500;
} // namespace PARAMS

#define _MAX(a,b) ( a > b ? a : b )
