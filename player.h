#pragma once
#include <SFML\Graphics.hpp>
#include <bitset>
#include "settings.h"

using namespace sf;

class Player
{
private:
	Vector2f position;

	RectangleShape playerShape;

	float playerSpeed = PLAYER_SPEED;

	int direction;

	Color playerColor;

	std::bitset <WIDTH> playerWall[HEIGHT];

public:
	Player(float startX, float startY, int startDirection, Color Color);

	Vector2f getPosition();

	void setPosition(int x, int y);

	RectangleShape getShape();

	void changeDirection(int a);

	int getDirection();

	Color getColor();

	void setWall(int x1, int y1, int x2, int y2);

	void setSingleWall(int x, int y);

	bool isCrashed(int x1, int y1, int x2, int y2);

	void wallReset();

	Vertex move();

	void update();
};