#include "../include/table.h"


void Table::Innit(sqlite3 *db, char* name) {
  int col_name_size = strlen(name);

  table_name_ = (char *) malloc(sizeof(char) * (col_name_size + 1));
  table_name_[0] = '\0';

  strcpy(table_name_,name);
  printf("%s\n", table_name_);

  number_of_cols_ = GetNumberOfCols(db);
  number_of_rows_ = GetNumberOfRows(db);

  cols_names_ = (char**) malloc(sizeof(char*) * number_of_rows_);
  for (int i = 0; i < number_of_rows_; i++) {
    cols_names_[i] = nullptr;
  }

  types_ = (DataTypes*)malloc(sizeof(DataTypes) * number_of_cols_);
  SetTypesAndNames(db);
  
  rows_ = new Row[number_of_rows_];
  for (int i = 0; i < number_of_rows_; i++) {
    rows_[i].data = (void**) malloc(sizeof(void*) * number_of_cols_);
    
    for (int j = 0; j < number_of_cols_; j++) {
      rows_[i].data = nullptr; 
    }
  }
  
}

Table::~Table() {
  free(types_);
}
Table::Table() {

}
void Table::SetTypesAndNames(sqlite3 *db) {
  char *err_msg = 0;
  char *sql_stmt = (char *)calloc(strlen("PRAGMA table_info(") + strlen(table_name_) + strlen(")") + 1,sizeof(char));
  
  strcat(sql_stmt,"PRAGMA table_info(");
  strcat(sql_stmt,table_name_);
  strcat(sql_stmt,")");

  sqlite3_stmt *stmt;
  sqlite3_prepare(db, sql_stmt, -1, &stmt, NULL);
  
  int col_intex = 0;
  char *type_char = nullptr;

  while (sqlite3_step(stmt) == SQLITE_ROW){

    char *col_name_aux = (char *) sqlite3_column_text(stmt,1);
    int col_name_size = strlen(col_name_aux);

    cols_names_[col_intex] = (char *) calloc(col_name_size + 1,sizeof(char));
    cols_names_[col_intex][0] = '\0';

    strcpy(cols_names_[col_intex],col_name_aux);

    type_char = (char *) sqlite3_column_text(stmt,2);

    if ((types_[col_intex] = GetTypeFromString(type_char)) == t_char) {
      for (int i = 0; i < number_of_rows_; i++) {

        CharType *data_template = (CharType *)malloc(sizeof(CharType));

        data_template->size = GetVarcharMaxFromString(type_char);
        data_template->text = (char *) calloc(data_template->size,sizeof(char));
        
        rows_[col_intex].data[i] = (void *) data_template;
      }
    }
    col_intex++;
  }

  sqlite3_finalize(stmt);
  
}

int Table::GetNumberOfCols(sqlite3 *db){
  int cols = 0;
  char *sql = (char *)calloc(
        strlen("PRAGMA table_info(") + 
        strlen(table_name_) + 
        strlen(")") + 1 ,sizeof(char));

  strcat(sql,"PRAGMA table_info(");
  strcat(sql,table_name_);
  strcat(sql,")");
  sqlite3_exec(db, sql, NumberOfColsCallback, &cols, 0);
  free(sql);
  return cols;
}

int Table::GetNumberOfRows(sqlite3 *db) {
  char *sql_stmt = (char *)calloc(strlen("PRAGMA table_info(") + 
        strlen(table_name_) + 1,sizeof(char));
  
  strcat(sql_stmt,"PRAGMA table_info(");
  strcat(sql_stmt,table_name_);
  
  sqlite3_stmt *stmt;
  sqlite3_prepare(db, sql_stmt, -1, &stmt, NULL);
  sqlite3_step(stmt);

  int number = sqlite3_column_int(stmt,0);
  sqlite3_finalize(stmt);
  
  return number;
}

DataTypes Table::GetTypeFromString(std::string string){
  if (string.find("TEXT",0) != std::string::npos) {
    return t_text;
  }

  if (string.find("CHAR",0) != std::string::npos) {
    return t_char;
  }
  
  if (string.find("INT",0) != std::string::npos) {
    return t_int;
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

  return t_int;
}

int Table::GetVarcharMaxFromString(std::string string){
  int start = string.find("(",0);
  int end = string.find(")",start + 1);
  char *number = (char *) malloc(sizeof(char)* (end - start));
  
  for (int i = start; i < end; i++) {
    number[i - start] = string[i + 1];
  }
  
  number[end - start - 1] = '\0';

  return atoi(number);
}


int Table::NumberOfColsCallback(void *number_of_cols, int argc, char **argv, 
                        char **azColName){
  int *number_of_cols_pointer = (int *) number_of_cols;
  *number_of_cols_pointer++;
  return 1;
}




