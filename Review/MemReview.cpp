#include "MemReview.h"
std::string MemRevIDGen(){
   srand(time(NULL));
   int num = rand() % 1001; //random number form 0-100
   return ("RvM-" + std::to_string(num));
}
MemReview::MemReview(std::string i_memReviewID, std::string i_memID, float i_score, std::string i_comment)
    : memReviewID(i_memReviewID), memID(i_memID), Review(i_score, i_comment){};