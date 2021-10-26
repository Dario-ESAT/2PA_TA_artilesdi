#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__ 1
#include <SFML/Graphics.hpp>

const int kScreenWidth = 800;
const int kScreenHeight = 900;

enum BrickNumbers{
  rows = 5,
  cols = 12
};

struct hitbox {
  float x1,y1,x2,y2;
};

struct Config {
  int brick_rows;
  int brick_cols;
  int brick_offset;
  int brick_spawn_start;
  int brick_spawn_end;

  float ball_width;
  float ball_height;
  float ball_speed;
  
  float platform_speed;
  float platform_width;
  float platform_height;

  unsigned char platform_r;
  unsigned char platform_g;
  unsigned char platform_b;
  
  unsigned char ball_r;
  unsigned char ball_g;
  unsigned char ball_b;
  
  unsigned char brick_r;
  unsigned char brick_g;
  unsigned char brick_b;
  /* 
  RowsOfBricks=10;
  ColsOfBricks=10;
  BricksOffset=5;
  BricksSpawnStart=40;
  BricksSpawnEnd=80;
  BallWidth=10;
  BallHeight=10;
  BallSpeed=5;
  PlatformWidth=80;
  PlatformHeight=20;
  PlatformSpeed=5;
  PlatformR=245;
  PlatformG=2;
  PlatformB=40;
  BallR=0;
  BallG=255;
  BallB=0;
  BrickR=0;
  BrickG=2;
  BrickB=255;
   */
};


class EntityClass{
  protected:
  sf::RectangleShape shape;
  bool alive;

  public:

  sf::RectangleShape getShape();

  void setShape(sf::RectangleShape shape);

  bool getAlive();

  void setAlive(bool alive = true);
};

#endif
