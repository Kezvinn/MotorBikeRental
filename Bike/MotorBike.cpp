#include "MotorBike.h"
std::string bikeIDGenerate(){
   srand(time(NULL));
   int num = rand() % 1001; //random number form 0-100
   return ("Bk-" + std::to_string(num));
}
MotorBike::MotorBike(std::string i_model, std::string i_color, int i_engineSize,
                     std::string i_mode, std::string i_yearMade, std::string i_description)
    : model(i_model), color(i_color), engineSize(i_engineSize),
      mode(i_mode), yearMade(i_yearMade), description(i_description){};

void MotorBike::showBikeInfo(){
   std::cout << "=============================================" << std::endl;
   std::cout << "Model: "  << model << "\tColor: " << color << std::endl;
   std::cout << "Engine Size: " << engineSize << "\tMode: " << mode << std::endl;
   std::cout << "Year Made: " << yearMade << std::endl;
   std::cout << "Description: " << description << std::endl;
   std::cout << "Rating: " <<bikeRating << "\tComment: " << comment << std::endl;
}
