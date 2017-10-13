/*
 Name:		tetris.ino
 Created:	10/13/2017 6:33:48 PM
 Author:	olehkurpiak
*/

#include <OLED_I2C.h>
#include "Shape.h"

Game game;

void setup()
{
	Serial.begin(9600);
	randomSeed(analogRead(0));

	game.setup();
}

void loop()
{
	game.update();
	game.draw();

	delay(500);
}
