#ifndef FUNCTION_H
#define FUNCTION_H
#include <bits/stdc++.h>

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

std::vector<std::string> splitString(std::string &input, char delimiter);
std::string stringCut(std::string &s);
int duration (std::string startdate, std::string enddate);

#endif