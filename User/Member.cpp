#include "Member.h"

std::string memIDGenerate(){
   srand(time(NULL));
   int num = rand() % 1001; //random number form 0-1000
   return ("M-" + std::to_string(num));
}

Member::Member(){
   std::cout << "Member default constructor" << std::endl;
};
Member::Member(std::string i_memberID, std::string i_memUsername, std::string i_memPassword,
               std::string i_fullname, std::string i_phoneNumber,
               std::string i_idType, std::string i_idNumber, std::string i_drvNumber,
               std::string i_expDate, float i_memRating, int i_credits,
               bool i_ownBike, std::string i_ownBikeID, std::string i_rentBikeID)
    : memberID(i_memberID), User(i_memUsername, i_memPassword),
      fullName(i_fullname), phoneNumber(i_phoneNumber),
      idType(i_idType), idNumber(i_idNumber), drvNumber(i_drvNumber),
      expDate(i_expDate), memRating(i_memRating), credits(i_credits),
      ownBike(i_ownBike), ownBikeID(i_ownBikeID), rentBikeID(i_rentBikeID) {};

void Member::showMemberInfo(){
   std::cout << "=====================================================" << std::endl;
   std::cout << "Fullname: " << fullName << "\tPhone#: " << phoneNumber << std::endl;
   std::cout << "ID type: " << idType << "\tID#: " << idNumber << std::endl;
   std::cout << "Drv License #: " << drvNumber << "\tExp. date: " << expDate <<std::endl;
   std::cout << "Rating: " << memRating << "\tCredits: " << credits << std::endl;
   if(ownBike == true) {
      std::cout << "Own bike: true" << "\tBike ID: "<< ownBikeID << std::endl;
   } else {
      std::cout << "Own bike: false" << "\tBike ID: "<< ownBikeID << std::endl;
   }
   // std::cout << "Own bike ID: " << ownBikeID << std::endl;
   std::cout << "=====================================================" << std::endl;
}

void Member::sendRequest(){
   std::cout << "=====================================================" << std::endl;
   std::cout << "|                REQUEST PREPARATION                |" << std::endl;
   std::cout << "=====================================================" << std::endl;
   std::cin.ignore();
   std::string requestid, renterid, rentbikeid, startdate, enddate, rqststatus;
   
   requestid = rqstIDGenerate();
   renterid = this->memberID;
   rqststatus = RQST_STATUS[0];  //pending by default
   rentbikeid = this->rentBikeID;
   do{
      do {
         std::cout << "Format: DD/MM/YYYY" << std::endl;
         std::cout << "Enter start date: ";
         std::getline(std::cin, startdate);
         std::cout << "=====================================================" << std::endl;
      } while(!isDateFormat(startdate));
      do {
         std::cout << "Format: DD/MM/YYYY" << std::endl;
         std::cout << "Enter return date: ";
         std::getline(std::cin,enddate);
         std::cout << "=====================================================" << std::endl;
      } while (!isDateFormat(enddate));
      if(duration(startdate,enddate) < 0){
         std::cerr << "Error: Invalid date input (End date < Start date)." << std::endl;
         std::cout << "=====================================================" << std::endl;
      }
   } while(duration(startdate,enddate) < 0); //end date > start date

   Request *rqst = new Request(requestid, renterid, rentbikeid,
                               startdate, enddate, rqststatus);
   rqstVect.push_back(rqst);
   
   std::cout << "=====================================================" << std::endl;
   std::cout << "|              REQUEST SEND SUCCESSFULLY            |" << std::endl;
   std::cout << "=====================================================" << std::endl;
}
void Member::loadRequest(){
   rqstVect.clear();
   std::ifstream file{REQUEST_FILE};
   if(!file) {
      std::cerr << "Couldn't open 'Request.txt' file" << std::endl;
   }
   std::string line;
   std::vector <std::string> dataList;
   while(std::getline(file, line)){
      dataList = splitString(line,'|');
      Request *rqst = new Request(dataList[0], dataList[1], dataList[2],
                                  dataList[3], dataList[4], dataList[5]);
      rqstVect.push_back(rqst);
   }
}
void Member::viewRequest(){
   int index = 0, order = 0;
   std::vector<int> track;
   std::cout << "=====================================================" << std::endl;
   std::cout << std::setw(7) << "-Index-"
             << std::setw(17) << "-Renter ID-"
             << std::setw(18) << "-Start date-"
             << std::setw(16) << "-End date-"
             << std::setw(14) << "-Status-"
             << std::endl;
   for (auto rqst : rqstVect){
      if (this->ownBikeID == rqst->rentbikeID){ // check if bike belong to user
         std::cout << std::setw(7) << order
                   << std::setw(17) << rqst->renterID
                   << std::setw(18) << rqst->startDate
                   << std::setw(16) << rqst->endDate
                   << std::setw(14) << rqst->rqst_status
                   << std::endl;
         order++;
         track.push_back(index);
      }
      index++;
   }
   std::cout << "=====================================================" << std::endl;
   std::cout << "Continue? " << std::endl;
   std::cout << "1. Choose request to action." << std::endl;
   std::cout << "2. Return to Member Menu." << std::endl;
   int choice = menuChoice(1,2);
   int choice2;
   switch (choice) {
   case 1:
      choice2 = menuChoice(0,order,track);
      
      break;   
   case 2:
      break;
   }
}

void Member::saveRequestToFile(){

}
void Member::topUp(){
   std::cout << "=====================================================" << std::endl;
   std::cout << "|                      TOP-UP                       |" << std::endl;
   std::cout << "=====================================================" << std::endl;
   std::cin.ignore();
   std::string in_credits;
   do {
      std::cout << "Format: only interger number allowed" << std::endl;
      std::cout << "Enter credits to add: ";
      std::getline(std::cin, in_credits);
      std::cout << "=====================================================" << std::endl;
   } while (!numValid(in_credits));
   
   this->credits += std::stoi(in_credits);   //add credit to member

}