#include "MotorBike.h"

MotorBike::MotorBike(){
   std::cout << "Motorbike default constructor" << std::endl;
};
MotorBike::MotorBike(std::string i_bikeID, std::string i_model, std::string i_color,
                     int i_engineSize, std::string i_mode, std::string i_yearMade,
                     float i_bikeRating, int i_rentPrice, std::string i_location,
                     float i_memRating, std::string i_status, std::string i_starttime, std::string i_endtime,
                     std::string i_description)
    : bikeID(i_bikeID), model(i_model), color(i_color),
      engineSize(i_engineSize), mode(i_mode), yearMade(i_yearMade),
      bikeRating(i_bikeRating), rentPrice(i_rentPrice), location(i_location),
      memRating(i_memRating), status(i_status), startTime(i_starttime), endTime(i_endtime),
      description(i_description){};

void MotorBike::showBikeInfo(){  //use to display after user added a new bike
   std::cout << "=====================================================" << std::endl;
   std::cout << "- Model: "  << model << "\t\tColor: " << color << std::endl;
   std::cout << "- Engine Size: " << engineSize << " cc\t\tMode: " << mode << std::endl;
   std::cout << "- Year Made: " << yearMade << "\t\tLocation: " << location << std::endl;
   std::cout << "- Rent Price: " << rentPrice << " credits\t\tBike Rating: " << bikeRating << "/10"<<  std::endl;
   std::cout << "- Member Rating: " << memRating << "/10\t\tStatus: " << status << std::endl;
   std::cout << "- Start date: " << startTime << "\t\tEnd date: " << endTime << std::endl;
   std::cout << "- Description: " << description << std::endl;
   std::cout << "=====================================================" << std::endl;
}

void MotorBike::bikeratingCal(){
   loadRating();  //load input
   float total = this->bikeRating;  //current rating of bike
   int count = 0;
   for (auto rev : bikeRevVect) {
      if(rev->bikeID == this->bikeID){
         total += rev->get_score();
         count++;
      }
   }
   this->bikeRating = total/(count+1);
}

void MotorBike::loadRating (){
   bikeRevVect.clear();
   std::ifstream file {BIKE_REV_FILE};
   if (!file) {
      std::cerr<< "Couldn't open 'BikeRev.txt' file." << std::endl;
      return;
   }
   std::string line;
   std::vector <std::string> dataList;
   while(std::getline(file, line)){
      dataList = splitString(line, '|');
      BikeReview *rev = new BikeReview(dataList[0], dataList[1],
                                       std::stof(dataList[2]),
                                       dataList[3]);
      bikeRevVect.push_back(rev);
   }
   // std::cout << "'BikeRev.txt' in bike loaded." << std::endl;
}