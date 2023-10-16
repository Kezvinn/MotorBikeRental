#include "System.h"

System::System(){
   // std::cout << "Default System Configuration" << std::endl;
};
void System::mainMenu(){
   std::cout << "=====================================================" << std::endl;
   std::cout << "|             MOTORBIKE RENTAL APPLICATION          |" << std::endl;
   std::cout << "=====================================================" << std::endl;
   
   std::cout << "Creator: Nhat Nguyen" << std::endl;
   std::cout << "Use the app as:" << std::endl; 
   std::cout << "1. Guest\t2. Member\t3. Admin" << std::endl; 
   int choice = menuChoice(1,3);
   switch (choice){
      case 1:
         guestMenu();
         break;
      case 2:
         memberLoginMenu();
         break;
      case 3:
         adminLoginMenu();
         break;
      case 4: 
         std::cout << "=====================================================" << std::endl;
         std::cout << "|                THANK YOU FOR USING!               |" << std::endl;
         std::cout << "=====================================================" << std::endl;
   
   }
}

void System::guestMenu(){
   std::cout << "=====================================================" << std::endl;
   std::cout << "|                    -GUEST MENU-                   |" << std::endl;
   std::cout << "=====================================================" << std::endl;

   loadMembers();
   loadBikes();
   // loadAdmin();
   std::cout << "1. View motorbike\n";
   std::cout << "2. Sign up\n";
   std::cout << "3. Return to main menu\n";
   int choice = menuChoice(1,3);
   // std::cin.ignore(0,' ');
   switch (choice){
      case 1:
         guestViewBikes();
         break;
      case 2:
         guestRegister();
         // saveMemberToFile();
         break;
      case 3:
         mainMenu();
         saveMemberToFile();
         saveBikesToFile();
         std::cout << "=====================================================" << std::endl;
         std::cout << "|                 -THANK YOU FOR USING-             |" << std::endl;
         std::cout << "=====================================================" << std::endl;
         break;
   }
}
void System::memberLoginMenu(){
   std::string username, password;
   std::cout << "=====================================================" << std::endl;
   std::cout << "|                 -MEMBER LOGIN MENU-               |" << std::endl;
   std::cout << "=====================================================" << std::endl;   
   std::cout << "1. Member Login" <<std::endl;
   std::cout << "2. Back to main menu" << std::endl;
   loadMembers();
   loadBikes();
   // loadAdmin();
   int choice;
   choice = menuChoice(1,2);
   switch (choice) {
   case 1:
      loadMembers();
      std::cout << "Enter Username: ";
      std::cin >> username;
      std::cin.ignore(0,' ');
      std::cout << "Enter Password: ";
      std::cin >> password;
      if (memberLogin(username, password)) { //if true -> login successfully
         std::cout << "Login successfully" << std::endl;
         memberMenu();
         break;
      } else {
         std::cout << "Login Failed! Wrong username or password." << std::endl;
      }
   case 2:
      mainMenu();
      break;
   }
}
void System::adminLoginMenu(){
 std::string username, password;
   std::cout << "=====================================================" << std::endl;
   std::cout << "|                 -ADMIN LOGIN MENU-                |" << std::endl;
   std::cout << "=====================================================" << std::endl;
   std::cout << "1. Admin Login" << std::endl;
   std::cout << "2. Back to main menu" << std::endl;
   // loadMembers();
   // loadBikes();
   // loadAdmin();
   int choice;
   choice = menuChoice(1,2);
   switch (choice) {
   case 1:
      loadAdmin();   
      std::cout << "Enter Username: ";
      // std::getline(std::cin, username);
      std::cin >> username;
      std::cin.ignore(0,' ');
      std::cout << "Enter Password: ";
      std::cin >> password;
      // std::getline(std::cin, password);
      if (adminLogin(username,password)) {
         std::cout << "Login successfully!" <<std::endl;
         adminMenu();
         break;
      } 
      else {
         std::cout << "Login failed! Wrong username or password!" <<std::endl;
      }
   case 2:
      mainMenu(); 
      break;
   }
}

bool System::adminLogin(std::string username, std::string password){
   if (username == this->admin->username && password == this->admin->password){
      return true;
   } else {
      return false;
   }
}
bool System::memberLogin(std::string username, std::string password){
   for(Member *mem : memberVect){
      if (username == mem->username && password == mem->password){
         currentMember = mem;
         return true;
      }
   }
   return false;
}

void System::adminMenu(){
   std::cout << "=====================================================" << std::endl;
   std::cout << "|                     -ADMIN MENU-                  |" << std::endl;
   std::cout << "=====================================================" << std::endl;

   std::cout << "1. View all members" <<std::endl; 
   std::cout << "2. View all motorbikes" <<std::endl;
   std::cout << "3. Logout" << std::endl;
   // loadMembers();
   // loadBikes();
   // loadAdmin();
   int choice = menuChoice(1,3);
   switch (choice) {
   case 1:
      adminViewMembers();   
      break;
   case 2:
      adminViewBikes();
      break;
   case 3:
      std::cout << "=====================================================" << std::endl;
      std::cout << "|                -LOGOUT SUCCESSFULLY-              |" << std::endl;
      std::cout << "=====================================================" << std::endl;

      break;
   }
}
void System::memberMenu(){
   currentMember->loadRequest();
   for (auto bike : bikeVect) {
      if (bike->bikeID == currentMember->rentBikeID) {
         bike->rentDuration = currentMember->requestCheck(); // check if the request send already processed
      }
   }
   std::cout << "=====================================================" << std::endl;
   std::cout << "|                    -MEMBER MENU-                  |" << std::endl;
   std::cout << "=====================================================" << std::endl;
   std::cout << "1. Rent Motorbikes" << std::endl; //view bike to rent
   std::cout << "2. Add motorbike" << std::endl;   // addbike to member
   std::cout << "3. List/Unlist motorbikes" << std::endl; //list or unlist motorbikes
   std::cout << "4. View Request" << std::endl; //view upcoming requests
   std::cout << "5. View History" << std::endl; //view history of bike or member
   std::cout << "6. Logout" << std::endl;
   int choice = menuChoice(1,6);
   switch (choice) {
   case 1:
      rentMenu();
      break;
   case 2:
      //add bike
      checkOwnBike();   //check if already have bike then action;
      break;
   case 3:  
      //list/unlist bike
      listBike();
      break;
   case 4:  
      //view request
      currentMember->viewRequest(); 
      memberMenu();
      break;
   case 5:
      //view history
      break;
   case 6:
      saveMemberToFile();
      saveBikesToFile();
      std::cout << "=====================================================" << std::endl;
      std::cout << "|               -THANK YOU FOR USING-               |" << std::endl;
      std::cout << "=====================================================" << std::endl;
      break;
   }
}

void System::loadMembers(){
   memberVect.clear();
   std::string line;
   std::ifstream file{MEMBER_FILE}; 
   if(!file.is_open()){
      std::cerr << "Couldn't open 'Member.txt'" << std::endl;
      // return;
   }
   while (std::getline(file, line)){      
      std::vector<std::string> dataList;
      dataList = splitString (line, '|');

      Member *member = new Member(dataList[0], dataList[1], dataList[2],
                                  dataList[3], dataList[4],
                                  dataList[5], dataList[6], dataList[7],
                                  dataList[8], std::stof(dataList[9]), std::stoi(dataList[10]),
                                  dataList[11], dataList[12]); // add attributes
      memberVect.push_back(member);
   }
   file.close();  
   // std::cout << "Member file loaded" << std::endl;
}
void System::loadBikes(){
   bikeVect.clear();
   std::string line;
   std::ifstream file{BIKE_FILE}; 
   if(!file.is_open()){
      std::cerr << "Couldn't open 'Bike.txt'" << std::endl;
      // return;
   }
   while (std::getline(file, line)){      
      std::vector<std::string> dataList;
      dataList = splitString (line, '|');

      MotorBike *bike = new MotorBike(dataList[0], dataList[1], dataList[2],
                                      std::stoi(dataList[3]), dataList[4], dataList[5],
                                      std::stof(dataList[6]), std::stoi(dataList[7]), dataList[8],
                                      std::stof(dataList[9]), dataList[10], std::stoi(dataList[11]),
                                      dataList[12]);
      bikeVect.push_back(bike);
   }
   file.close();  
   // std::cout << "Bike file loaded" << std::endl;
}
void System::loadAdmin(){
   std::ifstream file{ADMIN_FILE};
   if (!file) {
      std::cerr << "Cant open file 'Admin.txt'" << std::endl;
      // return;
   }
   std::string line;
   getline(file, line);
   std::vector<std::string> dataList = splitString(line, '|');

   std::string username = dataList[0];
   std::string password = dataList[1];
   
   this->admin = new Admin(username, password);

   // std::cout << "Admin file loaded" << std::endl;
   file.close();
}

void System::saveBikesToFile(){
   if (currentBike != nullptr){
      for(auto b : bikeVect) {
         if (currentBike->bikeID == b->bikeID) {
            b = currentBike;
         }
      }
   }
   std::ofstream file {BIKE_FILE};
   if (!file ){
      std::cerr << "Couldn't open motorbike file" << std::endl;
      return;
   }
   for(auto bike : bikeVect){
      file << bike->bikeID << "|" << bike->model << "|"
           << bike->color << "|" << bike->engineSize << "|"
           << bike->mode << "|" << bike->yearMade << "|"
           << bike->bikeRating << "|" << bike->rentPrice << "|"
           << bike->location << "|" << bike->memRating << "|"
           << bike->status << "|" << bike->rentDuration << "|"
           << bike->description << std::endl;
   }
   file.close();
   // std::cout << "Motorbike file saved successfully!" << std::endl;
}
void System::saveMemberToFile(){
   if (currentMember != nullptr){
      for(auto m : memberVect) {
         if (currentMember->memberID == m->memberID) {
            m = currentMember;
         }
      }
   }
   std::ofstream file{MEMBER_FILE};
   if (!file){
      std::cerr<< "Couln't open member file" <<std::endl;
      return;
   }
   for (auto mem : memberVect) {
      file << mem->memberID << "|" << mem->username << "|"
           << mem->password << "|" << mem->fullName << "|"
           << mem->phoneNumber << "|" << mem->idType << "|"
           << mem->idNumber << "|" << mem->drvNumber << "|"
           << mem->expDate << "|" << mem->memRating << "|"
           << mem->credits << "|" << mem->ownBikeID << "|"
           << mem->rentBikeID;
      // if (currentMember != nullptr) {  //for members
      //    if (mem->memberID == currentMember->memberID) {
      //       if(currentMember->ownBikeID == "null") {
      //          file << "|null";
      //       } else {
      //          file << "|" << currentMember->ownBikeID;
      //       }
      //    } else {
      //       file << "|" << mem->ownBikeID << "|" << mem->rentBikeID;
      //    }
      // } 
      // else { //new register
      //    file << "|" << mem->ownBikeID << "|" << mem->rentBikeID;
      // }
      file << "\n";
   }
   file.close();
   // std::cout << "Members file saved successfully!" << std::endl;
}

void System::guestViewBikes(){
   int index = 1;
   std::cout << "Motorbikes in the System" <<std::endl;
   std::cout << std::left << std::setw(10) << "-Index- "
             << std::left << std::setw(15) << "-Model-"
             << std::left << std::setw(15) << "-Color-"
             << std::left << std::setw(20) << "-Engine Size-"
             << std::left << std::setw(15) << "-Year Made-"
             << std::left << std::setw(15) << "-Mode-"
             << std::left << std::setw(15) << "-Location-"
             << std::left << std::setw(15) << "-Rent Price-"
             << std::endl;
   for(auto bike: bikeVect){
      std::cout << std::left << std::setw(10) << index
                << std::left << std::setw(15) << bike->model
                << std::left << std::setw(15) << bike->color
                << std::left << std::setw(20) << bike->engineSize
                << std::left << std::setw(15) << bike->yearMade
                << std::left << std::setw(15) << bike->mode
                << std::left << std::setw(15) << bike->location
                << std::left << std::setw(15) << bike->rentPrice
                << std::endl;
      index++;
   }
   std::cout << "Continue" << std::endl;
   std::cout << "1. Sign up." << std::endl;
   std::cout << "2. Return to Guest Menu." << std::endl;
   int choice = menuChoice(1,3);
   switch (choice){
   case 1:
      guestRegister();
      break;
   case 2:
      guestMenu();
      break;
   }
}
void System::guestRegister(){
   std::string memID, username, password,
       fullname, phonenumber,
       idtype, idnumber, drivernumber,
       exptdate, ownbikeid = "null", rentbikeid = "null";
   float memrating = INITIAL_MEM_RATING;
   int credits = INITIAL_CREDITS;
   std::cout << "=====================================================" << std::endl;
   std::cout << "|                 -MEMBER REGISTRATION-             |" <<std::endl;
   std::cout << "=====================================================" << std::endl;
   // std::cin.ignore(0,' ');
   std::cin.ignore();
   do{
      std::cout << "Format: 6 char minimum. No whitespaces. No symbols (&=_'-+,<>.)" << std::endl;
      std::cout << "1. Enter your username: ";
      std::getline(std::cin, username);
      std::cout << "=====================================================" << std::endl;
   }while (!isUsername(username));
   
   do {
      std::cout << "Format: length of 8 - 15. Included: one Uppercase. one Number, one Special Character" <<std::endl;
      std::cout << "2. Enter your password: ";
      std::getline(std::cin, password);
      std::cout << "=====================================================" << std::endl;
   } while (!isPassword(password));
   
   do {
      std::cout << "Format: no symbols, no numbers" << std::endl;
      std::cout << "3. Enter your fullname: " ;
      std::getline(std::cin, fullname);
      std::cout << "=====================================================" << std::endl;
   } while (!isFullname(fullname));

   do {
      std::cout << "Format: 10 numbers, no characters, no symbols" << std::endl;
      std::cout << "4. Enter your phonenumber: ";
      std::getline(std::cin, phonenumber);
      std::cout << "=====================================================" << std::endl;
   } while (!isPhoneNum(phonenumber));
   
   std::cout << "5. Choose your ID type: 1. CitizenID\t2. PassportID" <<std::endl;
   int choice1 = menuChoice(1,2);
   std::cout << "=====================================================" << std::endl;
   switch (choice1) {
   case 1:
      idtype = ID_TYPE[0]; //citizens ID 12
      std::cin.ignore();
      do {
         std::cout << "Format: 12 numbers, no characters, no symbols" << std::endl;
         std::cout << "6. Enter your ID#: " ;
         std::getline(std::cin, idnumber);
         std::cout << "=====================================================" << std::endl;
      } while (!isIDValid(idnumber,1));
      break;
   case 2:
      idtype = ID_TYPE[1];    //passport ID 8
      std::cin.ignore();
      do {
         std::cout << "Format: 8 numbers, no characters, no symbols" << std::endl;
         std::cout << "6. Enter your ID#: " ;
         std::getline(std::cin, idnumber);
         std::cout << "=====================================================" << std::endl;
      } while (!isIDValid(idnumber,2));
      break;
   }
   do {
      std::cout << "Format: 12 numbers, no characters, no symbols" << std::endl;
      std::cout << "7. Enter your driver license ID: ";
      std::getline(std::cin, drivernumber);
      std::cout << "=====================================================" << std::endl;
   } while (!isLicence(drivernumber));

   do {
      std::cout << "Format: DD/MM/YYYY" << std::endl;
      std::cout << "8. Enter license expiration date: ";
      std::getline(std::cin, exptdate);
      std::cout << "=====================================================" << std::endl;
   } while (!isDateFormat(exptdate));
   memID = memIDGenerate();
   Member *mem = new Member(memID, username, password,
                            fullname, phonenumber,
                            idtype, idnumber, drivernumber,
                            exptdate, memrating, credits,
                            ownbikeid, rentbikeid);
   memberVect.push_back(mem);
   saveMemberToFile();
   std::cout << "=====================================================" << std::endl;
   std::cout << "|               -REGISTER SUCCESSFULLY-             |" << std::endl;
   std::cout << "=====================================================" << std::endl;
   mem->showMemberInfo();  //show member information

}

void System::adminViewBikes(){
   loadBikes();
   int index = 1;
   std::cout << "Motorbikes in the System" << std::endl;
   std::cout << "======================================================================================================================================================================" << std::endl;
   std::cout << std::setw(7) << "-Index-" << std::setw(15) << "-Bike ID-"
             << std::setw(13) << "-Model-" << std::setw(13) << "-Color-"
             << std::setw(16) << "-Year Made-" << std::setw(12) << "-Mode-"
             << std::setw(16) << "-Location-" << std::setw(15) << "-Credits-"
             << std::setw(19) << "-Bike Rating-" << std::setw(21) << "-Member Rating-"
             << std::setw(18) << "-Descripton-" << std::endl;
   for (auto bike : bikeVect) {
      std::cout << std::setw(4) << index << std::setw(16) << bike->bikeID
                << std::setw(14) << bike->model << std::setw(13) << bike->color
                << std::setw(13) << bike->yearMade << std::setw(15) << bike->mode
                << std::setw(13) << bike->location << std::setw(15) << bike->rentPrice
                << std::setw(17) << bike->bikeRating << std::setw(21) << bike->memRating
                << std::setw(21) << bike->description << std::endl;
      index++;
   }
   std::cout << "======================================================================================================================================================================" << std::endl;
   std::cout << "Total Motorbikes: " << bikeVect.size() << std::endl;
   std::cout << std::endl;
   std::cout << "Continue?" << std::endl;
   std::cout << "1. Return to Admin Menu."  << std::endl;
   std::cout << "2. Logout Admin." << std::endl;
   int choice = menuChoice(1,2);
   switch (choice){
      case 1:
         adminMenu();
         break;
      case 2:
         std::cout << "=====================================================" << std::endl;
         std::cout << "|                -LOGOUT SUCCESSFULLY-              |" << std::endl;
         std::cout << "=====================================================" << std::endl;
         break;
   }
}
void System::adminViewMembers(){
   int index = 1;
   loadMembers();
   std::cout << "Member in the system: "<<std::endl;
   std::cout << "===============================================================================================================================================================" << std::endl;
   std::cout << std::setw(7) << "-Index-" << std::setw(17) << "-Member_ID-"
             << std::setw(16) << "-Username-" << std::setw(16) << "-Password-"
             << std::setw(17) << "-Full Name-" << std::setw(15) << "-Phone #-"
             << std::setw(15) << "-ID Type-" << std::setw(18) << "-ID Number#-"
             << std::setw(15) << "-Credits-" << std::setw(14) << "-Rating-" 
             << std::endl;
   for (auto mem : memberVect) {
      std::cout << std::setw(4) << index << std::setw(17) << mem->memberID
                  << std::setw(16) << mem->username << std::setw(18) << mem->password
                  << std::setw(19) << mem->fullName << std::setw(15) << mem->phoneNumber
                  << std::setw(14) << mem->idType << std::setw(18) << mem->idNumber
                  << std::setw(11) << mem->credits << std::setw(16) << mem->memRating
                  << std::endl;
      index++;
   }
   std::cout << "===============================================================================================================================================================" << std::endl;
   std::cout << "Total members: " << memberVect.size() << std::endl;
   std::cout << std::endl;
   std::cout << "Continue?" << std::endl;
   std::cout << "1. Return to Admin Menu" << std::endl;
   std::cout << "2. Logout Admin" << std::endl;
   int choice = menuChoice(1,2);
   switch (choice){
      case 1:
         adminMenu();
         break;
      case 2:
         std::cout << "=====================================================" << std::endl;
         std::cout << "|                -LOGOUT SUCCESSFULLY-              |" << std::endl;
         std::cout << "=====================================================" << std::endl;
         break;
   }
}

void System::rentMenu(){
   std::cout << "=====================================================" << std::endl;
   std::cout << "|                     -RENT MENU-                   |" << std::endl;
   std::cout << "=====================================================" << std::endl;
   std::cout << "Choose your location:\t1. Hanoi\t2. Danang\t3. Saigon\n";
   int index = 0; // for keep track index in vector
   int order = 0; // for display
   std::vector<int> track;
   int choice = menuChoice(1,3);
   std::cout << "=====================================================" << std::endl;
   std::cout << std::setw(7) << "-Index-" << std::setw(15) << "-Bike ID-"
             << std::setw(13) << "-Model-" << std::setw(13) << "-Color-"
             << std::setw(16) << "-Year Made-" << std::setw(12) << "-Mode-"
             << std::setw(16) << "-Location-" << std::setw(15) << "-Credits-"
             << std::setw(19) << "-Bike Rating-" << std::setw(21) << "-Member Rating-"
             << std::setw(18) << "-Descripton-" << std::endl;
   switch (choice) {
      case 1:
         for(MotorBike *bike: bikeVect){
         if (bike->location == LOCATION[0] && bike->status == BIKE_STATUS[0] &&
             bike->bikeID != currentMember->ownBikeID && bike->memRating <= currentMember->memRating) { // HN/Available/not own bike/ qualify with rating
            std::cout << std::setw(4) << order << std::setw(16) << bike->bikeID
                << std::setw(14) << bike->model << std::setw(13) << bike->color
                << std::setw(13) << bike->yearMade << std::setw(15) << bike->mode
                << std::setw(13) << bike->location << std::setw(15) << bike->rentPrice
                << std::setw(17) << bike->bikeRating << std::setw(21) << bike->memRating
                << std::setw(21) << bike->description << std::endl;
            order++;
            track.push_back(index);
         }
         index++;
         }
         std::cout << "=====================================================" << std::endl;
         break;
      case 2:
         for(MotorBike *bike: bikeVect){
         if (bike->location == LOCATION[1] && bike->status == BIKE_STATUS[0] &&
             bike->bikeID != currentMember->ownBikeID && bike->memRating <= currentMember->memRating) { // DN
            std::cout << std::setw(4) << order << std::setw(16) << bike->bikeID
                      << std::setw(14) << bike->model << std::setw(13) << bike->color
                      << std::setw(13) << bike->yearMade << std::setw(15) << bike->mode
                      << std::setw(13) << bike->location << std::setw(15) << bike->rentPrice
                      << std::setw(17) << bike->bikeRating << std::setw(21) << bike->memRating
                      << std::setw(21) << bike->description << std::endl;
            order++;
            track.push_back(index);
         }
            index++;
         }
         std::cout << "=====================================================" << std::endl;
         break;
      case 3:
         for(MotorBike *bike: bikeVect){
            if (bike->location == LOCATION[2] && bike->status == BIKE_STATUS[0] &&
                bike->bikeID != currentMember->ownBikeID && bike->memRating <= currentMember->memRating) { // SG
            std::cout << std::setw(4) << order << std::setw(16) << bike->bikeID
                      << std::setw(14) << bike->model << std::setw(13) << bike->color
                      << std::setw(13) << bike->yearMade << std::setw(15) << bike->mode
                      << std::setw(13) << bike->location << std::setw(15) << bike->rentPrice
                      << std::setw(17) << bike->bikeRating << std::setw(21) << bike->memRating
                      << std::setw(21) << bike->description << std::endl;
            order++;
            track.push_back(index);
            }
         index++;
         }
         std::cout << "=====================================================" << std::endl;
         break;
      } 
      std::cout << "Continue?" << std::endl;
      std::cout << "1. Choose bike to rent." << std::endl;
      std::cout << "2. Return to Rent Menu." << std::endl;
      int choice2 = menuChoice(1,2);
      int choice3;
      switch (choice2) {
      case 1:
         choice3 = menuChoice(0,order,track);
         currentBike = bikeVect[choice3];
         currentMember->rentBikeID = currentBike->bikeID;
         currentBike->showBikeInfo();
         currentMember->sendRequest(currentBike->bikeID, currentBike->rentPrice);
         
         std::cout << "=====================================================" << std::endl;
         std::cout << "|                Return to MemberMenu               |" << std::endl;
         std::cout << "=====================================================" << std::endl;
         memberMenu();
         break;
      case 2:
         rentMenu();
         break;
      }
}
void System::checkOwnBike(){
   if (currentMember->ownBikeID != "null"){  // already have bike list
      std::cout << "You already have bike!" << std::endl;
      for (auto bike : bikeVect){
         if (currentMember->ownBikeID == bike->bikeID){
            currentBike = bike;
         }
      }
      
      currentBike->showBikeInfo();
      std::cout << "Continue?" << std::endl;
      std::cout << "1. Yes, remove current bike and add new bike." << std::endl;
      std::cout << "2. No, return to Member Menu." << std::endl;
      int choice3 = menuChoice(1,2);
      switch (choice3) {
         case 1:
            for (int i = 0; i < bikeVect.size(); i++) {
               if (bikeVect[i]->bikeID == currentMember->ownBikeID) {
                  bikeVect.erase(bikeVect.begin()+ i);
               }
            }
            currentBike = nullptr;  //remove pointer
            addBike();
            memberMenu();
            break;
         case 2:
            memberMenu();
            break;
      }
   }
   else {
      addBike();
      memberMenu();
   }
}
void System::addBike(){
   // checkOwnBike();
   std::cout << "=====================================================" << std::endl;
   std::cout << "|                  -BIKE REGISTRATION-              |" << std::endl;
   std::cout << "=====================================================" << std::endl;
   std::cin.ignore();
   
   std::string bikeid, model, color,
       enginesize, mode, yearmade,
       bikerating, rentprice, location,
       memrating, status, rentduration,
       description;
   bikeid = bikeIDGenerate();

   do {
      std::cout << "Format: no certain symbols" << std::endl;
      std::cout << "Enter motorbike model: ";
      std::getline(std::cin,model);
      std::cout << "=====================================================" << std::endl;
   } while (!isModel(model));
   do {
      std::cout << "Format: no number, no symbol" << std::endl;
      std::cout << "Enter bike color: ";
      std::getline(std::cin,color);
      std::cout << "=====================================================" << std::endl;   
   } while (!isColor(color));

   do {
      std::cout << "Format: no symbol, character. Unit (cc) Number ONLY." <<std::endl;
      std::cout << "Enter bike engine size: ";
      std::getline(std::cin,enginesize);
      std::cout << "=====================================================" << std::endl;
   } while (!isEngineSize(enginesize));

   std::cout << "Choose bike mode: " << std::endl;
   std::cout << "1. Auto.\t2. Manual.\t3. Semi." << std::endl;
   int choice = menuChoice(1,3);
   switch (choice) {
   case 1:
      mode = MODE[0];   // auto
      break;
   case 2:
      mode = MODE[1];   // Manual
      break;
   case 3:
      mode = MODE[2];   // Semi
      break;
   }
   std::cout << "=====================================================" << std::endl;
   std::cin.ignore();
   do {
      std::cout << "Format: YYYY, number ONLY." << std::endl;
      std::cout << "Enter bike year made: ";
      std::getline(std::cin,yearmade);
      std::cout << "=====================================================" << std::endl;
   } while (!isYear(yearmade));
   
   bikerating = "10.0";

   do {
      std::cout << "Format: integer number > 0." << std::endl;
      std::cout << "Enter bike rent price: ";
      std::getline(std::cin,rentprice);
      std::cout << "=====================================================" << std::endl;
   } while (!isRent(rentprice));

   std::cout << "Choose bike available location: " << std::endl;
   std::cout << "1. Hanoi.\t2. Danang.\t3. Saigon." << std::endl;
   int choice2 = menuChoice(1,3);
   switch (choice2) {
   case 1:
      location = LOCATION[0];   // HN
      break;
   case 2:
      location = LOCATION[1];   // DN
      break;
   case 3:
      location = LOCATION[2];   // SG
      break;
   }
   std::cout << "=====================================================" << std::endl;
   std::cin.ignore();
   do {
      std::cout << "Format: Number ONLY." << std::endl;
      std::cout << "Enter member rating: ";
      std::getline(std::cin, memrating);
      std::cout << "=====================================================" << std::endl;
   } while (!isFloat(memrating));

   status = BIKE_STATUS[1]; // status unavailable by default
   rentduration = "0";
   do {
      std::cout << "Format: no certain symbol" << std::endl;
      std::cout << "Enter bike description: ";
      std::getline(std::cin,description);
      std::cout << "=====================================================" << std::endl;
   } while (!isDescription(description));
   
   MotorBike *bike = new MotorBike(bikeid, model, color,
                                   std::stoi(enginesize), mode, yearmade,
                                   std::stof(bikerating), std::stoi(rentprice), location,
                                   std::stof(memrating), status, std::stoi(rentduration),
                                   description);
   bikeVect.push_back(bike);
   currentMember->ownBikeID = bikeid;  //save bike id to member
   currentBike = bike;
   bike->showBikeInfo();   // show bike information
   std::cout << "=====================================================" << std::endl;
   std::cout << "|              -BIKE ADDED SUCCESSFULLY-            |" << std::endl;
   std::cout << "=====================================================" << std::endl;
}
void System::listBike(){
   std::cout << "=====================================================" << std::endl;
   std::cout << "List/Unlist motorbike." << std::endl;
   std::cout << "1. List bike for rent." << std::endl;
   std::cout << "2. Unlist bike." << std::endl;
   int choice = menuChoice(1,2);
   for (auto bike : bikeVect){
      if (bike->bikeID == currentMember->ownBikeID){
         currentBike = bike;  //locate bike
      }
   }
   switch (choice) {
      case 1:
         currentBike->status = BIKE_STATUS[0]; // Available
         currentBike->rentDuration = 0;
         break;
      case 2:
         currentBike->status = BIKE_STATUS[1];  //Unavailable
         break;
   }
   std::cout << "=====================================================" << std::endl;
   std::cout << "|                   -ACTION COMPLETED-              |" << std::endl;
   std::cout << "=====================================================" << std::endl;   
   memberMenu();
}
