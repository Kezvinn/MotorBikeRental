#include "Member.h"
#include "User.cpp"
#include "../Request/Request.cpp"

std::string memIDGenerate(){
   srand(time(NULL));
   int num = rand() % 1001; //random number form 0-1000
   return ("M-" + std::to_string(num));
}
Member::Member(){};
Member::Member(std::string i_memberID, std::string i_memUsername, std::string i_memPassword,
               std::string i_fullname, std::string i_phoneNumber,
               std::string i_idType, std::string i_idNumber, std::string i_drvNumber,
               std::string i_expDate, float i_memRating,int i_credits)
    : memberID(i_memberID), User(i_memUsername, i_memPassword),
      fullname(i_fullname), phoneNumber(i_phoneNumber),
      idType(i_idType), idNumber(i_idNumber), drvNumber(i_drvNumber),
      expDate(i_expDate), memRating(i_memRating),credits(i_credits){};
