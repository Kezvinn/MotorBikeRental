#ifndef BIKEREVIEW_H
#define BIKEREVIEW_H

#include <bits/stdc++.h>
#include "Review.h"

class BikeReview : public Review {
   private:
      std::string bikeReviewID;
      std::string bikeID;
   public:
      BikeReview(std::string i_bikeReviewID, std::string i_bikeID, float i_score, std::string i_comment);
      friend class Member;
      void showBikeRev();
      friend class MotorBike;
};
#endif