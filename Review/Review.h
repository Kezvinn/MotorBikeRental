#ifndef REVIEW_H
#define REVIEW_H
#include <bits/stdc++.h>
class Review{
   private:
      float score;
      std::string comment;
   public:
      Review(float i_score, std::string i_comment);
      float get_score();
      std::string get_comment();
      // friend class BikeReview;
      // friend class MemReview;
};
#endif