#ifndef __GAME_H__
#define __GAME_H__ 1

#include <SFML/Graphics.hpp>
#include <fstream>

using namespace std;

#include "..\include\definitions.h"

#include "..\include\ball.h"
#include "..\include\brick.h"
#include "..\include\platform.h"

class Game {
  public:
  int lives, score;
  Config config;
  
  BrickList brick_list;
  PlatformClass player;
  BallClass ball;

  Game();

  bool IsInsideHitbox(hitbox item, float x, float y);
  
  char GetWhereIs(hitbox item, hitbox second_item);

  bool Collision(hitbox first_item, hitbox second_item);

  void BuildBricks(sf::Vector2u window_size);

  void InitPLatform(sf::Vector2u window_size);

  void InitBall();

  void BallBricksCollision();

  void PlatformBallCollision();

  void RestartPLayer();

  void RestartLvL();

  void CheckLoss();

  bool ReadConfig();
};

#endif