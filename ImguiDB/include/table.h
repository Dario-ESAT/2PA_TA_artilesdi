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
  char **cols_names_;
  char *table_name_;
  DataTypes *types_;
  int number_of_rows_;
  int number_of_cols_;

  Table();
  void Innit(sqlite3 *db, char *name);
  ~Table();
private:
  int GetNumberOfCols(sqlite3 *db);
  int GetNumberOfRows(sqlite3 *db);

  void SetTypesAndNames(sqlite3 *db);

  DataTypes GetTypeFromString(std::string string);
  int GetVarcharMaxFromString(std::string string);


  static int NumberOfColsCallback(void *number_of_cols, int argc, char **argv, 
                                  char **azColName);
};




#endif