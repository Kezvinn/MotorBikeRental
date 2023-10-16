#include "Date.h"
Date::Date(){};
Date::Date(int i_date, int i_month, int i_year) : date(i_date), month(i_month), year(i_year){};
std::string Date::dateToString(){
   return (std::to_string(this->date) + "/" + std::to_string(this->month) + "/" + std::to_string(this->year));
}
