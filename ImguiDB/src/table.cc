#include "../include/table.h"


Table::Table(sqlite3 *db) {
  number_of_cols_ = GetNumberOfCols(db);
  number_of_rows_ = GetNumberOfRows(db);

  row_names_ = (char**) malloc(sizeof(char*) * number_of_rows_);

  for (int i = 0; i < number_of_rows_; i++) {
    
  }

  rows_ = (Row*) malloc(sizeof(Row*) * number_of_rows_);

  for (int i = 0; i < number_of_rows_; i++) {
    rows_[i].data = (void**) malloc(sizeof(void*) * number_of_cols_);
  }
  
  types_ = (DataTypes*)malloc(sizeof(DataTypes) * number_of_cols_);
  SetTypes(db);

}

Table::~Table() {
  free(types_);
}

void Table::SetTypes(sqlite3 *db) {
  char *err_msg = 0;
  
  char *sql_stmt = "PRAGMA table_info(";
  strcat(sql_stmt,table_name_);
  strcat(sql_stmt,")");

  sqlite3_stmt *stmt;
  sqlite3_prepare(db, sql_stmt, -1, &stmt, NULL);
  
  int col_intex = 0;

  while (sqlite3_step(stmt) == SQLITE_ROW){

    


    col_intex++;
  }
  
}

int Table::GetNumberOfCols(sqlite3 *db){
  int cols = 0;
  char *sql = "PRAGMA table_info(";

  strcat(sql,table_name_);
  strcat(sql,")");
  sqlite3_exec(db, sql, NumberOfColsCallback, &cols, 0);
  
  return cols;
}

int Table::GetNumberOfRows(sqlite3 *db) {
  char *sql_stmt = "SELECT COUNT(*) FROM ";
  strcat(sql_stmt,table_name_);
  
  sqlite3_stmt *stmt;
  sqlite3_prepare(db, sql_stmt, -1, &stmt, NULL);
  sqlite3_step(stmt);

  return sqlite3_column_int(stmt,0);
}

int Table::NumberOfColsCallback(void *number_of_cols, int argc, char **argv, 
                        char **azColName){
  int *number_of_cols_pointer = (int *) number_of_cols;
  *number_of_cols_pointer++;
  return 1;
}

DataTypes Table::GetTypeFromString(std::string string){
  if (string.find("TEXT",0) != std::string::npos) {
    return t_text;
  }

  if (string.find("CHAR",0) != std::string::npos) {
    return t_varchar;
  }
  
  if (string.find("INT",0) != std::string::npos) {
    return t_text;
  }
  
  if (string.find("FLOAT",0) != std::string::npos || 
      string.find("REAL",0) != std::string::npos) {
    return t_float;
  }

  if (string.find("DOUBLE",0) != std::string::npos || 
      string.find("DECIMAL",0) != std::string::npos) {
    return t_double;
  }

  if (string.find("date",0) != std::string::npos) {
    return t_date;
  }
  
  if (string.find("TIME",0) != std::string::npos) {
    return t_time;
  }

  if (string.find("BOOL",0) != std::string::npos) {
    return t_bool;
  }
}



