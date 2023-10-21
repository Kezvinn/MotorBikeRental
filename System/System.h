#ifndef SYSTEM_H
#define SYSTEM_H
#include <bits/stdc++.h>
//class files
#include "../Function/Function.h"
#include "../User/Member.h"
#include "../User/Admin.h"
#include "../Bike/MotorBike.h"
//data files
#define MEMBER_FILE "Data/Member.txt"
#define BIKE_FILE "Data/Bike.txt"
#define ADMIN_FILE "Data/Admin.txt"

class System {
   private:
      std::vector <Member*> memberVect;   //all member
      std::vector <MotorBike*> bikeVect;  // all bike
      
      Admin *admin;
      Member *currentMember = nullptr;  //pointer to current member
      MotorBike *currentBike = nullptr; //pointer to current motorbike
   public:
      System();   //default constructor

      void mainMenu();  
      //login menu
      void guestMenu(); 
      void memberLoginMenu(); // login menu
      void adminLoginMenu();  // login menu
      
      //input functions
      void loadMembers();  //retrieve all member in system to vector
      void loadBikes();    //retrieve all member in system to vector
      void loadAdmin();    //retrieve admin to system;
      
      //output functions
      void saveMemberToFile();   //save member to file
      void saveBikesToFile();    //save bike to file
      void saveAdminToFile();    //save admin to file

      //guest functions
      void guestViewBikes();     // guest view bike
      void guestRegister();      // register new member
      
      //admin functions
      bool adminLogin(std::string userName, std::string password);  //admin login
      void adminMenu();       //after login
      void adminViewBikes();  //view all bikes
      void adminViewMembers();//view all members

      //member functions
      bool memberLogin(std::string userName, std::string password);
      void memberMenu();   //after login
      void rentMenu();     //1. member rent menu
      void checkOwnBike(); //2.1 check if already own bike
      void addBike();      //2.2 add new bike to system
      void listBike();     //3. set status of bike for rent
      
      //review menu
      void memRevMenu();   //6. review member
      void bikeRevMenu();  //7. review bike

      void bikeSttCheck(); //check for current bike availability at given time

};
#endif