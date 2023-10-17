#ifndef MEMBER_H
#define MEMBER_H
#include <bits/stdc++.h>

#include "User.h"
#include "../Request/Request.h"
#include "../Review/MemReview.h"
#include "../Function/Function.h"

#define REQUEST_FILE "Data/Request.txt"
#define MEM_REV_FILE "Data/MemRev.txt"

#define INITIAL_MEM_RATING 10.0
#define INITIAL_CREDITS 20

std::string static ID_TYPE[2] = {"CitizenID", "Passport"};

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
      std::string ownBikeID = "null";
      std::string rentBikeID = "null";

      std::vector <Request*> rqstVect; //request list
      std::vector <MemReview*> memRevVect;   // all review of the member
      Request *currentRequest = nullptr;
   public:
      // Member();
      Member(std::string i_memberID, std::string i_memUsername, std::string i_memPassword,
             std::string i_fullname, std::string i_phoneNumber,
             std::string i_idType, std::string i_idNumber, std::string i_drvNumber,
             std::string i_expDate, float i_memRating, int i_credits,
             std::string i_ownBikeID, std::string i_rentBikeID);
   
      void showMemberInfo();  // show member info
      void sendRequest(std::string bikeID, int cost);  // get dates and create request
      void loadRequest();  //get all request from file txt
      void saveRequestToFile();  //save request to file txt
      void viewRequest();  //choose which requst to accept
      void topUp();  // add credits into accout
      int requestCheck(); //check if request sent is accepted or declined
      void reviewMember(); //leave comment and rating for member
      float memRatingCal();   // calculate average mem rating
   
      friend class System;
};

std::string memIDGenerate();
#endif // MEMBER_H