#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <SFML/Graphics.hpp>

#include "definitions.h"
#include "brick.h"
#include "platform.h"
#include "ball.h"
#include "game.h"


int main(int argc, char** argv){
  sf::RenderWindow window(sf::VideoMode(kScreenWidth, kScreenHeight), "SFML works!");
  window.setFramerateLimit(30);
  window.getSize();
  Game game;
  game.BuildBricks(window.getSize());
  game.InitPLatform(window.getSize());
  game.InitBall();

  while (window.isOpen()){

    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed || 
          sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        window.close();
      }
    }
    // ---- Input ------------

    game.player.MovePlatform();
    game.ball.MoveBall();

    // ---------------------------

    // ---- Update ---------------

    game.BallBricksCollision();
    game.PlatformBallCollision();
    game.ball.CheckBoundaries();
    game.CheckLoss();

    // ---------------------------

    window.clear();

    // ---- Draw ------------------------

    game.player.DrawPlatform(&window);
    game.brick_list.printBricksAlive(&window);
    game.ball.DrawBall(&window);
    
    // ----------------------------------

    window.display();

  }

  return 0;
}

