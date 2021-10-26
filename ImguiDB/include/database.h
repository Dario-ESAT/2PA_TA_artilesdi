#ifndef __DATABASE_H__
#define __DATABASE_H__ 1
#include "sqlite3.h"
#include "../include/table.h"
#include <stdio.h>

class Database {
public:
  sqlite3 *db_;
  Table *tables_;
  Table *consulta;
  int number_of_tables_;
  char *db_path_;

  Database(char *db_path);
  ~Database();
  

private:
  bool Open();
  bool Close();

  void InitializeTables();
  void SetNumberOfTables();

};




#endif
