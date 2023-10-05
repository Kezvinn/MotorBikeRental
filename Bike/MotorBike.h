#ifndef MOTORBIKE_H
#define MOTORBIKE_H
#include <bits/stdc++.h>

class MotorBike{
   private:
      std::string bikeID;  //auto-generated
      float bikeRating;
      std::string comment;
   public:
      std::string model;
      std::string color;
      int engineSize;
      std::string mode;
      std::string yearMade;
      std::string description;
      MotorBike(std::string i_model, std::string i_color, int i_engineSize,
                std::string i_mode, std::string i_yearMade, std::string i_description);
      void showBikeInfo();
};
std::string bikeIDGenerate();

#endif // MOTORBIKE_H