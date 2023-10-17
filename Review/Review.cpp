#include "Review.h"
Review::Review(float i_score, std::string i_comment) : score(i_score), comment(i_comment){};
float Review::get_score(){
   return this->score;
}
std::string Review::get_comment(){
   return this->comment;
}
      