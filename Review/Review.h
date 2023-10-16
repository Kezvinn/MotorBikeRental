#ifndef REVIEW_H
#define REVIEW_H
#include <bits/stdc++.h>
class Review{
   private:
      float score;
      std::string comment;
   public:
      Review(float i_score, std::string i_comment);
      friend class MemReview;
      friend class BikeReview;
};
#endif