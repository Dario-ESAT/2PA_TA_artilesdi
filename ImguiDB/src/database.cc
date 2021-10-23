#include "../include/database.h"
#include "../include/table.h"
#include <stdint.h>
Database::Database(char *db_path) {

  db_path_ = db_path;
  Open();
  
  number_of_tables_ = 0;
  CountTables();
  // InitializeTables();
}

Database::~Database() {
  Close();
}

void Database::InitializeTables(){
  
  tables_ = (Table*) malloc(sizeof(Table) * number_of_tables_);


  char *sql = "SELECT name FROM sqlite_master WHERE type='table'";
  sqlite3_exec(db_, sql, InitializeTablesCallback, 0, 0);
}

void Database::CountTables(){

  char *sql = "SELECT COUNT(name) FROM sqlite_master WHERE type='table'";
  sqlite3_exec(db_, sql, NumberOfTablesCallback, &number_of_tables_, 0);
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

int Database::NumberOfTablesCallback(void *number_of_tables, int argc, char **argv, 
                          char **azColName){
  int *number_of_tables_pointer = (int *) number_of_tables;
  *number_of_tables_pointer = atoi(argv[0]);
  return 1;
}

int Database::InitializeTablesCallback(void *number_of_tables, int argc, char **argv, 
                          char **azColName){

  return 1;
}
