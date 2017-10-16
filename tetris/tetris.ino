/*
 Name:		tetris.ino
 Created:	10/13/2017 6:33:48 PM
 Author:	olehkurpiak
*/

#include <OLED_I2C.h>
#include "Game.h"

#define LEFT_BUTTIN_PIN 4
#define RIGHT_BUTTON_PIN 5

Game game;

void setup()
{
	Serial.begin(9600);
	randomSeed(analogRead(0));

	pinMode(LEFT_BUTTIN_PIN, INPUT);
	pinMode(RIGHT_BUTTON_PIN, INPUT);

	game.setup();
}

void loop()
{
	game.update();

	if (digitalRead(LEFT_BUTTIN_PIN) == HIGH) 
	{
		game.shapeToLeft();
	}
	else if (digitalRead(RIGHT_BUTTON_PIN) == HIGH)
	{
		game.shapeToRight();
	}

	game.draw();

	delay(300);
}
