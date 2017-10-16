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
				if (_cells[i][j].value == MOVABLE_CELL)
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
	if (checkIfMoveLeftPossible())
	{
		for (int i = 0; i < GAME_FIELD_HEIGHT; ++i)
		{
			for (int j = 0; j < GAME_FIELD_WIDTH; ++j)
			{
				if (_cells[i][j].value == MOVABLE_CELL)
				{
					_cells[i][j].value = EMPLTY_CELL;
					_cells[i][j - 1].value = MOVABLE_CELL;
				}
			}
		}
	}
}

void Game::shapeToRight()
{
	if (checkifMoveRightPossible())
	{
		for (int i = 0; i < GAME_FIELD_HEIGHT; ++i)
		{
			for (int j = GAME_FIELD_WIDTH - 1; j >= 0; --j)
			{
				if (_cells[i][j].value == MOVABLE_CELL)
				{
					_cells[i][j].value = EMPLTY_CELL;
					_cells[i][j + 1].value = MOVABLE_CELL;
				}
			}
		}
	}
}

void Game::draw()
{
	_display.clrScr();
  
	_display.drawRect(SCREEN_TOP_OFFSET, SCREEN_RIGHT_OFFSET - 1, 126, 63);

	for (int i = 0; i < GAME_FIELD_HEIGHT; ++i)
	{
		for (int j = 0; j < GAME_FIELD_WIDTH; ++j)
		{
			if (_cells[i][j].value != EMPLTY_CELL)
			{
				int x = i * RECT_SIZE + SCREEN_TOP_OFFSET;
				int y = j * RECT_SIZE + SCREEN_RIGHT_OFFSET;

				_display.drawRect(x, y, x + RECT_SIZE, y + RECT_SIZE);
				_display.setPixel(x + 2, y + 2);
				_display.setPixel(x + 2, y + 3);
				_display.setPixel(x + 3, y + 2);
				_display.setPixel(x + 3, y + 3);
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
			if (_cells[i][j].value == MOVABLE_CELL)
			{
				// still possible to move down
				if (i + 1 < GAME_FIELD_HEIGHT)
				{
					if (_cells[i + 1][j].value == STATIC_CELL)
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

bool Game::checkIfMoveLeftPossible()
{
	for (int i = 0; i < GAME_FIELD_HEIGHT; ++i)
	{
		for (int j = 0; j < GAME_FIELD_WIDTH; ++j)
		{
			if (_cells[i][j].value == MOVABLE_CELL)
			{
				// still possible to move left
				if (j > 0)
				{
					if (_cells[i][j - 1].value == STATIC_CELL)
					{
						return false;
					}
				}
				else
				{
					// impossible to move one more cell left
					return false;
				}
			}
		}
	}

	return true;
}

bool Game::checkifMoveRightPossible()
{
	for (int i = 0; i < GAME_FIELD_HEIGHT; ++i)
	{
		for (int j = GAME_FIELD_WIDTH - 1; j >= 0; --j)
		{
			if (_cells[i][j].value == MOVABLE_CELL)
			{
				// still possible to move right
				if (j + 1 < GAME_FIELD_WIDTH)
				{
					if (_cells[i][j + 1].value == STATIC_CELL)
					{
						return false;
					}
				}
				else
				{
					// impossible to move one more cell right
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
			if (_cells[i][j].value == MOVABLE_CELL)
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
