#ifndef SYSTEM_H
#define SYSTEM_H
#include <bits/stdc++.h>

#include "../User/Member.h"
#include "../User/Admin.h"
#include "../Bike/MotorBike.h"

#define MEMBER_FILE "../Data/Member.txt"
#define BIKE_FILE "../Data/Bike.txt"
#define ADMIN_FILE "../Data/Admin.txt"
class System {
   private:
      std::vector <Member*> memberVect;
      std::vector <MotorBike*> bikeVect;

      Admin *admin;
      Member *currentMember;  //pointer to current member
      MotorBike *currentBike; //pointer to current motorbike
   public:
      System();

      void mainMenu();

      void guestMenu();
      void memberLoginMenu();
      void adminLoginMenu();

      void loadMembers();  //retrieve all member in system to vector
      void loadBikes(); //retrieve all member in system to vector
      void loadAdmin(); //retrieve admin to system;

      bool adminLogin(std::string userName, std::string password);
      void adminMenu();
      void adminViewBikes();
      void adminViewMembers();

      bool memberLogin(std::string userName, std::string password);
      void memberMenu();
      
      void guestViewBikes();
      void guestRegister();

      void saveMemberToFile();
      void saveBikesToFile();
      
};
std::vector<std::string> splitString(std::string &input, char delimiter);
std::string stringCut(std::string &s);
int menuChoice(int start, int end);
int menuChoice(int start, int end, std::vector<int> track);
bool numValid(std::string s);
bool isPhoneNum(std::string s);  // first 0, 10 char, all num
bool isPassword(std::string s);  // min length 8 char, no space
bool isUsername(std::string s);  // no symbol, space, min length 6
bool isFullname(std::string s);  // no symbol, number,
bool isDateFormat(std::string s);       // DD/MM/YYYY
bool isLicence(std::string s);          // 12 number, no space or symbol
bool isIDValid(std::string s, int num); // 8 number for passport, 10 for citizen ID
#endif