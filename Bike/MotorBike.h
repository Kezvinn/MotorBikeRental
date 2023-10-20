#ifndef MOTORBIKE_H
#define MOTORBIKE_H

#include <bits/stdc++.h>
//----------------------------------------------------------------
#include "../Review/BikeReview.h"
#include "../Function/Function.h"
//----------------------------------------------------------------
#define BIKE_REV_FILE "Data/BikeRev.txt"
//----------------------------------------------------------------
std::string static LOCATION[3] = {"HN", "DN", "SG"};
std::string static BIKE_STATUS[2] = {"Available", "Unavailable"};
std::string static MODE[3] = {"Auto", "Manual", "Semi"};
class MotorBike{
   private:
      std::string bikeID;  //auto-generated
      float bikeRating;
      std::vector <BikeReview*> bikeRevVect;
   public:
      std::string model;
      std::string color;
      int engineSize;
      std::string mode;
      std::string yearMade;
      std::string description;
      std::string location;   //limited to 3 locations
      int rentPrice;
      float memRating; 
      //availalbe = when owner list bike for rent
      //unavailable = when owner unlist bike for rent/ bike on rent 
      std::string status; // bike being listed or not (available/unavailable)
      MotorBike();
      MotorBike(std::string i_bikeID, std::string i_model, std::string i_color,
                int i_engineSize, std::string i_mode, std::string i_yearMade,
                float i_bikeRating, int i_rentPrice, std::string i_location,
                float i_memRating, std::string i_status,
                std::string i_description);
      
      void showBikeInfo(); //show bike information
      void bikeratingCal();  //calculate bike rating
      void loadRating();   //get data into vector
      
      friend class System;
};
#endif // MOTORBIKE_H