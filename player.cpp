#include <algorithm>
#include "player.h"
#include "settings.h"

Player::Player(float startX, float startY, int startDirection, sf::Color Color)
{
	position.x = startX;
	position.y = startY;

	playerShape.setSize(sf::Vector2f(PLAYER_LENGTH,PLAYER_HEIGHT));
	playerShape.setPosition(position);

	direction = startDirection+1;
	changeDirection(startDirection);
	direction = startDirection;

	playerShape.setFillColor(Color);

	playerColor = Color;

	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			playerWall[j][i] = 0;
		}
	}
}

sf::Vector2f Player::getPosition()
{
	return position;
}

void Player::setPosition(int x, int y)
{
	position = sf::Vector2f(x, y);
}

sf::RectangleShape Player::getShape()
{
	return playerShape;
}

void Player::changeDirection(int a)
{
	if (a % 2 != direction % 2)
	{
		switch (a)
		{
		case up:
			playerShape.setRotation(270);
			break;

		case down:
			playerShape.setRotation(90);
			break;

		case left:
			playerShape.setRotation(180);
			break;

		case right:
			playerShape.setRotation(0);
			break;

		default:
			break;
		}
		direction = a;
	}
}

int Player::getDirection()
{
	return direction;
}

sf::Color Player::getColor()
{
	return playerColor;
}

void Player::setWall(int x1, int y1, int x2, int y2)
{
	if (x1 == x2)
	{
		for (int i = std::min(y1, y2); i <= std::max(y1, y2); i++)
		{
			if(i > 0 && i < HEIGHT) playerWall[i][x1] = 1;
		}
	}
	else if (y1 == y2)
	{
		for (int i = std::min(x1, x2); i <= std::max(x1, x2); i++)
		{
			if (i > 0 && i < WIDTH) playerWall[y1][i] = 1;
		}
	}
	playerWall[(int)position.y][(int)position.x] = 0;
}

void Player::setSingleWall(int x, int y)
{
	if(x > 0 && y > 0 && x < WIDTH && y < HEIGHT) playerWall[y][x] = 1;
}

bool Player::isCrashed(int x1, int y1, int x2, int y2)
{
	if (x1 == x2)
	{
		for (int i = std::min(y1, y2); i <= std::max(y1, y2); i++)
		{
			if (i > 0 && i < HEIGHT && playerWall[i][x1]) return 1;
		}
	}
	else if (y1 == y2)
	{
		for (int i = std::min(x1, x2); i <= std::max(x1, x2); i++)
		{
			if (i > 0 && i < WIDTH && playerWall[y1][i]) return 1;
		}
	}
	return 0;
}

void Player::wallReset()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		playerWall[i].reset();
	}

	for (int j = 0; j <= 5; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			playerWall[j][i] = 1;
			playerWall[HEIGHT - 1 - j][i] = 1;
		}
	}

	for (int j = 0; j <= 5; j++)
	{
		for (int i = 0; i < HEIGHT; i++)
		{
			playerWall[i][j] = 1;
			playerWall[i][WIDTH - 1 - j] = 1;
		}
	}
}

sf::Vertex Player::move()
{
	Vector2f pos = position;
	switch (direction)
	{
	case up:
		position.y -= playerSpeed;
		break;

	case down:
		position.y += playerSpeed;
		break;

	case right:
		position.x += playerSpeed;
		break;

	case left:
		position.x -= playerSpeed;
		break;

	default:
		break;
	}
	
	return Vertex(pos, playerColor);
}

void Player::update()
{
	playerShape.setPosition(position);
}