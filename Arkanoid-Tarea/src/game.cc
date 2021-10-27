#include "..\include\game.h"

#include "..\deps\sqlite3\sqlite3.h"

Game::Game() {
  lives = 3;
  score = 0;
}

int Clamp(int value, int min, int max){
  if (value < min) {
    return min;
  }
  if (value > max) {
    return max;
  }
  return value;
}

float Clamp(float value, float min, float max){
  if (value < min) {
    return min;
  }
  if (value > max) {
    return max;
  }
  return value;
}

bool Game::ReadConfig(){
  sqlite3 *db;

  int rc;
  rc = sqlite3_open("../data/configuration.db", &db);
  if( rc ) {
    return false;
  }

  char *sql_stmt = "SELECT id, Width, Height, Speed, Red, Green, Blue FROM PlatformBall WHERE id = 'Ball'";
  sqlite3_stmt *stmt;

  sqlite3_prepare(db, sql_stmt, -1, &stmt, NULL);

  sqlite3_step(stmt);

  config.ball_width = Clamp((float)sqlite3_column_double(stmt,1),5.0f,20.0f);
  config.ball_height = Clamp((float)sqlite3_column_double(stmt,2),5.0f,20.0f);
  config.ball_speed = Clamp((float)sqlite3_column_double(stmt,3),1.0f,20.0f);

  config.ball_r = Clamp(sqlite3_column_int(stmt,4),0,255);
  config.ball_g = Clamp(sqlite3_column_int(stmt,5),0,255);
  config.ball_b = Clamp(sqlite3_column_int(stmt,6),0,255);

  sqlite3_finalize(stmt);

  sql_stmt = "SELECT id, Width, Height, Speed, Red, Green, Blue FROM PlatformBall WHERE id = 'Platform'";

  sqlite3_prepare(db, sql_stmt, -1, &stmt, NULL);

  sqlite3_step(stmt);

  config.platform_width = Clamp((float)sqlite3_column_double(stmt,1),5.0f,20.0f);
  config.platform_height = Clamp((float)sqlite3_column_double(stmt,2),5.0f,20.0f);
  config.platform_speed = Clamp((float)sqlite3_column_double(stmt,3),1.0f,20.0f);

  config.platform_r = Clamp(sqlite3_column_int(stmt,4),0,255);
  config.platform_g = Clamp(sqlite3_column_int(stmt,5),0,255);
  config.platform_b = Clamp(sqlite3_column_int(stmt,6),0,255);

  sqlite3_finalize(stmt);

  sql_stmt = "SELECT Rows, Cols, Start, End, OffsetX, OffsetY, Red, Green, Blue FROM Bricks";
  sqlite3_prepare(db, sql_stmt, -1, &stmt, NULL);

  sqlite3_step(stmt);

  config.brick_rows = Clamp(sqlite3_column_int(stmt,0),3,20);
  config.brick_cols = Clamp(sqlite3_column_int(stmt,1),2,15);

  config.brick_spawn_start = Clamp(sqlite3_column_int(stmt,2),0,100);
  config.brick_spawn_end = Clamp(sqlite3_column_int(stmt,3), config.brick_spawn_start, 500);

  config.brick_offset_x = Clamp((float)sqlite3_column_double(stmt,4),0.0f,10.0f);
  config.brick_offset_y = Clamp((float)sqlite3_column_double(stmt,5),0.0f,10.0f);

  config.brick_r = Clamp(sqlite3_column_int(stmt,6),0,255);
  config.brick_g = Clamp(sqlite3_column_int(stmt,7),0,255);
  config.brick_b = Clamp(sqlite3_column_int(stmt,8),0,255);

  sqlite3_finalize(stmt);
  
  if (sqlite3_close(db) != SQLITE_OK) {
    return false;
  }

  return true;
}

bool Game::IsInsideHitbox(hitbox item, float x, float y){
  return x>item.x1 && x<item.x2 && y>item.y1 && y<item.y2;
}

char Game::GetWhereIs(hitbox item, hitbox second_item){
  if (item.y1 >= second_item.y2 || item.y2 <= second_item.y1) {
    return 'T';
  } else if(item.x1 >= second_item.x2 || item.x2 <= second_item.x1){
    return 'S';
  }
  
  return 'N';
}

bool Game::Collision(hitbox first_item, hitbox second_item){
  return IsInsideHitbox(first_item,second_item.x1,second_item.y1) || 
  IsInsideHitbox(first_item,second_item.x2,second_item.y1) ||
  IsInsideHitbox(first_item,second_item.x1,second_item.y2) || 
  IsInsideHitbox(first_item,second_item.x2,second_item.y2);
}

void Game::BuildBricks(sf::Vector2u window_size){

  sf::Vector2f position = sf::Vector2f(config.brick_offset_x,config.brick_spawn_start);
  
  float size_y = (config.brick_spawn_end - config.brick_spawn_start) / config.brick_rows;
  float size_x = (window_size.x - (config.brick_offset_x * config.brick_cols)) / config.brick_cols;

  sf::Vector2f size = sf::Vector2f(size_x,size_y);
  
  sf::RectangleShape shape(size);
  shape.setFillColor(sf::Color(config.brick_r, config.brick_g, config.brick_b));
  
  for (int i = 0; i < config.brick_rows; i++) {
    for (int f = 0; f < config.brick_cols; f++) {
      if (f != 0) {
        position.x += size.x + config.brick_offset_x;
      }
      
      shape.setPosition(position);
      Brick building_brick(shape);

      brick_list.addBrick(building_brick);
      
    }
    position.x = config.brick_offset_x;
    position.y += size.y + config.brick_offset_y;
  }
  
}

void Game::InitPLatform(sf::Vector2u window_size){
  sf::RectangleShape player_shape(sf::Vector2f(80,20));
  player_shape.setPosition(window_size.x/2,window_size.y - config.platform_height);
  
  player_shape.setFillColor(sf::Color(config.platform_r, config.platform_g, config.platform_b));

  player = PlatformClass(player_shape,config.platform_speed);
}

void Game::InitBall(){
  sf::RectangleShape shape(sf::Vector2f(config.ball_width,config.ball_height));
  
  shape.setPosition(sf::Vector2f(player.getShape().getPosition().x + player.getShape().getSize().x/2 - shape.getSize().x/2,player.getShape().getPosition().y - player.getShape().getSize().y - 5));

  shape.setFillColor(sf::Color(config.ball_r, config.ball_g, config.ball_b));
  
  ball = BallClass(shape,sf::Vector2i(1,-1),config.ball_speed);

  // printf("ball-> %f\n",ball.getShape().getPosition().y);
}

void Game::BallBricksCollision(){
  sf::Vector2f raycast = sf::Vector2f(ball.getShape().getPosition().x + ball.getDirection().x * ball.getSpeed(), ball.getShape().getPosition().y + ball.getDirection().y * ball.getSpeed());
  
  hitbox h_ball_raycast = {raycast.x,raycast.y,
    raycast.x + ball.getShape().getSize().x,raycast.y + ball.getShape().getSize().y};
  
  hitbox h_ball = {ball.getShape().getPosition().x,ball.getShape().getPosition().y,
    ball.getShape().getPosition().x + ball.getShape().getSize().x,ball.getShape().getPosition().y + ball.getShape().getSize().y};
  
  for (BrickNode* current = brick_list.getHead(); current != nullptr; current = current->next) {
    if (current->data.getAlive()) {
      hitbox h_brick = {current->data.getShape().getPosition().x,current->data.getShape().getPosition().y,
        current->data.getShape().getPosition().x + current->data.getShape().getSize().x,current->data.getShape().getPosition().y + current->data.getShape().getSize().y};

      if (Collision(h_brick,h_ball_raycast)) {
        current->data.setAlive(false);
        ball.Bounce(GetWhereIs(h_brick,h_ball));
        break;
      }
    }
  }
}

void Game::PlatformBallCollision(){
  sf::Vector2f raycast = sf::Vector2f(ball.getShape().getPosition().x + ball.getDirection().x * ball.getSpeed(), ball.getShape().getPosition().y + ball.getDirection().y * ball.getSpeed());

  hitbox h_ball_raycast = {raycast.x,raycast.y,
    raycast.x + ball.getShape().getSize().x,raycast.y + ball.getShape().getSize().y};
  
  hitbox h_ball = {ball.getShape().getPosition().x,ball.getShape().getPosition().y,
    ball.getShape().getPosition().x + ball.getShape().getSize().x,ball.getShape().getPosition().y + ball.getShape().getSize().y};
  hitbox h_platform = {player.getShape().getPosition().x,player.getShape().getPosition().y,
        player.getShape().getPosition().x + player.getShape().getSize().x,player.getShape().getPosition().y + player.getShape().getSize().y};
    
  if (Collision(h_platform,h_ball_raycast)) {
    if (player.getDirection().x != 0) {
      ball.setDirection(sf::Vector2i(player.getDirection().x, -1));
    } else {
      ball.setDirection(sf::Vector2i(ball.getDirection().x, -1));
    }
  }
}

void Game::RestartPLayer() {
  sf::RectangleShape shape = player.getShape(); 
  shape.setPosition(360,860);
  player.setShape(shape);
  
  shape = ball.getShape();
  shape.setPosition(sf::Vector2f(player.getShape().getPosition().x + player.getShape().getSize().x/2 - shape.getSize().x/2,player.getShape().getPosition().y - player.getShape().getSize().y - 5));
  ball.setShape(shape);
}

void Game::RestartLvL(){
  RestartPLayer();
  lives = 3;
  for (BrickNode* current = brick_list.getHead(); current != nullptr; current = current->next) {
    current->data.setAlive();
  }
}

void Game::CheckLoss(){
    if(ball.getShape().getPosition().y >= kScreenHeight - ball.getShape().getSize().y){
      lives--;
      if (lives < 0){
        RestartLvL();
      } else {
        RestartPLayer();
      }
    }
  }
 