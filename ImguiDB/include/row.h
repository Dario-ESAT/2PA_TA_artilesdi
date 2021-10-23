#ifndef __ROW_H__
#define __ROW_H__ 1

#include "../include/structs_enums.h"
#include "../include/column.h"

class Row {
public:
  void **data;
  Row();
  ~Row();
};




#endif