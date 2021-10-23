#ifndef __GAME_H__
#define __GAME_H__ 1

#include <SFML/Graphics.hpp>

#include "..\include\definitions.h"

#include "..\include\ball.h"
#include "..\include\brick.h"
#include "..\include\platform.h"

class Game{
  public:
  int lives, score;
  
  BrickList brick_list;
  PlatformClass player;
  BallClass ball;

  Game();

  bool IsInsideHitbox(hitbox item, float x, float y);
  
  char GetWhereIs(hitbox item, hitbox second_item);

  bool Collision(hitbox first_item, hitbox second_item);

  void buildBricks();

  void initPLatform();

  void initBall();

  void BallBricksCollision();

  void PlatformBallCollision();

  void RestartPLayer();

  void RestartLvL();

  void CheckLoss();
};

#endif