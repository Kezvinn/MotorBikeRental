#include "Member.h"

std::string memIDGenerate(){
   srand(time(NULL));
   int num = rand() % 1001; //random number form 0-1000
   return ("M-" + std::to_string(num));
}

Member::Member(std::string i_memberID, std::string i_memUsername, std::string i_memPassword,
               std::string i_fullname, std::string i_phoneNumber,
               std::string i_idType, std::string i_idNumber, std::string i_drvNumber,
               std::string i_expDate, float i_memRating, int i_credits,
               std::string i_ownBikeID, std::string i_rentBikeID)
    : memberID(i_memberID), User(i_memUsername, i_memPassword),
      fullName(i_fullname), phoneNumber(i_phoneNumber),
      idType(i_idType), idNumber(i_idNumber), drvNumber(i_drvNumber),
      expDate(i_expDate), memRating(i_memRating), credits(i_credits),
      ownBikeID(i_ownBikeID), rentBikeID(i_rentBikeID) {};
//showInfo
void Member::showMemberInfo(){
   std::cout << "=====================================================" << std::endl;
   std::cout << "- Fullname: " << fullName << "\tPhone#: " << phoneNumber << std::endl;
   std::cout << "- ID type: " << idType << "\tID#: " << idNumber << std::endl;
   std::cout << "- Drv License #: " << drvNumber << "\tExp. date: " << expDate <<std::endl;
   std::cout << "- Rating: " << memRating << "\tCredits: " << credits << std::endl;
   std::cout << "- Own Bike ID: "<< ownBikeID << std::endl;
   std::cout << "=====================================================" << std::endl;
}
//input
void Member::loadRequest(){
   rqstVect.clear();
   std::ifstream file{REQUEST_FILE};
   if(!file) {
      std::cerr << "Couldn't open 'Request.txt' file" << std::endl;
      return;
   }
   std::string line;
   std::vector <std::string> dataList;
   while(std::getline(file, line)){
      dataList = splitString(line,'|');
      Request *rqst = new Request(dataList[0], dataList[1], dataList[2],
                                  dataList[3], dataList[4], 
                                  std::stoi(dataList[5]), dataList[6],dataList[7]);
      rqstVect.push_back(rqst);
   }
}
void Member::loadMemRev(){
   memRevVect.clear();
   std::ifstream file {MEM_REV_FILE};
   if (!file) {
      std::cerr<< "Couldn't open 'MemRev.txt' file." << std::endl;
      return;
   }
   std::string line;
   std::vector <std::string> dataList;
   while(std::getline(file, line)){
      dataList = splitString(line,'|');
      MemReview *rev = new MemReview(dataList[0], dataList[1],
                                     std::stof(dataList[2]),
                                     dataList[3]);
      memRevVect.push_back(rev);
   }
}
//output
void Member::saveRequestToFile(){
   std::ofstream file {REQUEST_FILE};
   if (!file){
      std::cerr << "Couldn't open 'Request.txt'" << std::endl;
   } 
   for(auto rqst : rqstVect){
      file << rqst->requestID << "|"
           << rqst->renterID << "|"
           << rqst->rentbikeID << "|"
           << rqst->startDate << "|"
           << rqst->endDate << "|"
           << rqst->rqst_status << "|"
           << rqst->revStatus
           << std::endl;
   }
   file.close(); 
}
void Member::saveMemRevToFile(){
   std::ofstream file {MEM_REV_FILE};
   if (!file){
      std::cerr << "Couldn't open 'MemRev' file " << std::endl;
   }
   for (auto rev : memRevVect) {
      file << rev->memReviewID << "|"
           << rev->memID << "|"
           << rev->get_score() << "|"
           << rev->get_comment() 
           << std::endl;
   }
   file.close();
   std::cout << "Member Reviews saved successfully" << std::endl;
}
//request actions
void Member::sendRequest(std::string bikeID, int cost){  //create request and send to bike owner
   std::cout << "=====================================================" << std::endl;
   std::cout << "|                REQUEST PREPARATION                |" << std::endl;
   std::cout << "=====================================================" << std::endl;
   std::cin.ignore();
   std::string requestid, renterid, rentbikeid, startdate, enddate, rqststatus,reviewstatus;
   
   requestid = rqstIDGenerate();
   renterid = this->memberID;
   rqststatus = RQST_STATUS[0];  //pending by default
   reviewstatus = REV_STATUS[0]; //not review by default
   rentbikeid = bikeID; 

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

   int total = cost * duration(startdate, enddate);

   std::cout << "=====================================================" << std::endl;
   std::cout << "|                   -CONFIRMATION-                  |" << std::endl;
   std::cout << "=====================================================" << std::endl;
   std::cout << "- Start date:\t" << startdate << std::endl;
   std::cout << "- End date:\t" << enddate << std::endl;
   std::cout << "- Total cost: " << total << " credits." << std::endl;
   std::cout << "=====================================================" << std::endl;

   if (this->credits < total) {
      std::cout << "Current balance: " << this->credits  << " credits"<< std::endl;
      std::cout << "Insufficient credits!" << std::endl;
      topUp();
   }
   this->credits -= total; 
   // this->rentBikeID = bikeID; //record the rent bike id;
   Request *rqst = new Request(requestid, renterid, rentbikeid,
                               startdate, enddate, 
                               total, rqststatus, reviewstatus);
   rqstVect.push_back(rqst);
   saveRequestToFile(); // save to txt file

   std::cout << "=====================================================" << std::endl;
   std::cout << "|              REQUEST SENT SUCCESSFULLY            |" << std::endl;
   std::cout << "=====================================================" << std::endl;
}
void Member::viewRequest(){   //view and take action upon requests
   //delete request if overtime 
   for (int i = 0; i < rqstVect.size(); i++) {
      if ((duration(TODAY_DATE, rqstVect[i]->startDate) <= 0) && rqstVect[i]->rqst_status == RQST_STATUS[0]){
         rqstVect.erase(rqstVect.begin()+i);
      }
   }

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
      if (rqst->rentbikeID == this->ownBikeID && rqst->rqst_status == RQST_STATUS[0]){ // check if bike belong to user
         std::cout << std::setw(4) << order
                  << std::setw(17) << rqst->renterID
                  << std::setw(20) << rqst->startDate
                  << std::setw(17) << rqst->endDate
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
   int choice3;
   switch (choice) {
   case 1:
      choice2 = menuChoice(0, order, track); // request want to action
      std::cout << "Action:\t1. Accept\t2. Decline" << std::endl;
      choice3 = menuChoice(1,2);
      if (choice3 == 1){
         rqstVect[choice2]->rqst_status = RQST_STATUS[1];   //accepted
      } else if (choice3 == 2){
         rqstVect[choice2]->rqst_status = RQST_STATUS[2];   //declined
      }

      std::cout << "=====================================================" << std::endl;
      std::cout << "|                     -COMPLETED-                   |" << std::endl;
      std::cout << "=====================================================" << std::endl;
      saveRequestToFile(); //save request to file
      break;   
   case 2:  //return to member menu
      break;
   }
}
bool Member::requestCheck () {   //check status and update rentbikeID to current member
   for (auto rqst :rqstVect) {
      if (rqst->renterID == this->memberID){ //if current memmber is the one who sent the request
         if (rqst->rqst_status == RQST_STATUS[0]){ //pending
         this->rentBikeID = "null";
         return false;
         }
         if (rqst->rqst_status == RQST_STATUS[1]){ //accepted
            if (rqst->startDate == TODAY_DATE) {
               this->rentBikeID = rqst->rentbikeID;
            }
            else {
               this->rentBikeID = "null";
            }
         }
         if (rqst->rqst_status == RQST_STATUS[2]){ //declined
            this->credits += rqst->totalCost;   //
            return false;
         }
      }
   }
      
   //check sent requests status? base on renter == current member iD
      //if accept and startdaty == today -> save bikeID to rentbikeID
      //if declined -> add back the money
      //if pendinng -> do nothing -> 'null'
   return true;   //accepted
}
//add credits into account
void Member::topUp(){ //add credits into account
   std::cout << "=====================================================" << std::endl;
   std::cout << "|                      TOP-UP                       |" << std::endl;
   std::cout << "=====================================================" << std::endl;
   std::string in_credits;
   do {
      std::cout << "Format: only interger number allowed" << std::endl;
      std::cout << "Enter credits to add: ";
      std::getline(std::cin, in_credits);
      std::cout << "=====================================================" << std::endl;
   } while (!numValid(in_credits));

   std::string pass;
   std::cout << "Enter your password: ";
   std::getline(std::cin, pass);
   if (pass == this->get_password()) {
      this->credits += std::stoi(in_credits);
      std::cout << "Correct password. Credits added successfully." << std::endl;
   }
}
//return rent duration to be save in bike info
int Member::rentDuration(){   //check status and return the duration 
   for (auto rqst : rqstVect) {
      if (rqst->renterID == this->memberID && rqst->rqst_status == RQST_STATUS[1]) {   //accepted
         this->rentBikeID = rqst->rentbikeID;   // set rentbikeID
         return duration (rqst->startDate, rqst->endDate);  // return duration
      }
   }
   return 0;
}
//comment and rate renter
void Member::reviewMember(std::string renterID){
   std::cout << "=====================================================" << std::endl;
   std::cout << "|                   -MEMBER REVIEW-                 |" << std::endl;
   std::cout << "=====================================================" << std::endl;
   std::cin.ignore();

   std::vector<int> track;
   std::string reviewID, comment, rating;   //completed
   do {
      std::cout << "Format: comment no special character." << std::endl;
      std::cout << "Enter your comment: ";
      std::getline(std::cin, comment);
   } while (!isComment(comment)); // char, num, special character allowed
   do
   {
      std::cout << "Format: Only number (1-10)." << std::endl;
      std::cout << "Enter your rating: ";
      std::getline(std::cin, rating);
   } while (!isFloat(rating, 1.0, 10.0)); // 1-10 float
   reviewID = MemRevIDGen();              // gen new review ID
   MemReview *review = new MemReview(reviewID, renterID,
                          std::stof(rating),
                          comment);
   memRevVect.push_back(review);
   this->memRating = memRatingCal(); // calculate new rating for member
   
   review->showMemRev();

   //change status of review
   for (auto rqst : rqstVect) {  
      if (rqst->renterID == renterID) {
         rqst->revStatus = REV_STATUS[1];
      }
   }   
   std::cout << "=====================================================" << std::endl;
   std::cout << "|             -THANK YOU FOR YOUR REVIEW-           |" << std::endl;
   std::cout << "=====================================================" << std::endl;
}
//calculate average rating base on the customer review
float Member::memRatingCal(){
   float total;
   for (int i = 0; i < memRevVect.size(); i++) {
      total += memRevVect[i]->get_score();
   }
   return total/memRevVect.size();
}

std::vector<std::string> Member::getRenter(std::vector<std::string> &storage){
   for (auto rqst : rqstVect) {
      if(rqst->rentbikeID == this->ownBikeID){  // if bike belong to current member
            if ((rqst->rqst_status == RQST_STATUS[1]) && (duration(TODAY_DATE, rqst->endDate) <= 0)) {                                        // check status == accepted, enddate == today
               if (rqst->revStatus == REV_STATUS[0]){   //review status == not review
                  storage.push_back(rqst->renterID);
               }
            }
      } 
   }
   return storage;
}