#ifndef FUNCTION_H
#define FUNCTION_H
#include <bits/stdc++.h>

//Options choosing functions
int menuChoice(int start, int end);
int menuChoice(int start, int end, std::vector<int> track);

//for member registration check
bool numValid(std::string s);
bool numValid(std::string s, int range);
bool isPhoneNum(std::string s);  // first 0, 10 char, all num
bool isPassword(std::string s);  // min length 8 char, no space
bool isUsername(std::string s);  // no symbol, space, min length 6
bool isFullname(std::string s);  // no symbol, number,
bool isDateFormat(std::string s);       // DD/MM/YYYY
bool isLicence(std::string s);          // 12 number, no space or symbol
bool isIDValid(std::string s, int num); // 8 number for passport, 10 for citizen ID

//string manipulation functions
std::vector<std::string> splitString(std::string &input, char delimiter);
std::string stringCut(std::string &s);

//time function
int duration (std::string startdate, std::string enddate);

// for bike registration check
bool isModel(std::string s);// no certain characters
bool isColor(std::string s);  //letter only, no symbol/number
bool isEngineSize(std::string s);   // number only, > 0
bool isYear(std::string s); // 4 num only
bool isRent(std::string s); // int number > 0, 
bool isDescription(std::string s); //
bool isFloat(std::string s);
bool isFloat(std::string s, float upper, float lower);
bool isComment(std::string s);

//IDGenerate
std::string memIDGenerate();
std::string bikeIDGenerate();
std::string rqstIDGenerate();
std::string MemRevIDGen();
std::string BikeRevIDGen();

#endif