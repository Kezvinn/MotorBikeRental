#include "Member.h"

std::string memIDGenerate(){
   srand(time(NULL));
   int num = rand() % 1001; //random number form 0-1000
   return ("M-" + std::to_string(num));
}

Member::Member(){
   std::cout << "Member default constructor" << std::endl;
};
Member::Member(std::string i_memberID, std::string i_memUsername, std::string i_memPassword,
               std::string i_fullname, std::string i_phoneNumber,
               std::string i_idType, std::string i_idNumber, std::string i_drvNumber,
               std::string i_expDate, float i_memRating, int i_credits)
    : memberID(i_memberID), User(i_memUsername, i_memPassword),
      fullName(i_fullname), phoneNumber(i_phoneNumber),
      idType(i_idType), idNumber(i_idNumber), drvNumber(i_drvNumber),
      expDate(i_expDate), memRating(i_memRating), credits(i_credits){};

void Member::showMemberInfo(){
   std::cout << "=====================================================" << std::endl;
   std::cout << "Fullname: " << fullName << "\tPhone#: " << phoneNumber << std::endl;
   std::cout << "ID type: " << idType << "\tID#: " << idNumber << std::endl;
   std::cout << "Drv License #: " << drvNumber << "\tExp. date: " << expDate <<std::endl;
   std::cout << "Rating: " <<memRating<<std::endl;
   std::cout << "Credits: " << credits << std::endl;
   std::cout << "=====================================================" << std::endl;
}