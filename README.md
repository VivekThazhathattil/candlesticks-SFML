# Candlestick Chart for Stock Trading

A C++ program for displaying historical stock data in a candlestick format. 

Dependency on SFML, a multimedia library.

<p float="left">
<img src="img/prog1.png" width="400" height="400"/>
<img src="img/prog2.png" width="400" height="400"/>
<img src="img/prog3.png" width="400" height="400"/>
<img src="img/prog4.png" width="400" height="400"/>
</p>

##### Current development branch: include-sfml-view

#### Keyboard shortcuts (press c to randomize)

| Key | Description                    |
|-----|--------------------------------|
| c   | randomize candle body colors   |
| b   | toggle between light/dark mode |
| +		|	Zoom in 											 |
| -		|	Zoom out 											 |
| UP	|	Move up 											 |
| DOWN|	Move down 										 |
| LEFT|	Move left										   |
|RIGHT|	Move right 										 |

### How to try it out (Instructions for Linux system):
* clone the repo: Run `git clone https://github.com/VivekThazhathattil/candlesticks-SFML` or download as zip and extract it.
* change directory: `cd candlesticks-SFML/test`
* Run the Makefile: `make` from within the `test` directory.
* Make sure that you have GNU C++ compiler and SFML libs installed within your system.
* Run the program using `./main`

### Ideas left to implement (aka TODO):
* ~~Custom kawaii colors + white bg~~
* user input html color codes for backgrounds, bullish candles and bearish candles
* ~~x-axis markings~~
* ~~zoomability~~  (scale time period)
* ~~horizontal mouse drag to change the time period (also with left/right arrow keys)~~ dynamic change in axes pending
* detect marubozus, dojis, and other typical single as well as multi-candle patterns.
* draw MACD, get VWAP
* indicate volume
* show help commands upon pressing h 
* refactor hardcoded dimensions
* ability to draw custom lines/ curves
* keyboard shortcut to reset all the changed plot behaviours
* convert to renko charts
* identify x coordinate marking format and convert into other compact notations
* specify the csv file as a terminal command
* ~~figure out the title of the graph from the file name. Override if custom name specified as command line argument.~~
* save user preferences in a local file and load that at startup.
* remove all the pixel scaling for candlesticks and replace it with sf::View functions : which makes it easy to implement zooming and scrolling, an resizing windows.
* implement box zoom functionality
* replace Pos with sfml equivalent to maintain consistency
