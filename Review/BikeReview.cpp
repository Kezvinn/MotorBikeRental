#include "BikeReview.h"
BikeReview::BikeReview(std::string i_bikereviewID, std::string i_bikeID, float i_score, std::string i_comment)
    : bikeReviewID(i_bikereviewID), bikeID(i_bikeID), Review(i_score, i_comment){};

std::string BikeRevIDGen() {
   srand(time(NULL));
   int num = rand() % 1001; // random number form 0-100
   return ("RvB-" + std::to_string(num));
}