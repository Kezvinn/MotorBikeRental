#ifndef MEMBER_H
#define MEMBER_H
#include <bits/stdc++.h>
//----------------------------------------------------------------
#include "User.h"
#include "../Request/Request.h"
#include "../Review/MemReview.h"
#include "../Review/BikeReview.h"
#include "../Function/Function.h"
//----------------------------------------------------------------
#define REQUEST_FILE "Data/Request.txt"   //file requests
#define MEM_REV_FILE "Data/MemRev.txt" //file member reviews
#define BIKE_REV_FILE "Data/BikeRev.txt"  //file bike review
//----------------------------------------------------------------
#define INITIAL_MEM_RATING 10.0
#define INITIAL_CREDITS 20

std::string static ID_TYPE[2] = {"CitizenID", "Passport"};
//----------------------------------------------------------------
#define TODAY_DATE "26/12/2023"  //today

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
      std::vector <BikeReview*> bikeRevVect; // all review of the member
      Request *currentRequest = nullptr;
   public:
      Member();
      Member(std::string i_memberID, std::string i_memUsername, std::string i_memPassword,
             std::string i_fullname, std::string i_phoneNumber,
             std::string i_idType, std::string i_idNumber, std::string i_drvNumber,
             std::string i_expDate, float i_memRating, int i_credits,
             std::string i_ownBikeID, std::string i_rentBikeID);
   
      void showMemberInfo();  // show member info
      
      //request handle function
      void sendRequest(std::string bikeID, int cost);  // get dates and create request
      void viewRequest();  //view all and choose which request to action
      void requestCheck();   //check status of sent requests
      
      //input
      void loadRequest();  //get all request from file txt
      void loadMemRev();   //load member review txt
      void loadBikeRev(); //load bike review txt
      
      //output
      void saveRequestToFile();  //save request to file txt
      void saveMemRevToFile(); //save member review to file txt
      void saveBikeRevToFile(); //save bike review to file txt

      //member review function
      void reviewMember(std::string renterID); //leave comment and rating for member      
      void memRatingCal(); // calculate avg member rating
      std::vector<std::string> getRenter(std::vector<std::string> &storage); // retrieve approved requestest renter ID for review
      
      //bike review function
      void reviewBike(std::string rentedBikeID);
      // void bikeRatingCal(); // calculate avg member rating
      std::vector<std::string> getRentedBike(std::vector<std::string> &storage); // retrieve approved requestest renter ID for review
      
      //credits add
      void topUp();  // add credits into accout
      
      // int rentDuration(); //check for accepted request and return duration
      
      friend class System;
};

std::string memIDGenerate();
#endif // MEMBER_H