#ifndef MEMRATING_H
#define MEMRATING_H
#include <bits/stdc++.h>
#include "Review.h"
class MemReview : public Review {
   private:
      std::string memReviewID;
      std::string memID;
   public:
      MemReview(std::string i_memReviewID, std::string i_memID, float i_score, std::string i_comment);
};
std::string MemRevIDGen();
#endif