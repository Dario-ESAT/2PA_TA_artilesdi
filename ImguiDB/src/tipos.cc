#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

int callback(void *, int, char **, char **);

class ClaseTonta {
public:
  int hola;
  ClaseTonta();
  ClaseTonta(int a);
  ~ClaseTonta();
};

ClaseTonta::ClaseTonta() {
  hola = 5;
}

ClaseTonta::ClaseTonta(int a_) {
  hola = a_;
}
ClaseTonta::~ClaseTonta()
{
}


int GetVarcharMaxFromString(std::string string){
  int start = string.find("(",0);
  int end = string.find(")",start + 1);
  // printf("%d:%c - %d:%c = %d\n",start,string[start], end,string[end], end - start);

  char *number = (char *) malloc(sizeof(char)* (end - start));
  
  for (int i = start; i < end; i++) {
    // printf("%d-%c  %d\n",i,string[i + 1], i - start);
    number[i - start] = string[i + 1];
  }
  
  number[end - start - 1] = '\0';
  // printf("--%s--  %d\n", number, end - start - 1);
  return atoi(number);
}

int main(void) {
  // const int tonterias = 3;
  // ClaseTonta *tonteria = new ClaseTonta[tonterias];
  // tonteria[2] = *new ClaseTonta(6);
  // for (int i = 0; i < tonterias; i++) {
  //   printf("%d \n", tonteria[i].hola);
  // }






  // sqlite3 *db;
  // char *err_msg = 0;
  
  // int rc = sqlite3_open("../data/jardineria.db", &db);
  
  // if (rc != SQLITE_OK) {
      
  //   fprintf(stderr, "Cannot open database: %s\n", 
  //           sqlite3_errmsg(db));
  //   sqlite3_close(db);
    
  //   return 1;
  // }
  
  // char *sql = "PRAGMA table_info(pago)";
      
  // rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
  
  // if (rc != SQLITE_OK ) {
      
  //     fprintf(stderr, "Failed to select data\n");
  //     fprintf(stderr, "SQL error: %s\n", err_msg);

  //     sqlite3_free(err_msg);
  //     sqlite3_close(db);
      
  //     return 1;
  // }
  

  // char *table_name_ = nullptr;

  // char *sql_stmt = "SELECT name FROM sqlite_master WHERE type='table'";

  // sqlite3_stmt *stmt;
  // sqlite3_prepare(db, sql_stmt, -1, &stmt, NULL);

  // int table_index = 0;
  // while (sqlite3_step(stmt) == SQLITE_ROW){
  //   char *name = (char *) sqlite3_column_text(stmt,0);
  //   int col_name_size = strlen(name);

  //   table_name_ = (char *) malloc(sizeof(char) * (col_name_size + 1));
  //   table_name_[0] = '\0';

  //   strcpy(table_name_,name);
  //   printf("%d -> %s\n", name != table_name_, table_name_);
  //   table_index++;
  //   free(table_name_);
  //   table_name_ = nullptr;
  // }

  // sqlite3_finalize(stmt);



  // sqlite3_stmt *stmt;
  // sql = "PRAGMA table_info(pago)";
  // sqlite3_prepare(db, sql, -1, &stmt, NULL);
  // int a = 0;
  // // printf("hola %d\n", sqlite3_step(stmt));
  // while (sqlite3_step(stmt) == SQLITE_ROW) {
  //   printf("OK %d\n", sqlite3_column_int(stmt,0));
  // }
  



  // sqlite3_close(db);
  
  return 0;
}

// int callback(void *count_, int argc, char **argv, 
//                     char **azColName) {
  // for (int i = 0; i < argc; i++) {
    // printf("%d",a.find("CHAR",0) != std::string::npos);
      // std::string a (argv[2]);

      // if (a.find("CHAR",0) != std::string::npos) {
      //   printf("%s\n", argv[2] ? argv[2] : "NULL");
      //   printf("---- %d ---\n", GetVarcharMaxFromString(a));
      // }
    // a.std::string::~string(); 
  // }
  // printf("\n");
  
//   return 0;
// }