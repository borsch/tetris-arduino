#include "Shape.h"

#define RECT_SIZE 5
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 128

Rect::Rect() :
  Shape(), _name("Rect")
{
  init();
}

Rect::~Rect()
{
  delete _name;
  delete[] _positions;
}

void Rect::init()
{
  _positions[0] = {0, 20};
  _positions[1] = {0, 25};
  _positions[2] = {5, 20};
  _positions[3] = {5, 25};
}

void Rect::move()
{
  for (int i = 0; i < 4; ++i)
  {
    _positions[i].x += 5;
  } 
}

void Rect::left()
{
  Serial.println("left");
}

void Rect::right()
{
  Serial.println("right");
}

const char* Rect::name()
{
  return _name;
}

uint Rect::size()
{
  return 4;
}

Position* Rect::positions()
{
  return _positions;
}

Game::Game()
	: _display(SDA, SCL), _shape(new Rect())
{

}

OLED& Game::display()
{
	return _display;
}

void Game::setup()
{
  display().begin();
}

void Game::update()
{
  _shape->move();
}

void Game::draw()
{
  display().clrScr();
  
  Position* positions = _shape->positions();

  int minX = positions[0].x;
  
  for (uint i = 0; i < _shape->size(); ++i)
  {
    Position p = positions[i];
    display().drawRect(p.x, p.y, p.x + RECT_SIZE, p.y + RECT_SIZE);
    display().setPixel(p.x + 2, p.y + 2);

    if (positions[i].x < minX)
    {
      minX = positions[i].x;
    }
  }

  if (minX > SCREEN_HEIGHT)
  {
    _shape->init();
  }

  display().update();
}
