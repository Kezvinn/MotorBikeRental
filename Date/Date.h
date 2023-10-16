#ifndef DATE_H
#define DATE_H
#include <bits/stdc++.h>
class Date {
   private:
      int date;
      int month;
      int year;
   public:
      Date();
      Date(int i_date, int i_month, int i_year);
      std::string dateToString();
      friend class System;
};



#endif