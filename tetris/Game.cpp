#include "Game.h"

Game::Game()
	: _display(SDA, SCL)
{
	for (int i = 0; i < GAME_FIELD_HEIGHT; ++i)
	{
		for (int j = 0; j < GAME_FIELD_WIDTH; ++j)
		{
			_cells[i][j].value = EMPLTY_CELL;
		}
	}

	generateShape();
}

void Game::setup()
{
  _display.begin();
}

void Game::update()
{
	if (checkIfMovePossible())
	{
		for (int i = GAME_FIELD_HEIGHT - 1; i >= 0; --i)
		{
			for (int j = GAME_FIELD_WIDTH - 1; j >= 0; --j)
			{
				if (abs(_cells[i][j].value) == abs(MOVABLE_CELL))
				{
					_cells[i][j].value = EMPLTY_CELL;
					_cells[i + 1][j].value = MOVABLE_CELL;
				}
			}
		}
	}
	else
	{
		movableToStatic();
		generateShape();
	}
}

void Game::shapeToLeft()
{

}

void Game::shapeToRight()
{

}

void Game::draw()
{
	_display.clrScr();
  
	_display.drawRect(SCREEN_TOP_OFFSET, SCREEN_RIGHT_OFFSET + 1, 127, 63);

	for (int i = 0; i < GAME_FIELD_HEIGHT; ++i)
	{
		for (int j = 0; j < GAME_FIELD_WIDTH; ++j)
		{
			if (abs(_cells[i][j].value) != abs(EMPLTY_CELL))
			{
				int x = i * RECT_SIZE + SCREEN_TOP_OFFSET;
				int y = j * RECT_SIZE + SCREEN_RIGHT_OFFSET;

				_display.drawRect(x, y, x + RECT_SIZE, y + RECT_SIZE);
				_display.setPixel(x + DOT_OFFSET, y + DOT_OFFSET);
			}
		}
	}

	_display.update();
}


#pragma region Private_methods

void Game::generateShape()
{
	_cells[0][4].value = MOVABLE_CELL;
	_cells[0][5].value = MOVABLE_CELL;
	_cells[1][4].value = MOVABLE_CELL;
	_cells[1][5].value = MOVABLE_CELL;
}

bool Game::checkIfMovePossible()
{
	for (int i = GAME_FIELD_HEIGHT - 1; i >= 0; --i)
	{
		for (int j = GAME_FIELD_WIDTH - 1; j >= 0; --j)
		{
			if (abs(_cells[i][j].value) == abs(MOVABLE_CELL))
			{
				// still possible to move down
				if (i + 1 <= GAME_FIELD_HEIGHT)
				{
					if (abs(_cells[i + 1][j].value) == abs(STATIC_CELL))
					{
						return false;
					}
				}
				else
				{
					// impossible to move one more cell down
					return false;
				}
			}
		}
	}

	return true;
}

void Game::movableToStatic()
{
	for (int i = 0; i < GAME_FIELD_HEIGHT; ++i)
	{
		for (int j = 0; j < GAME_FIELD_WIDTH; ++j)
		{
			if (abs(_cells[i][j].value) == abs(MOVABLE_CELL))
			{
				_cells[i][j].value = STATIC_CELL;
			}
		}
	}
}

void Game::printCell(int i, int j)
{
	Serial.print("[");
	Serial.print(i);
	Serial.print("]");
	Serial.print("[");
	Serial.print(j);
	Serial.print("]: ");
	Serial.println(_cells[i][j].value);
}



#pragma endregion
