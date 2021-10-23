#ifndef __BRICK_H__
#define __BRICK_H__ 1
#include <SFML/Graphics.hpp>

#include "..\include\definitions.h"


class Brick : public EntityClass{
  
   protected:

   public:
  Brick(sf::RectangleShape shape, int id, bool alive = true);

  Brick();
};

class BrickNode {
  public:
    Brick data;
    BrickNode* next;

    BrickNode(Brick data);
    ~BrickNode();
};

class BrickList{
  private:
  BrickNode* head;

  public:
  BrickList();
  ~BrickList();

  BrickNode* getHead();
  
  void setHead(BrickNode* head);

  void addBrick(Brick data);

  void printBricks(sf::RenderWindow *window);
  
  void printBricksAlive(sf::RenderWindow *window);

};

#endif