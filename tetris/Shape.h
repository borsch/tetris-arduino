#ifndef SHAPE_H
#define SHAPE_H

#include <OLED_I2C.h>

typedef unsigned int uint;

struct Position
{
  int x;
  int y;
};

class Shape
{
public:
	Shape() {}
  virtual ~Shape() {}

  virtual void move() = 0;
  virtual void left() = 0;
  virtual void right() = 0;
  virtual const char* name() = 0;
  virtual void init() = 0;
  virtual uint size() = 0;
  virtual Position* positions() = 0;
};

class Rect: public Shape
{
private:
  const char* _name;
  Position _positions[4];
public:
  Rect();
  ~Rect();
  
  virtual void move();
  virtual void left();
  virtual void right();
  virtual const char* name();
  virtual void init();
  virtual uint size();
  virtual Position* positions();
};

class Game
{
private:
	OLED _display;
  Shape* _shape;
  
  OLED& display();
public:
	Game();

  void setup();
  
  void update();
  void draw();
};

#endif
