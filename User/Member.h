#ifndef MEMBER_H
#define MEMBER_H
#include <bits/stdc++.h>
#include "User.h"

#define INITIAL_MEM_RATING 10.0
#define INITIAL_CREDITS 20

std::string static ID_TYPE[3] = {"CitizenID", "Passport"};

class Member : public User {
   private:
      std::string fullName;
      std::string phoneNumber;
      std::string idType; 
      std::string idNumber;
      std::string drvNumber;
      std::string expDate;    //DD/MM/YYYY
      float memRating;
      std::string memberID; //auto-generated
      int credits;
      bool ownBike = false;  
      std::string ownBikeID = "null";
   public:
      Member();
      Member(std::string i_memberID, std::string i_memUsername, std::string i_memPassword,
             std::string i_fullname, std::string i_phoneNumber,
             std::string i_idType, std::string i_idNumber, std::string i_drvNumber,
             std::string i_expDate, float i_memRating, int i_credits,
             bool i_ownBike, std::string i_ownBikeID);
      void showMemberInfo();
      friend class System;
};
std::string memIDGenerate();

#endif // MEMBER_H