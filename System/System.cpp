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
         saveMemberToFile();
         break;
      case 3:
         mainMenu();
         saveMemberToFile();
         saveBikesToFile();
         break;
   }
}
void System::memberLoginMenu(){
   std::string username, password;
   std::cout << "=====================================================" << std::endl;
   std::cout << "|                    -MEMBER MENU-                  |" << std::endl;
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
      std::cout << "Enter Member Username: ";
      std::cin >> username;
      std::cin.ignore(0,' ');
      std::cout << "Enter Member Password: ";
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
   std::cout << "|                    -ADMIN MENU-                   |" << std::endl;
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
      std::cout << "Enter Admin Username: ";
      // std::getline(std::cin, username);
      std::cin >> username;
      std::cin.ignore(0,' ');
      std::cout << "Enter Admin Password: ";
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
      break;
   case 3:
      //list/unlist bike
      break;
   case 4:  
      //view request
      currentMember->viewRequest(); 
      break;
   case 5:
      //view history
      break;
   case 6:
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
                                  std::stoi(dataList[11]), dataList[12],dataList[13]); // add attributes
      memberVect.push_back(member);
   }
   file.close();  
   std::cout << "Member file loaded" << std::endl;
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
   std::cout << "Bike file loaded" << std::endl;
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

   std::cout << "Admin file loaded" << std::endl;
   file.close();
}

void System::saveBikesToFile(){
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
   std::cout << "Motorbike file saved successfully!" << std::endl;
}
void System::saveMemberToFile(){
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
           << mem->credits << "|";
      if (currentMember != nullptr) {  
         if(mem->memberID == currentMember->memberID && currentMember->ownBike == true) {
            file << currentMember->ownBike << "|" << currentMember->ownBikeID;
         }
         else {
            file << mem->ownBike << "|" << mem->ownBikeID;
         }
      } else {
         if(mem->ownBike == true) {
            file << mem->ownBike << "|" << mem->ownBikeID;
         }
         else {
            file << mem->ownBike << "|null";
         }
         // file << mem->ownBike << "|" << mem->ownBikeID;
      }
      file << "\n";
   }
   file.close();
   std::cout << "Members file saved successfully!" << std::endl;
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
   std::cout << "2. Exit program." << std::endl;
   int choice = menuChoice(1,3);
   switch (choice){
   case 1:
      guestRegister();
      break;
   case 2:
      std::cout << "=====================================================" << std::endl;
      std::cout << "|                 -THANK YOU FOR USING-             |" << std::endl;
      std::cout << "=====================================================" << std::endl;
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
   bool ownbike = false;
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
                            ownbike, ownbikeid, rentbikeid);
   memberVect.push_back(mem);
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
   std::cout << /*std::left <<*/ std::setw(7) << "-Index-"
             << /*std::left <<*/ std::setw(15) << "-Bike ID-"
             << /*std::left <<*/ std::setw(13) << "-Model-"
             << /*std::left <<*/ std::setw(13) << "-Color-"
             << /*std::left <<*/ std::setw(16) << "-Year Made-"
             << /*std::left <<*/ std::setw(12) << "-Mode-"
             << /*std::left <<*/ std::setw(16) << "-Location-"
             << /*std::left <<*/ std::setw(15) << "-Credits-"
             << /*std::left <<*/ std::setw(19) << "-Bike Rating-"
             << /*std::left <<*/ std::setw(21) << "-Member Rating-"
             << /*std::left <<*/ std::setw(18) << "-Descripton-"
             << std::endl;
   for (auto bike : bikeVect) {
      std::cout << /*std::left* <<*/ std::setw(4) << index
                << /*std::left* <<*/ std::setw(16) << bike->bikeID
                << /*std::left* <<*/ std::setw(14) << bike->model
                << /*std::left* <<*/ std::setw(13) << bike->color
                << /*std::left* <<*/ std::setw(13) << bike->yearMade
                << /*std::left* <<*/ std::setw(15) << bike->mode
                << /*std::left* <<*/ std::setw(13) << bike->location
                << /*std::left* <<*/ std::setw(15) << bike->rentPrice
                << /*std::left* <<*/ std::setw(17) << bike->bikeRating
                << /*std::left* <<*/ std::setw(21) << bike->memRating
                << /*std::left* <<*/ std::setw(21) << bike->description
                << std::endl;
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
   std::cout << /*std::left <<*/ std::setw(7) << "-Index-"
             << /*std::left <<*/ std::setw(17) << "-Member_ID-"
             << /*std::left <<*/ std::setw(16) << "-Username-"
             << /*std::left <<*/ std::setw(16) << "-Password-"
             << /*std::left <<*/ std::setw(17) << "-Full Name-"
             << /*std::left <<*/ std::setw(15) << "-Phone #-"
             << /*std::left <<*/ std::setw(15) << "-ID Type-"
             << /*std::left <<*/ std::setw(18) << "-ID Number#-"
             << /*std::left <<*/ std::setw(15) << "-Credits-"
             << /*std::left <<*/ std::setw(14) << "-Rating-" << std::endl;
   for (auto mem : memberVect) {
      std::cout << /*std::left <<*/ std::setw(4) << index
                  << /*std::left <<*/ std::setw(17) << mem->memberID
                  << /*std::left <<*/ std::setw(16) << mem->username
                  << /*std::left <<*/ std::setw(18) << mem->password
                  << /*std::left <<*/ std::setw(19) << mem->fullName
                  << /*std::left <<*/ std::setw(15) << mem->phoneNumber
                  << /*std::left <<*/ std::setw(14) << mem->idType
                  << /*std::left <<*/ std::setw(18) << mem->idNumber
                  << /*std::left <<*/ std::setw(11) << mem->credits
                  << /*std::left <<*/ std::setw(16) << mem->memRating << std::endl;
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
   std::cout << std::left << std::setw(10) << "-Index- "
             << std::left << std::setw(15) << "-Bike ID-"
             << std::left << std::setw(15) << "-Model-"
             << std::left << std::setw(15) << "-Color-"
             << std::left << std::setw(15) << "-Year Made-"
             << std::left << std::setw(15) << "-Mode-"
             << std::left << std::setw(15) << "-Location-"
             << std::left << std::setw(15) << "-Credits-"
             << std::left << std::setw(15) << "-Bike Rating-"
             << std::left << std::setw(15) << "-Member Rating-"
             << std::left << std::setw(25) << "-Descripton-"
             << std::endl;
   switch (choice) {
      case 1:
         for(MotorBike *bike: bikeVect){
            if (bike->location == LOCATION[0] && bike->status == BIKE_STATUS[0]){  //HN and Available
               std::cout << std::left << std::setw(10) << order
                         << std::left << std::setw(15) << bike->bikeID
                         << std::left << std::setw(15) << bike->model
                         << std::left << std::setw(15) << bike->color
                         << std::left << std::setw(15) << bike->yearMade
                         << std::left << std::setw(15) << bike->mode
                         << std::left << std::setw(15) << bike->location
                         << std::left << std::setw(15) << bike->rentPrice
                         << std::left << std::setw(15) << bike->bikeRating
                         << std::left << std::setw(15) << bike->memRating
                         << std::left << std::setw(25) << bike->description
                         << std::endl;
               order++;
               track.push_back(index);
            }  
         index++;
         }
         std::cout << "=====================================================" << std::endl;
         break;
      case 2:
         for(MotorBike *bike: bikeVect){
               if (bike->location == LOCATION[1] && bike->status == BIKE_STATUS[0]){  //DN
               std::cout << std::left << std::setw(10) << order
                         << std::left << std::setw(15) << bike->bikeID
                         << std::left << std::setw(15) << bike->model
                         << std::left << std::setw(15) << bike->color
                         << std::left << std::setw(15) << bike->yearMade
                         << std::left << std::setw(15) << bike->mode
                         << std::left << std::setw(15) << bike->location
                         << std::left << std::setw(15) << bike->rentPrice
                         << std::left << std::setw(15) << bike->bikeRating
                         << std::left << std::setw(15) << bike->memRating
                         << std::left << std::setw(25) << bike->description
                         << std::endl;
               order++;
               track.push_back(index);
               }
            index++;
         }
         std::cout << "=====================================================" << std::endl;
         break;
      case 3:
         for(MotorBike *bike: bikeVect){
            if (bike->location == LOCATION[2] && bike->status == BIKE_STATUS[0]){  //SG
               std::cout << std::left << std::setw(10) << order
                         << std::left << std::setw(15) << bike->bikeID
                         << std::left << std::setw(15) << bike->model
                         << std::left << std::setw(15) << bike->color
                         << std::left << std::setw(15) << bike->yearMade
                         << std::left << std::setw(15) << bike->mode
                         << std::left << std::setw(15) << bike->location
                         << std::left << std::setw(15) << bike->rentPrice
                         << std::left << std::setw(15) << bike->bikeRating
                         << std::left << std::setw(15) << bike->memRating
                         << std::left << std::setw(25) << bike->description
                         << std::endl;
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
         std::cout << "choice3 = " << choice3 << std::endl;
         currentBike = bikeVect[choice3];
         currentMember->rentBikeID = currentBike->bikeID;
         currentBike->showBikeInfo();
         currentMember->sendRequest();
         std::cout << "=====================================================" << std::endl;
         std::cout << "|----------------Return to MemberMenu---------------|" << std::endl;
         std::cout << "=====================================================" << std::endl;
         memberMenu();
         break;
      case 2:
         rentMenu();
         break;
      }
}