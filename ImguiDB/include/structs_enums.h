#ifndef __STRUCTS_ENUMS_H__
#define __STRUCTS_ENUMS_H__ 1

enum DataTypes {
  t_int,
  t_float,
  t_double,
  t_text,
  t_varchar,
  t_bool,
  t_date,
  t_time,
  t_date_time
};

struct TextType {
  char *  text;
  int     size;
};


#endif