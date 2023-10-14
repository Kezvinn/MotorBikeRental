#include "Function.h"
//-------------------Option Choosing Functions----------------------------
int menuChoice(int start, int end) {
   int finalChoice;
   bool flag;
   std::string tempo;
   do {
      std::cout << "Enter your choice: ";
      std::cin >> tempo;
      if (!numValid(tempo)) {   //check if the input is number
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
      if (!numValid(tempo)){   //check if the input is number
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
//-------------------Member information check-----------------------------
bool numValid(std::string s){
   std::regex reg ("^[0-9 ]+$"); //only allow number
   std::string str;
   str = stringCut(s);
   if (!std::regex_match(str, reg)) {
      return false;
   }
   return true;
}
bool numValid(std::string s, int range){  //number in a certain range
   if (std::stoi(s) > range) {return false;};
   std::regex reg ("^[0-9 ]+$"); //only allow number
   std::string str;
   str = stringCut(s);
   if (!std::regex_match(str, reg)) {
      return false;
   }
   return true;
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
//-------------------String Manip functions--------------------------------
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
//-------------------Time calculate----------------------------------------
int duration (std::string startDate, std::string endDate){  // DD/MM/YYYY
   std::vector <std::string> data1= splitString(startDate,'/');
   std::vector <std::string> data2= splitString(endDate,'/');
   int d1,d2,m1,m2,y1,y2;
   d1 = std::stoi(data1[0]);
   m1 = std::stoi(data1[1]);
   y1 = std::stoi(data1[2]);

   d2 = std::stoi(data2[0]);
   m2 = std::stoi(data2[1]);
   y2 = std::stoi(data2[2]);

   const int Days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   if (m1 <= 2) {
      y1--;
   }
   int ly1 = y1 / 4 - y1 / 100 + y1 / 400;   //leap year check
   
   if (m2 <= 2) {
      y2--;
   }
   int ly2 = y2 / 4 - y2 / 100 + y2 / 400;   //leap year check
   
   long int count1 = y1 * 365 + d1;
   for (int i = 0; i < m1 - 1; i++) {
      count1 += Days[i];
   }
   count1 += ly1;
   
   long int count2 = y2 * 365 + d2;
   for (int i = 0; i < m2 - 1; i++) {
      count2 += Days[i];
   }
   count2 += ly2;

   return count2 - count1; 
}
//-------------------Bike information check--------------------------------
bool isModel(std::string s){ // letter, certain characters allowed
   std::regex reg("^[a-zA-Z&=_'-+,<>. ]+$"); 
   s = stringCut(s);
   if (!std::regex_match(s, reg)) {
      return false; 
   } 
   return true;
}
bool isColor(std::string s){  //letter only, no symbol/number
   std::regex reg("^[a-zA-Z ]+$"); 
   s = stringCut(s);
   if (!std::regex_match(s, reg)) {
      return false; 
   } 
   return true;
} 
bool isEngineSize(std::string s){  // number only, > 0  
   if(std::stoi(s) < 0) {return false;}
   std::regex reg ("^[0-9 ]+$"); //only allow number
   std::string str;
   str = stringCut(s);
   if (!std::regex_match(str, reg)) {
      return false;
   }
   return true;
}
bool isYear(std::string s){ // 4 num only
   if (s.length() != 4) {return false;}
   std::regex reg ("^[0-9 ]+$"); //only allow number
   std::string str;
   str = stringCut(s);
   if (!std::regex_match(str, reg)) {
      return false;
   }
   return true;
}
bool isRent(std::string s){   // int number > 0,
   if (std::stoi(s) < 0) {return false;} 
   std::regex reg("^[0-9 ]+$"); // only allow number
   std::string str;
   str = stringCut(s);
   if (!std::regex_match(str, reg)) {
      return false;
   }
   return true;
}  
bool isDescription(std::string s){  // letter and certain characters allowed
   std::regex reg("^[a-zA-Z&=_'-+,<>. ]+$"); 
   s = stringCut(s);
   if (!std::regex_match(s, reg)) {
      return false; 
   } 
   return true;
}
bool isFloat(std::string s) {
   std::regex reg ("^[0-9. ]+$"); //only allow number
   std::string str;
   str = stringCut(s);
   if (!std::regex_match(str, reg)) {
      return false;
   }
   return true;
}