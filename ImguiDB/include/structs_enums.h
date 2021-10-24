#ifndef __STRUCTS_ENUMS_H__
#define __STRUCTS_ENUMS_H__ 1

enum DataTypes {
  t_int,
  t_float,
  t_double,
  t_text,
  t_char,
  t_bool,
  t_date,
  t_time,
  t_date_time
};

struct CharType {
  char *  text;
  int     size;
};

struct DateType {
  int year;
  int month;
  int day;
};

struct TimeType {
  int hours;
  int minutes;
  int seconds;
};

struct DateTimeType {
  DateType date;
  TimeType time;
};


#endif