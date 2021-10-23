#ifndef __TABLE_H__
#define __TABLE_H__ 1

#include <iostream>
#include <string>
#include <sqlite3.h>
#include "../include/structs_enums.h"
#include "../include/row.h"

class Table {
public:
  Row *rows_;
  char **row_names_;
  char *table_name_;
  DataTypes *types_;
  int number_of_rows_;
  int number_of_cols_;

  Table(sqlite3 *db);
  ~Table();
private:
  int GetNumberOfCols(sqlite3 *db);
  int GetNumberOfRows(sqlite3 *db);

  void SetTypes(sqlite3 *db);

  std::string aux;
  DataTypes GetTypeFromString(std::string string);

  static int NumberOfColsCallback(void *number_of_cols, int argc, char **argv, 
                                  char **azColName);
};




#endif