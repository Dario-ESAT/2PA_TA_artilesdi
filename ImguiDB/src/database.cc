#include "../include/database.h"
#include "../include/table.h"
#include <stdint.h>
Database::Database(char *db_path) {

  db_path_ = db_path;
  Open();
  
  SetNumberOfTables();
  InitializeTables();
}

Database::~Database() {
  Close();
}

void Database::InitializeTables(){
  tables_ = new Table[number_of_tables_];
  char *sql_stmt = "SELECT name FROM sqlite_master WHERE type='table'";

  sqlite3_stmt *stmt;
  sqlite3_prepare(db_, sql_stmt, -1, &stmt, NULL);

  int table_index = 0;
  while (sqlite3_step(stmt) == SQLITE_ROW){

    char *name = (char *) sqlite3_column_text(stmt,0);
    printf("%s\n", name);
    tables_[table_index].Innit(db_,name);
    table_index++;
    printf("%d\n",table_index);
  }
  printf("%s\n","OUT");
  sqlite3_finalize(stmt);
}

void Database::SetNumberOfTables(){
  char *sql_stmt = "SELECT COUNT(name) FROM sqlite_master WHERE type='table'";
  sqlite3_stmt *stmt;
  sqlite3_prepare(db_, sql_stmt, -1, &stmt, NULL);
  if (sqlite3_step(stmt) == SQLITE_ROW) {

    number_of_tables_ = sqlite3_column_int(stmt,0);
  } else {

    number_of_tables_ = 0;
  }
  sqlite3_finalize(stmt);
  
}

bool Database::Open(){
 int rc;

  rc = sqlite3_open(db_path_, &db_);

  if( rc ) {
    return false;
  } else {
    return true;
  }
  sqlite3_close(db_);
};

bool Database::Close () {
  if (sqlite3_close(db_) != SQLITE_OK) {
    return false;
  }
  return true;
}
