#include "MotorBike.h"
std::string bikeIDGenerate(){
   srand(time(NULL));
   int num = rand() % 1001; //random number form 0-100
   return ("Bk-" + std::to_string(num));
}
MotorBike::MotorBike(){
   std::cout << "Motorbike default constructor" << std::endl;
};
MotorBike::MotorBike(std::string i_bikeID, std::string i_model, std::string i_color,
                     int i_engineSize, std::string i_mode, std::string i_yearMade,
                     float i_bikeRating, int i_rentPrice, std::string i_location,
                     float i_memRating, std::string i_status, int i_rentDuration,
                     std::string i_description)
    : bikeID(i_bikeID), model(i_model), color(i_color),
      engineSize(i_engineSize), mode(i_mode), yearMade(i_yearMade),
      bikeRating(i_bikeRating), rentPrice(i_rentPrice), location(i_location),
      memRating(i_memRating), status(i_status), rentDuration(i_rentDuration),
      description(i_description){};

void MotorBike::showBikeInfo(){  //use to display after user added a new bike
   std::cout << "=====================================================" << std::endl;
   std::cout << "| Model: "  << model << "\t\tColor: " << color << std::right << std::setw(10) << "|" << std::endl;
   std::cout << "| Engine Size: " << engineSize << "\t\tMode: " << mode << std::right << std::setw(10) << "|" << std::endl;
   std::cout << "| Year Made: " << yearMade << "\t\tLocation: " << location << std::right << std::setw(10) << "|" <<std::endl;
   std::cout << "| Rent Price: " << rentPrice << "\t\tBike Rating: " << bikeRating << std::right << std::setw(10) << "|" <<  std::endl;
   std::cout << "| Member Rating: " << memRating << "\t\tStatus: " << status << std::right << std::setw(10) << "|" << std::endl;
   std::cout << "| Description: " << description << std::right << std::setw(10) << "|" << std::endl;
   std::cout << "=====================================================" << std::endl;
}
