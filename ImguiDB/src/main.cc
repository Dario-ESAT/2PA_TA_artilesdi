#include <SFML/Graphics.hpp>

#include "../include/structs_enums.h"
#include "../include/database.h"
#include "../include/table.h"
#include "../include/imgui_window.h"


int main() {
  // sf::RenderWindow window(sf::VideoMode(1200, 900), "DB con Imgui");
  // ImGui::SFML::Init(window);
  // char *sql = (char *)calloc(strlen("PRAGMA table_info(") + strlen("table_name_") + strlen(")") + 1,sizeof(char));
  
  // strcat(sql,"PRAGMA table_info(");
  // strcat(sql,"table_name_");
  // strcat(sql,")");
  // printf("%s",sql);
  Database *database = new Database("../data/jardineria.db");
  printf("%s - Table Name",database->tables_[0].table_name_);
  printf("%d - Number of tables",database->number_of_tables_);
  for (int i = 0; i < database->tables_[0].number_of_cols_; i++) {
    printf("%s - Cols name",database->tables_[0].cols_names_[i]);
  }

  // CharType *char_aux;
  // for (int i = 0; i < database->tables_[0].number_of_cols_; i++) {

  //   if (database->tables_[0].rows_[0].data[i] != nullptr) {
  //     char_aux = (CharType*)database->tables_[0].rows_[0].data[i];
  //     printf("Varchar max: %d\n",char_aux->size);
  //   }
  // }

  



  // while (window.isOpen()) {
  // sf::Event event;
  // while (window.pollEvent(event)) {

  //   if (event.type == sf::Event::Closed)
  //   window.close();
  // }
  // printf("%d\n", window.getSize().x);
  // window.clear();
  
  // window.display();
  // }

return 0;
}

