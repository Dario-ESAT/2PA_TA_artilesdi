#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

int callback(void *, int, char **, char **);

int main(void) {
    
  sqlite3 *db;
  char *err_msg = 0;
  
  int rc = sqlite3_open("../data/jardineria.db", &db);
  
  if (rc != SQLITE_OK) {
      
    fprintf(stderr, "Cannot open database: %s\n", 
            sqlite3_errmsg(db));
    sqlite3_close(db);
    
    return 1;
  }
  
  char *sql = "PRAGMA table_info(pago)";
      
  rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
  
  if (rc != SQLITE_OK ) {
      
      fprintf(stderr, "Failed to select data\n");
      fprintf(stderr, "SQL error: %s\n", err_msg);

      sqlite3_free(err_msg);
      sqlite3_close(db);
      
      return 1;
  }

  sqlite3_stmt *stmt;

  sql = "SELECT COUNT(*) FROM pago";
  sqlite3_prepare(db, sql, -1, &stmt, NULL);
  int a = 0;
  // printf("hola %d\n", sqlite3_step(stmt));
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    printf("OK %d\n", sqlite3_column_int(stmt,0));
  }
  



  sqlite3_close(db);
  
  return 0;
}

int callback(void *NotUsed, int argc, char **argv, 
                    char **azColName) {
    
  NotUsed = 0;
  
  for (int i = 0; i < argc; i++) {

    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  
  printf("\n");
  
  return 0;
}