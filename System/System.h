#ifndef SYSTEM_H
#define SYSTEM_H
#include <bits/stdc++.h>
#include "../Function/Function.h"

#include "../User/Member.h"
#include "../User/Admin.h"
#include "../Bike/MotorBike.h"

#define MEMBER_FILE "Data/Member.txt"
#define BIKE_FILE "Data/Bike.txt"
#define ADMIN_FILE "Data/Admin.txt"

class System {
   private:
      std::vector <Member*> memberVect;
      std::vector <MotorBike*> bikeVect;

      Admin *admin;
      Member *currentMember = nullptr;  //pointer to current member
      MotorBike *currentBike = nullptr; //pointer to current motorbike
   public:
      System();   //default constructor

      void mainMenu();  

      void guestMenu(); 
      void memberLoginMenu(); // login menu
      void adminLoginMenu();  // login menu

      void loadMembers();  //retrieve all member in system to vector
      void loadBikes();    //retrieve all member in system to vector
      void loadAdmin();    //retrieve admin to system;

      bool adminLogin(std::string userName, std::string password);
      void adminMenu();       //after login
      void adminViewBikes();  //view all bikes
      void adminViewMembers();//view all members

      bool memberLogin(std::string userName, std::string password);
      void memberMenu();   //after login
      void addBike();      //add bike into system

      void guestViewBikes();     // guest view bike
      void guestRegister();      // register new member

      void saveMemberToFile();   //save member to file
      void saveBikesToFile();    //save bike to file

      void rentMenu();  //member rent menu
      void listBike();  //set status of bike for rent

      void checkOwnBike();
      // void viewHistory();
      
};
#endif