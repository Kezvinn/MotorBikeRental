#include "BikeReview.h"

BikeReview::BikeReview(std::string i_bikereviewID, std::string i_bikeID, float i_score, std::string i_comment)
    : bikeReviewID(i_bikereviewID), bikeID(i_bikeID), Review(i_score, i_comment){};

void BikeReview::showBikeRev(){
   std::cout << "=====================================================" << std::endl;
   std::cout << "- Review ID: " << bikeReviewID << std::endl;
   std::cout << "- Bike ID: " << bikeID << std::endl;
   std::cout << "- Score: " << get_score() << std::endl;
   std::cout << "- Comment: " << get_comment() << std::endl;
   std::cout << "=====================================================" << std::endl;
}