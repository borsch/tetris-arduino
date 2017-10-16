#ifndef SHAPE_H
#define SHAPE_H

#include <OLED_I2C.h>

#define RECT_SIZE 5
#define DOT_OFFSET 2

#define GAME_FIELD_HEIGHT 20
#define GAME_FIELD_WIDTH 9
#define SCREEN_RIGHT_OFFSET 15
#define SCREEN_TOP_OFFSET 28

// cells that contains shape that are moving at this very momment
#define MOVABLE_CELL 2
// "floor" cells that not moving any more
#define STATIC_CELL 1
#define EMPLTY_CELL 0

typedef unsigned int uint;

struct Cell
{
	uint value : 2;
};

class Game
{
private:
	OLED _display;
	Cell _cells[GAME_FIELD_HEIGHT][GAME_FIELD_WIDTH];

	/*
		generate new shape
	*/
	void generateShape();

	/*
		check if current movable shape can move one more cell down/left/right
	*/
	bool checkIfMovePossible();
	bool checkIfMoveLeftPossible();
	bool checkifMoveRightPossible();

	/*
		conver all cell marked as movable to be a static cell
	*/
	void movableToStatic();

	void printCell(int i, int j);
public:
	Game();

	void setup();
  
	void shapeToLeft();
	void shapeToRight();

	void update();
	void draw();
};

#endif
