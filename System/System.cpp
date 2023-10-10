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
   std::cout << "=====================================================" << std::endl;   std::cout << "1. Member Login" <<std::endl;
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
   std::cout << "=====================================================" << std::endl;   std::cout << "1. Admin Login" <<std::endl;
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
      //rent menu
      break;
   case 2:
      //add bike
      break;
   case 3:
      //list/unlist bike
      break;
   case 4:  
      //view request
      break;
   case 5:
      //view history
      break;
   case 6:
      std::cout << "=====================================================" << std::endl;
      std::cout << "|                 -THANK YOU FOR USING-             |" << std::endl;
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
                                  dataList[8], std::stof(dataList[9]), std::stoi(dataList[10])); // add attributes
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
            file << "|" << currentMember->ownBikeID;
         }
         else {
            file << "|" << mem->ownBikeID;
         }
      } else {
         file << "|" << mem->ownBikeID;
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
      break;
   }
}
void System::guestRegister(){
   std::string memID, username, password,
       fullname, phonenumber,
       idtype, idnumber, drivernumber,
       exptdate;
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
                            exptdate, memrating, credits);
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
   std::cout << std::left << std::setw(10) << "-Index- "
             << std::left << std::setw(15) << "-Bike_ID-" 
             << std::left << std::setw(15) << "-Model-"
             << std::endl;
   for (auto bike : bikeVect) {
      std::cout << std::left << std::setw(12) << index
                << std::left << std::setw(13) << bike->bikeID
                << std::left << std::setw(15) << bike->model << std::endl;
      index++;
   }
   std::cout << "Continue:" << std::endl;
   std::cout << "1. View motorbikes detail"  << std::endl;
   std::cout << "2. Back to admin menu" << std::endl;
   int choice = menuChoice(1,2);
   switch (choice){
      case 1:
         index = 1;
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
                   << std::left << std::setw(30) << "-Descripton-"
                   << std::endl;
         for(auto bike: bikeVect){
            std::cout << std::left << std::setw(10) << index
                   << std::left << std::setw(15) << bike->bikeID
                   << std::left << std::setw(15) << bike->model
                   << std::left << std::setw(20) << bike->color
                   << std::left << std::setw(15) << bike->yearMade
                   << std::left << std::setw(15) << bike->mode
                   << std::left << std::setw(15) << bike->location
                   << std::left << std::setw(15) << bike->rentPrice
                   << std::left << std::setw(15) << bike->bikeRating
                   << std::left << std::setw(15) << bike->memRating
                   << std::left << std::setw(30) << bike->description
                   << std::endl;
            index++;
         }
         std::cout << "Total Motorbikes: " << bikeVect.size() << std::endl;
         std::cout << "Return to admin menu "<< std::endl;
         adminMenu();
         break;
      case 2:
         adminMenu();
         break;
   }
}
void System::adminViewMembers(){
   int index = 1;
   loadMembers();
   std::cout << "Member in the system: "<<std::endl;
   std::cout << std::left << std::setw(10) << "-Index- "
             << std::left << std::setw(15) << "-Member_ID-" 
             << std::left << std::setw(15) << "-Full Name-"
             << std::endl;
   for (auto mem : memberVect) {
      std::cout << std::left << std::setw(13) << index
                << std::left << std::setw(13) << mem->memberID
                << std::left << std::setw(15) << mem->fullName << std::endl;
      index++;
   }
   std::cout << std::endl;
   std::cout << "1. View member details" << std::endl;
   std::cout << "2. Back to admin menu" << std::endl;
   int choice = menuChoice(1,2);
   switch (choice){
      case 1:
         index = 1;
         std::cout << std::left << std::setw(10) << "-Index- "
                   << std::left << std::setw(15) << "-Member_ID-"
                   << std::left << std::setw(15) << "-Username-"
                   << std::left << std::setw(15) << "-Password-"
                   << std::left << std::setw(15) << "-Full Name-"
                   << std::left << std::setw(15) << "-Phone Number-"
                   << std::left << std::setw(15) << "-ID_Type-"
                   << std::left << std::setw(15) << "-ID_Number-"
                   << std::left << std::setw(15) << "-Credits-"
                   << std::left << std::setw(15) << "-Rating-" << std::endl;
         for (auto mem : memberVect) {
         std::cout << std::left << std::setw(10) << index
                   << std::left << std::setw(15) << mem->memberID
                   << std::left << std::setw(15) << mem->username
                   << std::left << std::setw(15) << mem->password
                   << std::left << std::setw(15) << mem->fullName
                   << std::left << std::setw(15) << mem->phoneNumber
                   << std::left << std::setw(15) << mem->idType
                   << std::left << std::setw(15) << mem->idNumber
                   << std::left << std::setw(15) << mem->credits
                   << std::left << std::setw(15) << mem->memRating << std::endl;
         index++;
         }
         std::cout << "Total members: " << memberVect.size()<< std::endl;
         std::cout << "Return to admin menu "<< std::endl;
         adminMenu();
         break;
      case 2:
         adminMenu();
         break;
   }
}

void System::rentMenu(){
   std::cout << "=====================================================" << std::endl;
   std::cout << "|                     -RENT MENU-                   |" << std::endl;
   std::cout << "=====================================================" << std::endl;
   std::cout << "Choose your location:\t1. Hanoi\t2. Danang\t3. Saigon\n";
   int index = 0;
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
            if (bike->location == LOCATION[0]){  //HN
               std::cout << std::left << std::setw(10) << index
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
            }
         index++;
         }
         std::cout << "=====================================================" << std::endl;
         break;
      case 2:
         for(MotorBike *bike: bikeVect){
               if (bike->location == LOCATION[1]){  //DN
               std::cout << std::left << std::setw(10) << index
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
               }
            index++;
         }
         std::cout << "=====================================================" << std::endl;
         break;
      case 3:
         for(MotorBike *bike: bikeVect){
            if (bike->location == LOCATION[2]){  //SG
               std::cout << std::left << std::setw(10) << index
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
            }
         index++;
         }
         std::cout << "=====================================================" << std::endl;
         break;
      } 
   
}
//-------------------Debug Functions--------------------------------
int menuChoice(int start, int end) {
   int finalChoice;
   bool flag;
   std::string tempo;
   do {
      std::cout << "Enter your choice: ";
      std::cin >> tempo;
      if (numValid(tempo)) {   //check if the input is number
         std::cout << "Only enter number as choice! Try again!" << std::endl;
         flag = false;
         continue;
      }
      finalChoice = std::stoi(tempo);
      if (finalChoice > end || finalChoice < start){  //check if the input is in range
         std::cout << "Enter choice in the range " << start << " - " << end << " only!" << std::endl;
         flag = false;
      } else {
         flag = true;
      }
   } while (!flag);
   return finalChoice;
};
int menuChoice(int start, int end,std::vector<int> track) { 
   int finalChoice;
   bool flag;
   std::string tempo;
   do{
      std::cout << "Enter your bike choice: ";
      std::cin >> tempo;
      // std::cin.ignore();
      if (numValid(tempo)){   //check if the input is number
         std::cout <<"Only enter number as choice! Try again!"<<std::endl;
         flag = false;
         continue;
      }
      finalChoice = std::stoi(tempo);
      for (int i = 0; i < track.size(); i++) {
         if (finalChoice > end || finalChoice < start) {
            std::cout << "Enter choice in the range " << start << " - " << end << " only!" << std::endl;
            flag = false;
         }
         else
         {
            flag = true;
         }
      }
   } while (!flag);
   return track[finalChoice];
};
//-------------------Validate input for system---------------------
bool numValid(std::string s){
   std::regex reg ("^[0-9 ]+$"); //only allow number
   std::string str;
   str = stringCut(s);
   if (!std::regex_match(str, reg)) {
      return false;
   }
   return false;
}
bool isPhoneNum(std::string s){// first 0, 10 char, all num
   if (s.length() != 10){ return false;}
   if (s[0] != '0'){ return false;}
   std::regex reg ("^[0-9 ]+$"); //only allow number
   std::string str = stringCut(s);
   if(!std::regex_match(str, reg)) {
      return false;
   }
   return true;
}  
bool isPassword(std::string s){    // min length 8 char, no space
   //min length of 8 - 15, one uppercase, one number, one special character
   std::regex reg ("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[@$!%*?&])[A-Za-z0-9@$!%*?&]{8,15}$");
   s = stringCut(s);
   if (!std::regex_match(s, reg)){
      return false;
   } 
   return true;
}
bool isUsername(std::string s){// no symbol, space, min length 6
   if (s.length() < 6){    // min length > 6
      // std::cout << "too short" << std::endl;
      return false; 
   }
   std::regex reg ("^[&=_'-+,<>. ]+$"); //doesnt include those symbols (&=_'-+,<>.)
   if (std::regex_match(s, reg)){
      // std::cout << "Cant have these symbols" << std::endl;
      return false;
   }
   for (int i = 0; i < s.length(); i++) {
      if (s[i] == ' ') { // no whitespace
         // std::cout << "No whitespace" << std::endl;
         return false;
      }
   }
   return true;
}  
bool isFullname(std::string s){// no symbol, number,
   std::regex reg("^[a-zA-Z ]+$"); // only allow letter uppercase and lowercase
   s = stringCut(s);
   if (!std::regex_match(s, reg)) {
      return false; 
   } 
   return true;
}  
bool isDateFormat(std::string s){   // DD/MM/YYYY
   if ((s.length() != 10) || (s[2] != '/' || s[5] != '/')){ // format check DD/MM/YYYY
      std::cerr << "Invalid format string. Must follow format DD/MM/YYYY." << std::endl;
      return false;
   }
   
   std::string date = s.substr(0,2);
   std::string month = s.substr(3,2);
   std::string year = s.substr(6,4);
   // std::cout << "day: " << date << " month: "  << month << " year: " << year << std::endl;
   
   if (std::stoi(month) == 2){   // leap year 
      if (std::stoi(year) % 4 == 0){
         if (std::stoi(date) > 29) {
            std::cerr << "Invalid date. Leap year. February only have 29 days!" << std::endl;
            return false;
         }  
      } else {
         if (std::stoi(date) > 28) {
            std::cerr << "Invalid date. Not a leap year. February only have 28 days!" << std::endl;
            return false;
         } 
      }

   }



   if (std::stoi(year) < 2023){  //year check
      std::cerr << "License expired" << std::endl;
      return false;
   } 

   if (std::stoi(month) > 12 || std::stoi(month) < 0){   //month check
      std::cerr << "Invalid Month. Only 1-12" << std::endl;
      return false;
   }

   for (int m : {1,3,5,7,8,10,12}) {   //date check
      if (std::stoi(month) == m && std::stoi(date) > 31){
         std::cerr << "Invalid date. Month " << month  << " only have 31 days" << std::endl;
         return false;
      }
   }
   for (int m : {2, 4, 6, 9, 11}) {
      if (std::stoi(month) == m && std::stoi(date) > 30){
         std::cerr << "Invalid date. Month " << month  << " only have 30 days" << std::endl;
         return false;
      }
   }
   

   return true;
}       
bool isLicence(std::string s){// 12 number, no space or symbol
   if (s.length() != 12)
      return false;              // minlength is 12
   std::regex reg ("^[0-9 ]+$"); //only allow number
   s = stringCut(s);
   if (!regex_match(s,reg)){
      return false;
   } else {
      return true;
   }
}
bool isIDValid(std::string s, int num){// 8 number for passport, 10 for citizen ID
   std::regex reg ("^[0-9 ]+$"); //only allow number
   std::string str;
   str = stringCut(s);
   if (num == 1){ //citizenID
      if(s.length() != 12) return false;
      if(!regex_match(str,reg))return false;
   } else if(num == 2){ //passport
      if(s.length() != 8) return false;   
      if(!regex_match(str,reg))return false;
   }
   return true;
} 
//-------------------Other support functions-----------------------
std::vector <std::string> splitString(std::string &str, char delimiter){//cut string into substring
   std::vector <std::string> result;
   std::istringstream is(str);
   std::string item;
   while (std::getline(is, item, delimiter)) {
      result.push_back(item);
   }
   return result;
}
std::string stringCut(std::string &s){  //remove all spaces
   std::string result;
   for (char c : s){
      if (c == ' '){
         continue;
      } else {
         result += c;
      }
   }
   return result;
}